#-------------------------------------------------
#
# Project created by QtCreator 2013-04-07T21:57:29
#
#-------------------------------------------------

QT       += network

QT       -= gui

TARGET = QtNet
TEMPLATE = lib

DEFINES += QTNET_LIBRARY

SOURCES += QtNet.cpp

HEADERS += QtNet.h\
        qtnet_global.h

unix:!symbian {
    maemo5 {
        target.path = /opt/usr/lib
    } else {
        target.path = /usr/lib
    }
    INSTALLS += target
}

INCLUDEPATH += $$PWD/../../include
