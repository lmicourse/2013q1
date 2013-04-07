#include "INetworkAdapter.h"
#include "User.h"
#include "GuiApplication.h"
#include "ui_GuiApplication.h"

GuiApplication::GuiApplication(const User &user, INetworkAdapter &networkAdapter, QWidget *parent)
    : QWidget(parent)
    , ui(new Ui::GuiApplication)
    , m_user(user)
    , m_networkAdapter(networkAdapter)
    , m_userList()

{
    ui->setupUi(this);
    ui->userList->setModel(&m_userList);
    connectNetworkSignals();
}

GuiApplication::~GuiApplication()
{
    delete ui;
}

void GuiApplication::connectNetworkSignals()
{
    connect(this, SIGNAL(login(const User&)), &m_networkAdapter, SLOT(login(const User&)));
    connect(this, SIGNAL(logout(const User&)), &m_networkAdapter, SLOT(logout(const User&)));

    connect(&m_networkAdapter, SIGNAL(loggedIn(User)), this, SLOT(onUserLogin(User)));
    connect(&m_networkAdapter, SIGNAL(loggedOut(User)), this, SLOT(onUserLogout(User)));
}

void GuiApplication::handleUserChange(const User &user, bool login)
{
    QString loginText = QString("%1 is logged %2 ...").arg(user.name()).arg(login ? "in" : "out");
    if (login)
    {
        m_userList.addUser(user);
    }
    else
    {
        m_userList.removeUser(user);
    }
    ui->chatroom->append(loginText);
}

void GuiApplication::onUserLogin(const User &user)
{
    handleUserChange(user, true);
}

void GuiApplication::onUserLogout(const User &user)
{
    handleUserChange(user, false);
}

void GuiApplication::onMessageReceived(const Message &message)
{
}

void GuiApplication::on_connectButton_clicked(bool checked)
{
    if (checked)
    {
        emit login(m_user);
    }
    else
    {
        emit logout(m_user);
    }
}
