#-------------------------------------------------
#
# Project created by QtCreator 2013-04-07T11:59:19
#
#-------------------------------------------------

QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = GuiApplication
TEMPLATE = app


SOURCES += main.cpp\
        GuiApplication.cpp \
    User.cpp \
    Message.cpp

HEADERS  += GuiApplication.h \
    INetworkAdapter.h \
    User.h \
    Message.h

FORMS    += GuiApplication.ui
