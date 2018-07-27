#include "gcodeplaner.h"

#include <math.h>

#include "ui_gcodeplaner.h"

#include "gcode_math/ecnc2math.h"

GCodePlaner::GCodePlaner(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::GCodePlaner) {
    ui->setupUi(this);
}

GCodePlaner::~GCodePlaner() {
    delete ui;
}

double GCodePlaner::VectorLengthSquare(const Point_2D &vec) {
  return pow(vec.x, 2) + pow(vec.y, 2);
}

/// arc C0
/// circle C1
Point_2D GCodePlaner::IntersectPoint(const GCodeArc &arc,
                                     const GCodeCircle &circle) {

  Point_2D u_vector = {circle.center.x - arc.center.x,
                       circle.center.y - arc.center.y};

  Point_2D v_vector = {u_vector.y, -u_vector.x};

  double s = 0.5 * ((pow(arc.r,2) - pow(circle.r,2)) / VectorLengthSquare(u_vector) + 1);
  double t = sqrt(pow(arc.r, 2) / VectorLengthSquare(u_vector) - pow(s, 2));

  Point_2D a = {arc.center.x + s * u_vector.x + t * v_vector.x,
                arc.center.y + s * u_vector.y + t * v_vector.y};

  if (PointOnArc(a, arc)) {
    return a;
  }

  Point_2D b = {arc.center.x + s * u_vector.x - t * v_vector.x,
                arc.center.y + s * u_vector.y - t * v_vector.y};

  if (PointOnArc(b, arc)) {
    return b;
  }

  Point_2D default_p = {0, 0};
  return default_p;
}


bool GCodePlaner::PointOnArc(const Point_2D &point, const GCodeArc &arc) {
  Point_2D start_to_end = {arc.end_point.x - arc.start_point.x,
                           arc.end_point.y - arc.start_point.y};

  Point_2D point_to_start = {point.x - arc.start_point.x,
                             point.y - arc.start_point.y};

  double ret = VectorDot(point_to_start, GetDotPerpVector(start_to_end));
  if (IsZero(ret) || IsGreater(ret, 0)) {
    return true;
  } else {
    return false;
  }
}

Point_2D GCodePlaner::GetDotPerpVector(const Point_2D &vec) {
  Point_2D dot_perp_vec = {vec.y, -vec.x};
  return dot_perp_vec;
}

Point_2D GCodePlaner::IntersectPoint(const GCodeLine &line,
                                     const GCodeCircle &circle) {

  Point_2D d_vector = GetDVector(line);
  Point_2D delta = {line.start_point.x - circle.center.x,
                    line.start_point.y - circle.center.y};

  double lower_delta = pow(VectorDot(d_vector, delta), 2) - \
      VectorLengthSquare(d_vector) * (VectorLengthSquare(delta) - pow(circle.r, 2));

  double t = 0;
  Point_2D point = {0, 0};
  if (IsEqual(lower_delta, 0)) {
    t = -VectorDot(d_vector, delta) / VectorLengthSquare(d_vector);
    point.x = line.start_point.x + t * d_vector.x;
    point.y = line.start_point.y + t * d_vector.y;
  } else if (IsGreater(lower_delta, 0)) {
    double t1 = (-VectorDot(d_vector, delta) + sqrt(lower_delta)) / VectorLengthSquare(d_vector);
    double t2 = (-VectorDot(d_vector, delta) - sqrt(lower_delta)) / VectorLengthSquare(d_vector);
    if (ValueInZeroToOne(t1)) {
      point.x = line.start_point.x + t1 * d_vector.x;
      point.y = line.start_point.y + t1 * d_vector.y;
    } else if (ValueInZeroToOne(t2)){
      point.x = line.start_point.x + t2 * d_vector.x;
      point.y = line.start_point.y + t2 * d_vector.y;
    }
  }
  return point;
}

int GCodePlaner::ValueInZeroToOne(double value) {
  return IsZero(value) || \
         (IsGreater(value, 0) && IsLesser(value, 1)) || \
         IsEqual(value, 1);
}

Point_2D GCodePlaner::GetDVector(const GCodeLine &line) {
  return GetDVector(line.start_point, line.end_point);
}

Point_2D GCodePlaner::GetDVector(const Point_2D &start_point,
                                 const Point_2D &end_point) {

  Point_2D d = {end_point.x - start_point.x, end_point.y - start_point.y};
  return d;
}

double GCodePlaner::VectorDot(const Point_2D &vec_a, const Point_2D &vec_b) {
  return vec_a.x * vec_b.x + vec_a.y * vec_b.y;
}

