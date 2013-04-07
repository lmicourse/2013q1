#ifndef QTNET_H
#define QTNET_H

#include "qtnet_global.h"
#include <QObject>
#include <QTcpSocket>
#include <QString>
#include <string>
#include "NetInterface.h"


class QTNETSHARED_EXPORT QtNet : public QObject, public NetInterface
{
    Q_OBJECT
public:
    QtNet(QString serverIp, int port);
    virtual ~QtNet();

    virtual void connect();
    virtual void close();

    virtual void setCallback(NetCallback& callback);
    virtual void sendPing(int selfId, std::string selfName);
    virtual void sendMessage(int selfId, std::string message);

private slots:
    void analyze();

private:
    void sendPacket(QString type, int selfId, QString selfName);

    static const QString kPingPacket;
    static const QString kMessagePacket;

private:
    NetCallback*    m_callback;
    QString         m_serverIp;
    int             m_port;
    QTcpSocket      m_socket;
};

#endif // QTNET_H
