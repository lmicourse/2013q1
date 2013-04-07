#ifndef USER_H
#define USER_H

#include <QMetaType>
#include <QString>

class User
{

public:
    User();
    User(int id, QString name);

public:
    int id() const;
    QString name() const;

    bool operator==(const User& other) const;
    bool operator<(const User& other) const;

private:
    int m_id;
    QString m_name;
};

Q_DECLARE_METATYPE(User)

#endif // USER_H
