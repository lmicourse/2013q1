#include "GuiApplication.h"
#include "ui_GuiApplication.h"

GuiApplication::GuiApplication(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::GuiApplication)
{
    ui->setupUi(this);
}

GuiApplication::~GuiApplication()
{
    delete ui;
}
