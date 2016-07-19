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
<<<<<<< HEAD
    server.h
=======
    dboperation.h
>>>>>>> 8f4e0f6977de7f5ee781cada56845297eac885d1

FORMS    += login.ui \
    mainwindow.ui
