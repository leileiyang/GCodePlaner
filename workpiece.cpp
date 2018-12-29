#include "workpiece.h"

#include <vector>

#include "gcode/GCommand.h"

Workpiece::Workpiece(int id, WorkpieceData &data, QObject *parent):
    QObject(parent), id_(id), data_(data), ownership_(true) {

  move_path_ = new GCodePath(Qt::yellow, 2);
  cutting_path_ = new GCodePath(Qt::magenta, 2);
  group_ = new QGraphicsItemGroup;
  group_->addToGroup(move_path_);
  group_->addToGroup(cutting_path_);
}

Workpiece::~Workpiece() {
  if (ownership_) {
    delete group_;
  }
}

void Workpiece::AddToScene(QGraphicsScene *scene) {
  scene->addItem(group_);
  ownership_ = false;
}

void Workpiece::RemoveFromScene(QGraphicsScene *scene) {
  scene->removeItem(group_);
  ownership_ = true;
}

void Workpiece::Draw() {
  std::vector<GCommand> &gcodes = data_.gcodes_;
  for (std::size_t i = 0; i < gcodes.size(); i++) {
    const GCommand &cur_cmd = gcodes[i];
    switch (cur_cmd.name_) {
      case G00:
        move_path_->MoveTo(cur_cmd.x0_, cur_cmd.y0_);
        move_path_->AddLine(cur_cmd.x0_, cur_cmd.y0_, cur_cmd.x_, cur_cmd.y_);
        cutting_path_->MoveTo(cur_cmd.x_, cur_cmd.y_);
        break;
      case G01:
        cutting_path_->AddLine(cur_cmd.x0_, cur_cmd.y0_, cur_cmd.x_, cur_cmd.y_);
        break;
      case G02:
      case G03:
        {
          Point_2D start = { cur_cmd.x0_, cur_cmd.y0_ };
          Point_2D end = { cur_cmd.x_, cur_cmd.y_ };
          Point_2D center = { cur_cmd.i_, cur_cmd.j_ };
          cutting_path_->AddArc(start, end, center,
              cur_cmd.name_ == G02 ? 1 : 0);

        }
        break;
      default:
        break;
    }
  }
}
