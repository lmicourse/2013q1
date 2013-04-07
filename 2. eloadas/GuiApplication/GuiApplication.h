#ifndef GUIAPPLICATION_H
#define GUIAPPLICATION_H

#include <QWidget>

class INetworkAdapter;
class User;
class Message;

namespace Ui {
class GuiApplication;
}

class GuiApplication : public QWidget
{
    Q_OBJECT
    
public:
    explicit GuiApplication(const User& user, INetworkAdapter& networkAdapter, QWidget *parent = 0);
    ~GuiApplication();

signals:
    void login(const User& user);
    void logout(const User& user);
    void sendMessage(const Message &message);

public slots:
    void onUserLogin(const User& user);
    void onUserLogout(const User& user);
    void onMessageReceived(const Message& message);

private slots:
    void on_connectButton_clicked(bool checked);

private:
    void connectNetworkSignals();

private:
    Ui::GuiApplication *ui;
    const User&         m_user;
    INetworkAdapter&    m_networkAdapter;

};

#endif // GUIAPPLICATION_H
