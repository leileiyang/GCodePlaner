#-------------------------------------------------
#
# Project created by QtCreator 2018-05-11T16:25:11
#
#-------------------------------------------------

QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = GCodePlaner
TEMPLATE = app


SOURCES += main.cpp\
        gcodeplaner.cpp \
    gcodepath.cpp \
    ecnc2math.c

HEADERS  += gcodeplaner.h \
    gcodepath.h \
    ecnc2math.h

FORMS    += gcodeplaner.ui
