#include "workpiece.h"

#include <vector>

#include "gcode/GCommand.h"
#include "librecad/lib/engine/rs_vector.h"
#include "librecad/lib/engine/rs_line.h"
#include "librecad/lib/engine/rs_arc.h"

Workpiece::Workpiece(int id, WorkpieceData &data, RS_EntityContainer *container):
    id_(id), data_(data), container_(container) {

  //move_path_ = new GCodePath(Qt::yellow, 2);
  move_path_pen_.setColor(Qt::yellow);

  //cutting_path_ = new GCodePath(Qt::magenta, 2);
  cutting_path_pen_.setColor(Qt::magenta);
}

Workpiece::~Workpiece() {}

void Workpiece::AddLine(double x0, double y0, double x1, double y1,
                        const RS_Pen &pen) {

  RS_Vector start(x0, y0);
  RS_Vector end(x1, y1);
  RS_Line *line = new RS_Line(container_, start, end);
  line->setPen(pen);
  line->setLayerToActive();
  container_->addEntity(line);
}

void Workpiece::AddCutLine(double x0, double y0, double x1, double y1) {
  AddLine(x0, y0, x1, y1, cutting_path_pen_);
}

void Workpiece::AddMoveLine(double x0, double y0, double x1, double y1) {
  AddLine(x0, y0, x1, y1, move_path_pen_);
}

void Workpiece::AddArc(const Point_2D &start, const Point_2D &end,
                       const Point_2D &center, int direction) {

  RS_Vector s(start.x, start.y);
  RS_Vector e(end.x, end.y);
  RS_Vector c(center.x, center.y);

  RS_ArcData arc_data(RS_Vector(false), 0.0, 2.*M_PI, 0.0, direction);
  arc_data.center = c;
  arc_data.radius = c.distanceTo(s);
  arc_data.angle1 = arc_data.center.angleTo(s);
  arc_data.angle2 = arc_data.center.angleTo(e);


  RS_Arc *arc = new RS_Arc(container_, arc_data);
  arc->setPen(cutting_path_pen_);
  arc->setLayerToActive();
  container_->addEntity(arc);
}

void Workpiece::Draw() {
  std::vector<GCommand> &gcodes = data_.gcodes_;
  for (std::size_t i = 0; i < gcodes.size(); i++) {
    const GCommand &cur_cmd = gcodes[i];
    switch (cur_cmd.name_) {
      case G00:
        AddMoveLine(cur_cmd.x0_, cur_cmd.y0_, cur_cmd.x_, cur_cmd.y_);
        break;
      case G01:
        AddCutLine(cur_cmd.x0_, cur_cmd.y0_, cur_cmd.x_, cur_cmd.y_);
        break;
      case G02:
      case G03:
        {
          Point_2D start = { cur_cmd.x0_, cur_cmd.y0_ };
          Point_2D end = { cur_cmd.x_, cur_cmd.y_ };
          Point_2D center = { cur_cmd.i_, cur_cmd.j_ };
          AddArc(start, end, center, cur_cmd.name_ == G03 ? 0 : 1);
        }
        break;
      default:
        break;
    }
  }
}
