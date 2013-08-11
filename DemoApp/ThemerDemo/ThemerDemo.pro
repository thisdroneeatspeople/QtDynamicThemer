#-------------------------------------------------
#
# Project created by QtCreator 2013-08-11T10:08:52
#
#-------------------------------------------------

QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = ThemerDemo
TEMPLATE = app


SOURCES += main.cpp\
        mainwindow.cpp

HEADERS  += mainwindow.h

FORMS    += mainwindow.ui


HEADERS += \
        ../../Themer/themer.h \
        ../../Themer/singleton.h \
        ../../Themer/singlethemer.h

SOURCES += \
        ../../Themer/themer.cpp \
        ../../Themer/singlethemer.cpp


INCLUDEPATH += ../../Themer/
