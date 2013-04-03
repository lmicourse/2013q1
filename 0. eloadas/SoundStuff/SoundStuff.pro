TEMPLATE = app
CONFIG += console
CONFIG -= app_bundle
CONFIG -= qt

QMAKE_CXXFLAGS += -std=c++11

INCLUDEPATH += lib/

SOURCES += \
    src/SoundSample.cpp \
    src/morsetext.cpp \
    src/main.cpp \
    lib/fft/fft.cpp \
    lib/fft/complex.cpp

HEADERS += \
    src/types.h \
    src/SoundSample.h \
    src/morsetext.h \
    lib/fft/fft.h \
    lib/fft/complex.h
