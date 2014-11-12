#-------------------------------------------------
#
# Project created by QtCreator 2014-11-06T15:08:23
#
#-------------------------------------------------

QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = IntelliGraph
TEMPLATE = app


SOURCES += main.cpp\
        mainwindow.cpp\
        workspace.cpp \
    colour.cpp \
    node.cpp

HEADERS  += mainwindow.h\
         workspace.h \
    colour.h \
    node.h

FORMS    += mainwindow.ui
