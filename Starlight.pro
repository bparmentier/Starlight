#-------------------------------------------------
#
# Project created by QtCreator 2015-03-23T15:48:38
#
#-------------------------------------------------

QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = Starlight
TEMPLATE = app

CONFIG += c++11

LIBS += -L./staticlib/

win32 {
QMAKE_CXXFLAGS += -U__STRICT_ANSI__
LIBS += -lstarlight_win32
}

unix {
LIBS += -lstarlight_lin64
}

SOURCES += main.cpp\
        mainwindowstarlight.cpp \
    dialogconfig.cpp \
    starlight/level.cpp \
    observateurstarlight.cpp

HEADERS  += mainwindowstarlight.h \
    dialogconfig.h \
    geometry/circle.h \
    geometry/line.h \
    geometry/misc.h \
    geometry/point2dd.h \
    geometry/rectangle.h \
    geometry/segment.h \
    misc/approximativecomparison.h \
    o_sdo/observateur.h \
    o_sdo/sujetdobservation.h \
    starlight/bomb.h \
    starlight/crystal.h \
    starlight/lens.h \
    starlight/level.h \
    starlight/lightmodifier.h \
    starlight/lightray.h \
    starlight/mirror.h \
    starlight/sourceoflight.h \
    starlight/target.h \
    starlight/wall.h \
    starlight/wavelength.h \
    observateurstarlight.h

FORMS    += mainwindowstarlight.ui \
    dialogconfig.ui
