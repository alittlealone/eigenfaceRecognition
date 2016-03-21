#-------------------------------------------------
#
# Project created by QtCreator 2016-03-21T21:14:48
#
#-------------------------------------------------

QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = UIDesignByDraggingInQt
TEMPLATE = app


SOURCES += main.cpp\
        mainwindow.cpp \
    video.cpp \
    picture.cpp \
    camera.cpp \
    database.cpp

HEADERS  += mainwindow.h \
    video.h \
    picture.h \
    camera.h \
    database.h

FORMS    += mainwindow.ui \
    video.ui \
    picture.ui \
    camera.ui \
    database.ui
