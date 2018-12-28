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
    gcode/GCodeParser.cpp \
    gcode/GCommand.cpp \
    gcode_math/ecnc2math.c \
    gcode_math/math_object.cpp \
    shapemonitor.cpp \
    pathmanager.cpp \
    workpiece.cpp

HEADERS  += gcodeplaner.h \
    gcodepath.h \
    gcode/GCodeParser.h \
    gcode/GCommand.h \
    gcode_math/ecnc2math.h \
    gcode_math/math_object.h \
    shapemonitor.h \
    pathmanager.h \
    workpiece.h

FORMS    += gcodeplaner.ui \
    shapemonitor.ui
