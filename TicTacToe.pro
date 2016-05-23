#-------------------------------------------------
#
# Project created by QtCreator 2016-03-13T13:26:33
#
#-------------------------------------------------

QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = TicTacToe
TEMPLATE = app

CONFIG += c++11
QMAKE_CXXFLAGS += -std=c++11

SOURCES += main.cpp\
        mainwindow.cpp \
    tickdialog.cpp \
    player.cpp \
    board.cpp \
    game.cpp \
    humanplayer.cpp \
    computerplayer.cpp \
    cell.cpp \
    playerselectdialog.cpp \
    playersnamedialog.cpp

HEADERS  += mainwindow.h \
    tickdialog.h \
    player.h \
    board.h \
    game.h \
    humanplayer.h \
    computerplayer.h \
    libtic.h \
    cell.h \
    playerselectdialog.h \
    playersnamedialog.h

RESOURCES += \
    resources.qrc

DISTFILES +=
