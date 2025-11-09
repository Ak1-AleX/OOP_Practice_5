QT += widgets core

CONFIG += c++17

TARGET = PolynomGUI
TEMPLATE = app

macx {
    CONFIG += app_bundle
}

SOURCES += \
    src/main.cpp \
    src/mainwindow.cpp \
    src/array.cpp \
    src/complex.cpp \
    src/polynom.cpp

HEADERS += \
    src/mainwindow.h \
    src/array.h \
    src/complex.h \
    src/polynom.h \
    src/number.h

FORMS += \
    src/mainwindow.ui
