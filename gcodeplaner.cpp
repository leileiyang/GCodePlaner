#include "gcodeplaner.h"

#include "ui_gcodeplaner.h"

#include <QtGui/QFileDialog>

#include "gcode/GCodeParser.h"

GCodePlaner::GCodePlaner(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::GCodePlaner) {

    ui->setupUi(this);
}

GCodePlaner::~GCodePlaner() {
    delete ui;
}

void GCodePlaner::on_actionOpen_triggered()
{
  QString file_name = QFileDialog::getOpenFileName(this, tr("Open File"),
      "/home/leiyang/smbdemo");

  workpiece_data_.Clear();
  scene_.clear();
  GCodeParser gcode_parser(workpiece_data_);
  gcode_parser.ParseGCodeFromFile(file_name.toStdString());

  Workpiece workpiece(0, workpiece_data_);
  workpiece.Draw();
  workpiece.AddToScene(&scene_);
  ui->shape_monitor_->setScene(&scene_);
  ui->shape_monitor_->setSceneRect(workpiece.WorkpieceSize());
}

void GCodePlaner::on_actionXMirror_triggered()
{
  workpiece_data_.XMirror();
  scene_.clear();
  Workpiece workpiece(0, workpiece_data_);
  workpiece.Draw();
  workpiece.AddToScene(&scene_);
  ui->shape_monitor_->setSceneRect(workpiece.WorkpieceSize());
}

void GCodePlaner::on_actionYMirror_triggered()
{
  workpiece_data_.YMirror();
  scene_.clear();
  Workpiece workpiece(0, workpiece_data_);
  workpiece.Draw();
  workpiece.AddToScene(&scene_);
  ui->shape_monitor_->setSceneRect(workpiece.WorkpieceSize());
}

void GCodePlaner::on_actionRotate_triggered()
{
  workpiece_data_.Rotate(30);
  scene_.clear();
  Workpiece workpiece(0, workpiece_data_);
  workpiece.Draw();
  workpiece.AddToScene(&scene_);
  ui->shape_monitor_->setSceneRect(workpiece.WorkpieceSize());
}
