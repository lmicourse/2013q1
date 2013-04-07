#include "Message.h"

Message::Message(int userId, QString message)
    : m_userId(userId)
    , m_message(message)
{}

int Message::userId() const
{
    return m_userId;
}

QString Message::message() const
{
    return m_message;
}
