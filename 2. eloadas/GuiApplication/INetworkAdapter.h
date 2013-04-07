#ifndef INETWORKADAPTER_H
#define INETWORKADAPTER_H

#include <QObject>

class User;
class Message;

class INetworkAdapter : public QObject
{
    Q_OBJECT
public:
    virtual ~INetworkAdapter() {}

public slots:
    virtual void login(const User &user) = 0;
    virtual void logout(const User& user) = 0;
    virtual void sendMessage(const Message& message) = 0;

protected slots:
    virtual void maintenance() = 0;

signals:
    void loggedIn(const User& user);
    void loggedOut(const User& user);
    void messageReceived(const Message& message);

protected:
    INetworkAdapter() {}
};

#endif // INETWORKADAPTER_H
