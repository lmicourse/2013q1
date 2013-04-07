#include "GuiApplication.h"
#include "LoopbackNetworkAdapter.h"
#include "User.h"
#include <QApplication>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    LoopbackNetworkAdapter dna;
    User me(777, "User");
    GuiApplication w(me, dna);
    w.show();

    return a.exec();
}
