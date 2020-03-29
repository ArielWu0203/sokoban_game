#-------------------------------------------------
#
# Project created by QtCreator 2020-02-21T17:36:08
#
#-------------------------------------------------

QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = sokoban
TEMPLATE = app


SOURCES += main.cpp\
        mainwindow.cpp \
    player.cpp \
    box.cpp \
    target.cpp

HEADERS  += mainwindow.h \
    player.h \
    box.h \
    target.h

FORMS    += mainwindow.ui

DISTFILES +=

RESOURCES += \
    resource.qrc
