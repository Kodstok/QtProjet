#-------------------------------------------------
#
# Project created by QtCreator 2016-03-23T14:05:13
#
#-------------------------------------------------

QT += widgets
QT       += core gui xml

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = TpQt
TEMPLATE = app


SOURCES += main.cpp\
        mainwindow.cpp \
    dialognewb.cpp \
    dialognewa.cpp

HEADERS  += mainwindow.h \
    possession.h \
    dialognewb.h \
    dialognewa.h

FORMS    += mainwindow.ui \
    dialognewA.ui \
    dialognewB.ui
