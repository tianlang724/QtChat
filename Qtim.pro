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
    cdatabaseoperation.cpp\
    login.cpp \
    mainwindow.cpp \
    cmsgoperation.cpp \
    csoftwareconfig.cpp \
    cudpbase.cpp \
    server.cpp

HEADERS  += login.h \
    mainwindow.h \
    cmsgoperation.h \
    csoftwareconfig.h \
    cudpbase.h\
    server.h\
    cdatabaseoperation.h





FORMS    += login.ui \
    mainwindow.ui
