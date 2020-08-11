#-------------------------------------------------
#
# Project created by QtCreator 2018-05-11T16:25:11
#
#-------------------------------------------------

QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = GCodePlaner
TEMPLATE = app

INCLUDEPATH += \
    librecad/lib/engine \
    librecad/lib/gui \
    librecad/lib/math \
    librecad/lib/debug \
    librecad/lib/actions \
    librecad/actions \
    librecad/ui/

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
    torch.cpp \
    librecad/lib/engine/rs.cpp \
    librecad/lib/engine/rs_color.cpp \
    librecad/lib/engine/rs_flags.cpp \
    librecad/lib/engine/rs_units.cpp \
    librecad/lib/engine/rs_vector.cpp \
    librecad/lib/gui/rs_grid.cpp \
    librecad/lib/gui/rs_graphicview.cpp \
    librecad/lib/math/rs_math.cpp \
    librecad/lib/debug/rs_debug.cpp \
    librecad/lib/engine/lc_rect.cpp \
    librecad/lib/engine/rs_settings.cpp \
    librecad/lib/gui/rs_painter.cpp \
    librecad/lib/gui/rs_painterqt.cpp \
    librecad/lib/gui/rs_pen.cpp \
    librecad/lib/engine/rs_graphic.cpp \
    librecad/lib/engine/rs_variabledict.cpp \
    librecad/lib/actions/rs_actioninterface.cpp \
    librecad/lib/engine/rs_undoable.cpp \
    librecad/lib/engine/rs_undocycle.cpp \
    librecad/actions/rs_actionzoomin.cpp \
    librecad/lib/gui/rs_eventhandler.cpp \
    librecad/lib/actions/rs_snapper.cpp \
    librecad/lib/engine/rs_entitycontainer.cpp

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
    torch.h \
    librecad/lib/engine/rs.h \
    librecad/lib/engine/rs_color.h \
    librecad/lib/engine/rs_flags.h \
    librecad/lib/engine/rs_units.h \
    librecad/lib/engine/rs_vector.h \
    librecad/lib/gui/qg_scrollbar.h \
    librecad/lib/gui/rs_grid.h \
    librecad/lib/gui/rs_graphicview.h \
    librecad/lib/math/rs_math.h \
    librecad/lib/debug/rs_debug.h \
    librecad/lib/engine/lc_rect.h \
    librecad/lib/engine/rs_settings.h \
    librecad/lib/gui/rs_painter.h \
    librecad/lib/gui/rs_painterqt.h \
    librecad/lib/gui/rs_pen.h \
    librecad/lib/engine/rs_graphic.h \
    librecad/lib/engine/rs_variable.h \
    librecad/lib/engine/rs_variabledict.h \
    librecad/lib/actions/rs_actioninterface.h \
    librecad/lib/engine/rs_undoable.h \
    librecad/lib/engine/rs_undocycle.h \
    librecad/actions/rs_actionzoomin.h \
    librecad/lib/gui/rs_eventhandler.h \
    librecad/lib/gui/rs_commandevent.h \
    librecad/lib/actions/rs_snapper.h \
    librecad/lib/engine/rs_entitycontainer.h \
    librecad/lib/gui/rs_coordinateevent.h

FORMS    += gcodeplaner.ui \
    shapemonitor.ui

unix:!macx: LIBS += -L$$PWD/../../../../usr/local/lib/ -lmuparser

INCLUDEPATH += $$PWD/../../../../usr/local/include
DEPENDPATH += $$PWD/../../../../usr/local/include
