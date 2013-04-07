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

    bool operator==(const User& other) const;

private:
    int m_id;
    QString m_name;
};

#endif // USER_H
