#-------------------------------------------------
#
# Project created by QtCreator 2016-01-08T23:59:11
#
#-------------------------------------------------

QT       += core gui multimedia multimediawidgets

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = OthelloPrototype
TEMPLATE = app


SOURCES += main.cpp\
        widget.cpp \
    newgamesettings.cpp \
    ai.cpp \
    savegame.cpp \
    loadgame.cpp

HEADERS  += widget.h \
    newgamesettings.h \
    ai.h \
    mhead.h \
    savegame.h \
    loadgame.h

FORMS    += widget.ui \
    newgamesettings.ui \
    savegame.ui \
    loadgame.ui

RESOURCES += \
    gameboard.qrc

RC_ICONS = appicon.ico
