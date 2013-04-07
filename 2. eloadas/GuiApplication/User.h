#ifndef USER_H
#define USER_H

#include <QString>

class User
{
public:
    User(int id, QString name);

public:
    int id() const;
    QString name() const;

private:
    int m_id;
    QString m_name;
};

#endif // USER_H
