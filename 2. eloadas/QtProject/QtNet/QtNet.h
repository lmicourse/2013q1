#ifndef QTNET_H
#define QTNET_H

#include "qtnet_global.h"
#include <QTcpSocket>
#include <QString>
#include <string>
#include "NetInterface.h"


class QTNETSHARED_EXPORT QtNet : public NetInterface
{

public:
    QtNet(QString serverIp, int port);

    virtual void connect();
    virtual void close();

    virtual void setCallback(NetCallback& callback);
    virtual void sendPing(int selfId, std::string selfName);
    virtual void sendMessage(int selfId, std::string message);

private:
    void sendPacket(QString type, int selfId, QString selfName);

private:
    NetCallback*    m_callback;
    QString         m_serverIp;
    int             m_port;
    QTcpSocket      m_socket;
};

#endif // QTNET_H
