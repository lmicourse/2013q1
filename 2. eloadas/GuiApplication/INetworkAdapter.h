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

signals:
    void login(const User& user);
    void logout(const User& user);
    void messageReceived(const Message& message);

private:
    INetworkAdapter();
};

#endif // INETWORKADAPTER_H
