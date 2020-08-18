#include "gcodeplaner.h"

#include "ui_gcodeplaner.h"

#include <QFileDialog>

#include "gcode/GCodeParser.h"
#include "librecad/actions/rs_actiondefault.h"
#include "librecad/lib/engine/rs_line.h"
#include "rs_arc.h"
#include "rs_actionzoomauto.h"
#include "lc_actiongroupmanager.h"
#include "lc_actionfactory.h"
#include "lc_widgetfactory.h"
#include "qg_graphicview.h"

GCodePlaner::GCodePlaner(QWidget *parent) :
    QMainWindow(parent),
    ag_manager_(new LC_ActionGroupManager(this)),
    ui(new Ui::GCodePlaner),
    action_handler_(new QG_ActionHandler(this)) {

    ui->setupUi(this);

    document_ = new RS_Graphic();
    document_->newDoc();

    graphic_view_ = new QG_GraphicView(ui->centralWidget, 0, document_);
    graphic_view_->setObjectName(QStringLiteral("graphic_view_"));

    graphic_view_->setAntialiasing(false);
    graphic_view_->setCursorHiding(false);
    graphic_view_->addScrollbars();

    ui->horizontalLayout->addWidget(graphic_view_);

    action_handler_->setView(graphic_view_);
    action_handler_->setDocument(document_);


    LC_ActionFactory a_factory(this, action_handler_);
    a_factory.using_theme = false;
    a_factory.fillActionContainer(a_map_, ag_manager_);

    LC_WidgetFactory widget_factory(this, a_map_, ag_manager_);
    widget_factory.createStandardToolbars(action_handler_);
}

GCodePlaner::~GCodePlaner() {
  delete ui;
  delete document_;
}

void GCodePlaner::on_actionOpen_triggered()
{
  QString file_name = QFileDialog::getOpenFileName(this, tr("Open File"),
      "/home/leiyang/smbdemo");

  workpiece_data_.Clear();
  GCodeParser gcode_parser(workpiece_data_);
  gcode_parser.ParseGCodeFromFile(file_name.toStdString());

  Workpiece workpiece(0, workpiece_data_, document_);
  workpiece.Draw();
  graphic_view_->redraw(RS2::RedrawDrawing);
}

void GCodePlaner::on_actionXMirror_triggered()
{
  workpiece_data_.XMirror();
  Workpiece workpiece(0, workpiece_data_, document_);
  workpiece.Draw();
}

void GCodePlaner::on_actionYMirror_triggered()
{
  workpiece_data_.YMirror();
  Workpiece workpiece(0, workpiece_data_, document_);
  workpiece.Draw();
}

void GCodePlaner::on_actionRotate_triggered()
{
  workpiece_data_.Rotate(30);
  Workpiece workpiece(0, workpiece_data_, document_);
  workpiece.Draw();
}

void GCodePlaner::on_actionRestore_triggered()
{
  RS_Line *line = new RS_Line(document_, RS_Vector(0, 0), RS_Vector(10, 10));
  line->setLayerToActive();
  line->setPenToActive();
  document_->addEntity(line);

  RS_Vector s(10, 0);
  RS_Vector e(0, 10);
  RS_Vector c(0, 0);
  RS_ArcData arc_data(RS_Vector(false), 0.0, 2.*M_PI, 0.0, true);
  arc_data.center = c;
  arc_data.radius = c.distanceTo(s);
  arc_data.angle1 = arc_data.center.angleTo(s);
  arc_data.angle2 = arc_data.center.angleTo(e);

  RS_Arc *arc = new RS_Arc(document_, arc_data);
  document_->addEntity(arc);

  graphic_view_->redraw(RS2::RedrawDrawing);
}
