#include "INetworkAdapter.h"
#include "User.h"
#include "GuiApplication.h"
#include "ui_GuiApplication.h"

GuiApplication::GuiApplication(const User &user, INetworkAdapter &networkAdapter, QWidget *parent)
    : QWidget(parent)
    , ui(new Ui::GuiApplication)
    , m_user(user)
    , m_networkAdapter(networkAdapter)

{
    ui->setupUi(this);
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

void GuiApplication::onUserLogin(const User &user)
{
    QString loginText = QString("%1 is logged in ...").arg(user.name());
    ui->chatroom->append(loginText);
}

void GuiApplication::onUserLogout(const User &user)
{
    QString logoutText = QString("%1 is logged out ...").arg(user.name());
    ui->chatroom->append(logoutText);
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
