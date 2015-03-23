#-------------------------------------------------
#
# Project created by QtCreator 2015-03-23T15:48:38
#
#-------------------------------------------------

QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = Starlight
TEMPLATE = app

QMAKE_CXXFLAGS += -std=c++11 \
    -pedantic-errors

SOURCES += main.cpp\
        mainwindow.cpp

HEADERS  += mainwindow.h

FORMS    += mainwindow.ui
