#-------------------------------------------------
#
# Project created by QtCreator 2014-11-06T15:08:23
#
#-------------------------------------------------

QT       += core gui
QT       += script

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = IntelliGraph
TEMPLATE = app

DESTDIR = $$PWD

SOURCES += main.cpp\
        mainwindow.cpp\
        workspace.cpp \
    node.cpp \
    edge.cpp \
    popup.cpp \
    popupedge.cpp \
    samplealgorithm.cpp

HEADERS  += mainwindow.h\
         workspace.h \
    node.h \
    edge.h \
    nodetype.h \
    popup.h \
    popupedge.h \
    algorithminterface.h \
    samplealgorithm.h

FORMS    += mainwindow.ui \
    popup.ui \
    popupedge.ui

RESOURCES += \
    images.qrc

INCLUDEPATH += $$PWD/algorithms
