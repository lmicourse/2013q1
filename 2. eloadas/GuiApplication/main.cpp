#include "GuiApplication.h"
#include "LoopbackNetworkAdapter.h"
#include "PingnetNetworkAdapater.h"
#include "User.h"
#include "Message.h"
#include "BoostNet.h"
#include <QApplication>

int main(int argc, char *argv[])
{
    qRegisterMetaType<User>();
    qRegisterMetaType<Message>();

    QApplication a(argc, argv);

    LoopbackNetworkAdapter adapter;

    //BoostNet net("127.0.0.1", 50002);
    //PingnetNetworkAdapater adapter(net);

    INetworkAdapter& iAdapter = adapter;

    User me(777, "User");
    GuiApplication w(me, iAdapter);

    w.show();

    return a.exec();
}
