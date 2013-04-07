#ifndef MESSAGE_H
#define MESSAGE_H

#include <QString>

class Message
{
public:
    Message(int userId, QString message);

    int userId() const;
    QString message() const;

private:
    int m_userId;
    QString m_message;
};

#endif // MESSAGE_H
