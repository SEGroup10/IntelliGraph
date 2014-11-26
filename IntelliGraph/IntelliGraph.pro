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
    node.cpp \
    edge.cpp \
    popup.cpp \
    popupedge.cpp

HEADERS  += mainwindow.h\
         workspace.h \
    node.h \
    edge.h \
    nodetype.h \
    popup.h \
    popupedge.h \
    algorithminterface.h

FORMS    += mainwindow.ui \
    popup.ui \
    popupedge.ui

RESOURCES += \
    images.qrc
