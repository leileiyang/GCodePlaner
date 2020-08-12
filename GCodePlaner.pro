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
    librecad/lib/information \
    librecad/lib/filters \
    librecad/lib/modification \
    librecad/lib/creation \
    librecad/actions \
    librecad/cmd \
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
    librecad/actions/rs_actionzoomin.cpp \
    librecad/lib/gui/rs_eventhandler.cpp \
    librecad/lib/actions/rs_snapper.cpp \
    librecad/lib/engine/rs_entitycontainer.cpp \
    librecad/actions/rs_actionzoomscroll.cpp \
    librecad/actions/rs_actionzoompan.cpp \
    librecad/lib/engine/rs_entity.cpp \
    librecad/lib/engine/rs_arc.cpp \
    librecad/lib/engine/rs_block.cpp \
    librecad/lib/engine/rs_circle.cpp \
    librecad/lib/engine/rs_ellipse.cpp \
    librecad/lib/engine/rs_insert.cpp \
    librecad/lib/engine/rs_layer.cpp \
    librecad/lib/engine/rs_line.cpp \
    librecad/lib/engine/rs_mtext.cpp \
    librecad/lib/engine/rs_point.cpp \
    librecad/lib/engine/rs_polyline.cpp \
    librecad/lib/engine/rs_text.cpp \
    librecad/lib/math/lc_quadratic.cpp \
    librecad/lib/engine/rs_undoable.cpp \
    librecad/lib/engine/rs_atomicentity.cpp \
    librecad/lib/engine/rs_document.cpp \
    librecad/lib/engine/rs_layerlist.cpp \
    librecad/lib/engine/rs_undo.cpp \
    librecad/lib/information/rs_information.cpp \
    librecad/lib/engine/lc_splinepoints.cpp \
    librecad/lib/engine/rs_constructionline.cpp \
    librecad/lib/engine/rs_blocklist.cpp \
    librecad/lib/engine/rs_dimension.cpp \
    librecad/lib/engine/rs_solid.cpp \
    librecad/lib/engine/rs_spline.cpp \
    librecad/lib/gui/rs_dialogfactory.cpp \
    librecad/lib/gui/rs_linetypepattern.cpp \
    librecad/lib/engine/lc_hyperbola.cpp \
    librecad/lib/engine/rs_font.cpp \
    librecad/lib/engine/rs_fontlist.cpp \
    librecad/ui/qg_graphicview.cpp \
    librecad/lib/engine/rs_undocycle.cpp \
    librecad/lib/engine/rs_system.cpp \
    librecad/lib/information/rs_locale.cpp \
    librecad/actions/rs_actiondefault.cpp \
    librecad/actions/rs_actionmodifydelete.cpp \
    librecad/actions/rs_actionselectsingle.cpp \
    librecad/actions/rs_actionzoomauto.cpp \
    librecad/lib/actions/rs_preview.cpp \
    librecad/lib/actions/rs_previewactioninterface.cpp \
    librecad/lib/modification/rs_modification.cpp \
    librecad/cmd/rs_commands.cpp \
    librecad/lib/engine/rs_overlaybox.cpp \
    librecad/lib/modification/rs_selection.cpp \
    librecad/lib/creation/rs_creation.cpp \
    librecad/lib/engine/lc_undosection.cpp \
    librecad/lib/engine/rs_image.cpp \
    librecad/lib/engine/rs_clipboard.cpp \
    librecad/lib/engine/rs_overlayline.cpp

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
    librecad/actions/rs_actionzoomin.h \
    librecad/lib/gui/rs_eventhandler.h \
    librecad/lib/gui/rs_commandevent.h \
    librecad/lib/actions/rs_snapper.h \
    librecad/lib/engine/rs_entitycontainer.h \
    librecad/lib/gui/rs_coordinateevent.h \
    librecad/actions/rs_actionzoomscroll.h \
    librecad/actions/rs_actionzoompan.h \
    librecad/lib/engine/rs_entity.h \
    librecad/lib/engine/rs_arc.h \
    librecad/lib/engine/rs_block.h \
    librecad/lib/engine/rs_circle.h \
    librecad/lib/engine/rs_ellipse.h \
    librecad/lib/engine/rs_insert.h \
    librecad/lib/engine/rs_layer.h \
    librecad/lib/engine/rs_line.h \
    librecad/lib/engine/rs_mtext.h \
    librecad/lib/engine/rs_point.h \
    librecad/lib/engine/rs_polyline.h \
    librecad/lib/engine/rs_text.h \
    librecad/lib/math/lc_quadratic.h \
    librecad/lib/engine/rs_undoable.h \
    librecad/lib/engine/rs_atomicentity.h \
    librecad/lib/engine/rs_document.h \
    librecad/lib/engine/rs_layerlist.h \
    librecad/lib/engine/rs_undo.h \
    librecad/lib/information/rs_information.h \
    librecad/lib/engine/lc_splinepoints.h \
    librecad/lib/engine/rs_constructionline.h \
    librecad/lib/engine/rs_blocklist.h \
    librecad/lib/engine/rs_dimension.h \
    librecad/lib/engine/rs_solid.h \
    librecad/lib/engine/rs_spline.h \
    librecad/lib/gui/rs_dialogfactory.h \
    librecad/lib/gui/rs_dialogfactoryadapter.h \
    librecad/lib/gui/rs_dialogfactoryinterface.h \
    librecad/lib/gui/rs_linetypepattern.h \
    librecad/lib/engine/lc_hyperbola.h \
    librecad/lib/engine/rs_font.h \
    librecad/lib/engine/rs_fontlist.h \
    librecad/ui/qg_graphicview.h \
    librecad/lib/filters/rs_filterinterface.h \
    librecad/lib/engine/rs_undocycle.h \
    librecad/lib/engine/rs_layerlistlistener.h \
    librecad/lib/engine/rs_blocklistlistener.h \
    librecad/lib/engine/rs_fontchar.h \
    librecad/lib/engine/rs_system.h \
    librecad/lib/information/rs_locale.h \
    librecad/actions/rs_actiondefault.h \
    librecad/actions/rs_actionmodifydelete.h \
    librecad/actions/rs_actionselectsingle.h \
    librecad/actions/rs_actionzoomauto.h \
    librecad/lib/actions/rs_preview.h \
    librecad/lib/actions/rs_previewactioninterface.h \
    librecad/lib/modification/rs_modification.h \
    librecad/cmd/rs_commands.h \
    librecad/lib/engine/rs_overlaybox.h \
    librecad/lib/modification/rs_selection.h \
    librecad/lib/creation/rs_creation.h \
    librecad/lib/engine/lc_undosection.h \
    librecad/lib/engine/rs_image.h \
    librecad/lib/engine/rs_clipboard.h \
    librecad/lib/engine/rs_overlayline.h

FORMS    += gcodeplaner.ui \
    shapemonitor.ui

unix:!macx: LIBS += -L$$PWD/../../../../usr/local/lib/ -lmuparser

INCLUDEPATH += $$PWD/../../../../usr/local/include
DEPENDPATH += $$PWD/../../../../usr/local/include

DISTFILES +=

RESOURCES += \
    librecad/res/ui/ui.qrc
