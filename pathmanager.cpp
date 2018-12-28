#include "pathmanager.h"

PathManager::PathManager(QObject *parent) : QObject(parent),
    move_path_(Qt::yellow, 2), cutting_path_(Qt::magenta, 2) {

  scene_ = new QGraphicsScene(this);
}

void PathManager::DrawGCode(const GCodeParser &gcode_parser) {
  for (std::size_t i = 0; i < gcode_parser.gcodes_.size(); i++) {
    const GCommand &cur_cmd = gcode_parser.gcodes_[i];
    switch (cur_cmd.name_) {
      case G00:
        move_path_.MoveTo(cur_cmd.x0_, cur_cmd.y0_);
        move_path_.AddLine(cur_cmd.x0_, cur_cmd.y0_, cur_cmd.x_, cur_cmd.y_);
        cutting_path_.MoveTo(cur_cmd.x_, cur_cmd.y_);
        break;
      case G01:
        cutting_path_.AddLine(cur_cmd.x0_, cur_cmd.y0_, cur_cmd.x_, cur_cmd.y_);
        break;
      case G02:
      case G03:
        {
          Point_2D start = { cur_cmd.x0_, cur_cmd.y0_ };
          Point_2D end = { cur_cmd.x_, cur_cmd.y_ };
          Point_2D center = { cur_cmd.i_, cur_cmd.j_ };
          cutting_path_.AddArc(start, end, center,
              cur_cmd.name_ == G02 ? 1 : 0);

        }
        break;
      default:
        break;
    }
  }
  scene_->addItem(&move_path_);
  scene_->addItem(&cutting_path_);
}
