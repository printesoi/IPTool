#-------------------------------------------------
#
# Project created by QtCreator 2012-10-26T21:32:12
#
#-------------------------------------------------

QT       += core gui
QT       -= console

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = IPTool
TEMPLATE = app

CONFIG += debug

SOURCES += main.cpp\
        mainwindow.cpp\
        ipv4.cpp\
        clickablebit.cpp\
        ipbyte.cpp\
        inputfield.cpp

HEADERS  += mainwindow.h\
    ipv4.h\
    clickablebit.h\
    ipbyte.h\
    inputfield.h

HEADERS += \
    logarea.h

SOURCES += \
    logarea.cpp
