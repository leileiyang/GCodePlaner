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
    shapemonitor.cpp \
    workpiece.cpp \
    workpiecedata.cpp \
    neomath/neomath.cpp \
    neomath/ecnc2math.c \
    torch.cpp

HEADERS  += gcodeplaner.h \
    gcodepath.h \
    gcode/GCodeParser.h \
    gcode/GCommand.h \
    shapemonitor.h \
    workpiece.h \
    workpiecedata.h \
    neomath/ecnc2math.h \
    neomath/neomath.h \
    gcode/GCodeDefine.h \
    torch.h

FORMS    += gcodeplaner.ui \
    shapemonitor.ui
