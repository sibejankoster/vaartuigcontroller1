#-------------------------------------------------
#
# Project created by QtCreator 2013-02-06T18:59:48
#
#-------------------------------------------------

QT       += core gui
QT       += sql

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = vaartuigcontroller
TEMPLATE = app


SOURCES += main.cpp\
        mainwindow.cpp \
    canformat.cpp \
    packet.cpp \
    gps.cpp \
    file.cpp \
    logfile.cpp \
    dynamics.cpp

HEADERS  += mainwindow.h \
    canformat.h \
    packet.h \
    gps.h \
    file.h \
    logfile.h \
    dynamics.h

FORMS    += mainwindow.ui
