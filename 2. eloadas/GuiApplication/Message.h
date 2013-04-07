#ifndef MESSAGE_H
#define MESSAGE_H

#include <QMetaType>
#include <QString>
#include "User.h"

class Message
{
public:
    Message();
    Message(const User& user, QString message);

    const User &user() const;
    QString message() const;

private:
    User m_user;
    QString m_message;
};

Q_DECLARE_METATYPE(Message)

#endif // MESSAGE_H
