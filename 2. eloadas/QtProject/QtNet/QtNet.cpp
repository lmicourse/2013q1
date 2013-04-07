#include <QDebug>
#include "QtNet.h"

QtNet::QtNet(QString serverIp, int port)
    : m_callback(NULL)
    , m_serverIp(serverIp)
    , m_port(port)
    , m_socket()
{}

void QtNet::connect()
{
    if (m_callback == NULL)
    {
        qDebug() << "Net callback is not set";
        return;
    }

    m_socket.connectToHost(m_serverIp, m_port);
    qDebug() << "Connected to server" << m_serverIp << ":" << m_port;
}

void QtNet::close()
{
    m_socket.close();
}

void QtNet::setCallback(NetCallback& callback) {
    m_callback = &callback;
}

void QtNet::sendPing(int selfId, std::string selfName)
{
    sendPacket("PING", selfId, QString::fromStdString(selfName));
}

void QtNet::sendMessage(int selfId, std::string message)
{
    sendPacket("MSG", selfId, QString::fromStdString(message));
}

void QtNet::sendPacket(QString type, int selfId, QString selfName)
{
    if (m_socket.isWritable())
    {
        QString packet = QString("%1 %2 %3\n").arg(type).arg(selfId).arg(selfName);
        m_socket.write(packet.toAscii());
        qDebug() << "Sent" << type << "packet";
    }
}
