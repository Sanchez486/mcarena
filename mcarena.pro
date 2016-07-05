QT += core
QT -= gui

CONFIG += c++11

TARGET = mcarena
CONFIG += console
CONFIG -= app_bundle

TEMPLATE = app

SOURCES += main.cpp \
    battlegui.cpp \
    battlemodel.cpp \
    menugui.cpp \
    menumodel.cpp \
    selectiongui.cpp \
    selectionmodel.cpp

HEADERS += \
    inc/menugui.h \
    inc/selectiongui.h \
    inc/battlegui.h \
    inc/menumodel.h \
    inc/selectionmodel.h \
    inc/battlemodel.h \
    inc/game.h \
    inc/hero.h \
    inc/heroqueue.h \
    inc/herogroup.h \
    inc/player.h \
    inc/action.h
