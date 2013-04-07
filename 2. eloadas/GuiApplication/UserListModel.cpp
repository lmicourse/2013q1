#include "UserListModel.h"

UserListModel::UserListModel(QObject *parent)
    : QAbstractListModel(parent)
    , m_elements()
{}

int UserListModel::rowCount(const QModelIndex &parent) const
{
    return m_elements.size();
}

QVariant UserListModel::data(const QModelIndex &index, int role) const
{
    if (role == Qt::DisplayRole && index.row()<m_elements.size())
    {
        return m_elements.at(index.row()).name();
    }
    return QVariant();
}

void UserListModel::addUser(const User &user)
{
    if ( ! m_elements.contains(user) )
    {
        m_elements.append(user);
        emit dataChanged(createIndex(0,0), createIndex(0, m_elements.size()));
    }
}

void UserListModel::removeUser(const User &user)
{
    if ( m_elements.removeAll(user) != 0 )
    {
        emit dataChanged(createIndex(0,0), createIndex(0, m_elements.size()));
    }
}
