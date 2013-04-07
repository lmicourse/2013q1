#include "User.h"

User::User(int id, QString name)
    : m_id(id)
    , m_name(name)
{}

int User::id() const
{
    return m_id;
}

QString User::name() const
{
    return m_name;
}

bool User::operator ==(const User &other) const
{
    return id() == other.id();
}
