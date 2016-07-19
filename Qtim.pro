#-------------------------------------------------
#
# Project created by QtCreator 2016-07-18T10:22:43
#
#-------------------------------------------------

QT       += core gui sql network

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = Qtim
TEMPLATE = app


SOURCES += main.cpp\
        login.cpp \
    mainwindow.cpp \
    server.cpp

HEADERS  += login.h \
    mainwindow.h \
    common.h \
    server.h \
    dboperation.h

FORMS    += login.ui \
    mainwindow.ui
