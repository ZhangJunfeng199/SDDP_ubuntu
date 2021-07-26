#-------------------------------------------------
#
# Project created by QtCreator 2018-12-21T15:03:43
#
#-------------------------------------------------

QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = demo
TEMPLATE = app

INCLUDEPATH += ./lib/include
LIBS += -lzmq -ljsoncpp -lcanlib -lglog -lm -lQtGui  -lpthread

SOURCES += main.cpp\
        mainwindow.cpp \
    sddp.cpp

HEADERS  += mainwindow.h \
    sddp.h

FORMS    += mainwindow.ui
