#include "gcodeplaner.h"

#include "ui_gcodeplaner.h"

#include <QFileDialog>

#include "gcode/GCodeParser.h"
#include "librecad/actions/rs_actiondefault.h"
#include "librecad/lib/engine/rs_line.h"
#include "rs_arc.h"
#include "librecad/actions/rs_actionzoomauto.h"

GCodePlaner::GCodePlaner(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::GCodePlaner) {

    ui->setupUi(this);

    document_ = new RS_Graphic();
    document_->newDoc();

    ui->graphic_view_->setContainer(document_);
    ui->graphic_view_->setDefaultAction(new RS_ActionDefault(*document_, *(ui->graphic_view_)));
    document_->setGraphicView(ui->graphic_view_);

    ui->graphic_view_->setAntialiasing(false);
    ui->graphic_view_->setCursorHiding(false);
    ui->graphic_view_->addScrollbars();
}

GCodePlaner::~GCodePlaner() {
    delete ui;
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
  //ui->graphic_view_->redraw(RS2::RedrawDrawing);
  ui->graphic_view_->setCurrentAction(new RS_ActionZoomAuto(*document_, *(ui->graphic_view_)));
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

  ui->graphic_view_->redraw(RS2::RedrawDrawing);
}
