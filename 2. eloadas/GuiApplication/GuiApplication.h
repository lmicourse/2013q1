#ifndef GUIAPPLICATION_H
#define GUIAPPLICATION_H

#include <QWidget>

namespace Ui {
class GuiApplication;
}

class GuiApplication : public QWidget
{
    Q_OBJECT
    
public:
    explicit GuiApplication(QWidget *parent = 0);
    ~GuiApplication();
    
private:
    Ui::GuiApplication *ui;
};

#endif // GUIAPPLICATION_H
