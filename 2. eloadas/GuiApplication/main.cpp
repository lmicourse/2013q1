#include "GuiApplication.h"
#include <QApplication>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    GuiApplication w;
    w.show();
    
    return a.exec();
}
