#-------------------------------------------------
#
# Project created by QtCreator 2016-12-17T13:45:02
#
#-------------------------------------------------

QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = saolei
TEMPLATE = app


SOURCES += main.cpp\
        mainwindow.cpp \
    myscene.cpp \
    myitem.cpp \
    myscenemain.cpp \
    myitemmain.cpp

HEADERS  += mainwindow.h \
    myscene.h \
    myitem.h \
    myscenemain.h \
    myitemmain.h

FORMS    += mainwindow.ui

RESOURCES += \
    pic.qrc
