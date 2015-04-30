#-------------------------------------------------
#
# Project created by QtCreator 2015-04-30T21:02:31
#
#-------------------------------------------------

QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = XTool
TEMPLATE = app


SOURCES += main.cpp\
        xtools.cpp

HEADERS  += xtools.h

FORMS    += xtools.ui

RESOURCES += \
    drawables.qrc \
    tools.qrc

QMAKE_CXXFLAGS += -fpermissive
