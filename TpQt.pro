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
    dialognewb.cpp \
    dialognewa.cpp \
    dialogcommitnew.cpp \
    annonce.cpp \
    mainwindow.cpp \
    dialogrecherche.cpp \
    objeta.cpp

HEADERS  += mainwindow.h \
    possession.h \
    dialognewb.h \
    dialognewa.h \
    dialogcommitnew.h \
    annonce.h \
    dialogrecherche.h \
    objeta.h

FORMS    += mainwindow.ui \
    dialognewA.ui \
    dialognewB.ui \
    dialogcommitnew.ui \
    annonce.ui \
    dialogrecherche.ui

DISTFILES +=
RESOURCES = icones.qrc
