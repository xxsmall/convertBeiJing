#-------------------------------------------------
#
# Project created by QtCreator 2018-07-20T10:53:30
#
#-------------------------------------------------

QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = convertToBeiJing
TEMPLATE = app


SOURCES += main.cpp\
        mainwindow.cpp \
    xyzclass.cpp \
    dialogqixiang.cpp \
    dialogorbit.cpp \
    dialogxingli.cpp \
    dialogttcdata.cpp

HEADERS  += mainwindow.h \
    xyzclass.h \
    dialogqixiang.h \
    dialogorbit.h \
    datastruct.h \
    dialogxingli.h \
    dialogttcdata.h

FORMS    += mainwindow.ui \
    dialogqixiang.ui \
    dialogorbit.ui \
    dialogxingli.ui \
    dialogttcdata.ui
