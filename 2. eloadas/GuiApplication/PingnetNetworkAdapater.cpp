#include "PingnetNetworkAdapater.h"
#include "Message.h"
#include "User.h"
#include <QMutexLocker>
#include <QDebug>

PingnetNetworkAdapater::PingnetNetworkAdapater(NetInterface &net)
    : m_net(net)
    , m_maintenance()
    , m_user()
    , m_loggedInUsers()
    , m_userLock()
{
    m_net.setCallback(*this);
    m_maintenance.setInterval(kPingTimeout);
    connect(&m_maintenance, SIGNAL(timeout()), this, SLOT(maintenance()));
}

PingnetNetworkAdapater::~PingnetNetworkAdapater()
{
    reset();
}

void PingnetNetworkAdapater::login(const User &user)
{
    m_user = user;

    m_net.connect();
    m_net.sendPing(user.id(), user.name().toStdString());
    m_maintenance.start();
}

void PingnetNetworkAdapater::logout(const User &user)
{
    reset();
}

void PingnetNetworkAdapater::maintenance()
{
    m_net.sendPing(m_user.id(), m_user.name().toStdString());

    updateUsers();
}

void PingnetNetworkAdapater::updateUsers()
{
    QMutexLocker lock(&m_userLock);

    for (QMap<User, QTime>::iterator it = m_loggedInUsers.begin();
         it != m_loggedInUsers.end();
         )
    {
        if ( it->elapsed() > (2 * kPingTimeout) )
        {
            emit loggedOut(it.key());
            it = m_loggedInUsers.erase(it);
            continue; // iterator is already moved to next element
        }
        ++it;
    }
}

void PingnetNetworkAdapater::reset()
{
    m_maintenance.stop();
    m_net.close();
    m_loggedInUsers.clear();
}

void PingnetNetworkAdapater::sendMessage(const Message &message)
{
    m_net.sendMessage(message.user().id(), message.message().toStdString());
}

void PingnetNetworkAdapater::onMessage(int id, std::string message)
{
    User messageUser(id, "Unknown");

    QMutexLocker lock(&m_userLock);

    for (QMap<User, QTime>::const_iterator it = m_loggedInUsers.begin();
         it != m_loggedInUsers.end();
         ++it)
    {
        if (it.key().id() == id)
        {
            messageUser = it.key();
            break;
        }
    }

    emit messageReceived(Message(messageUser, QString::fromStdString(message)));
}

void PingnetNetworkAdapater::onPing(int id, std::string userName)
{
    User pingUser(id, QString::fromStdString(userName));

    QMutexLocker lock(&m_userLock);

    QMap<User, QTime>::iterator it = m_loggedInUsers.find(pingUser);

    if ( it != m_loggedInUsers.end() )
    {
        qDebug() << "Last seen" << pingUser.name() << it->elapsed() << "ms ago";
        it->start();
    }
    else
    {
        qDebug() << "New user" << pingUser.name();
        QTime t;
        t.start();
        m_loggedInUsers.insert(pingUser, t);
        emit loggedIn(pingUser);
    }
}
