#include "Message.h"

Message::Message()
    : m_user()
    , m_message()
{}

Message::Message(const User &user, QString message)
    : m_user(user)
    , m_message(message)
{}

const User& Message::user() const
{
    return m_user;
}

QString Message::message() const
{
    return m_message;
}
