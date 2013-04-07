#include <QDebug>
#include <QStringList>
#include "QtNet.h"

const QString QtNet::kPingPacket = "PING";
const QString QtNet::kMessagePacket = "MSG";

QtNet::QtNet(QString serverIp, int port)
    : m_callback(NULL)
    , m_serverIp(serverIp)
    , m_port(port)
    , m_socket()
{
    QObject::connect(&m_socket, SIGNAL(readyRead()), this, SLOT(analyze()));
}

QtNet::~QtNet()
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
    if (m_socket.isOpen())
    {
        m_socket.close();
        qDebug() << "Close connection to " << m_serverIp;
    }
}

void QtNet::setCallback(NetCallback& callback) {
    m_callback = &callback;
}

void QtNet::sendPing(int selfId, std::string selfName)
{
    sendPacket(kPingPacket, selfId, QString::fromStdString(selfName));
}

void QtNet::sendMessage(int selfId, std::string message)
{
    sendPacket(kMessagePacket, selfId, QString::fromStdString(message));
}

void QtNet::analyze()
{

    while ( m_socket.canReadLine() )
    {
        QString packet = m_socket.readLine().trimmed();

        if (packet.isEmpty())
        {
            continue;
        }

        //qDebug() << "Packet" << packet;

        QString type    = packet.section(" ", 0, 0);
        int id          = packet.section(" ", 1, 1).toInt();
        QString payload = packet.section(" ", 2);


        if (type == kPingPacket)
        {
            m_callback->onPing(id, payload.toStdString());
        }
        else if (type == kMessagePacket)
        {
            m_callback->onMessage(id, payload.toStdString());
        }
        else
        {
            qDebug() << "Unrecognisable packet" << packet;
        }
    }
}

void QtNet::sendPacket(QString type, int selfId, QString selfName)
{
    if (m_socket.isWritable())
    {
        QString packet = QString("%1 %2 %3\n").arg(type).arg(selfId).arg(selfName);
        m_socket.write(packet.toAscii());
        //qDebug() << "Sent" << type << "packet";
    }
}
