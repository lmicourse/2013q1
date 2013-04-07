#ifndef PINGNETNETWORKADAPATER_H
#define PINGNETNETWORKADAPATER_H

#include <string>
#include <QMap>
#include <User.h>
#include <QTime>
#include <QTimer>
#include <QMutex>
#include "NetInterface.h"
#include "INetworkAdapter.h"


class PingnetNetworkAdapater : public INetworkAdapter, NetCallback
{
public:
    PingnetNetworkAdapater(NetInterface& net);
    virtual ~PingnetNetworkAdapater();

public slots:
    virtual void login(const User &user);
    virtual void logout(const User &user);
    virtual void sendMessage(const Message &message);

public:
    virtual void onMessage(int id, std::string message);
    virtual void onPing(int id, std::string userName);

private slots:
    void maintenance();

private:
    void updateUsers();
    void reset();

private:
    static const int    kPingTimeout = 3000;

    NetInterface&       m_net;
    QTimer              m_maintenance;
    User                m_user;
    QMap<User, QTime>   m_loggedInUsers;
    QMutex              m_userLock;
};

#endif // PINGNETNETWORKADAPATER_H
