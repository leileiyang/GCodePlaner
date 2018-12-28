#ifndef MATH_OBJECT_H
#define MATH_OBJECT_H

struct Point_2D {
  double x;
  double y;
};

struct GCodeLine {
  Point_2D start_point;
  Point_2D end_point;
};

struct GCodeCircle {
  Point_2D center;
  double r;
};

struct GCodeArc {
  Point_2D start_point;
  Point_2D end_point;
  Point_2D center;
  double r;
};


double CenterAngle(const Point_2D &point, const Point_2D &center);
double CenterAngle(const Point_2D &vec_oa);

double SpanCenterAngle(double start_angle, double end_angle, int cw_ccw);
double SpanCenterAngle(const Point_2D &start_pos, const Point_2D &end_pos,
                       const Point_2D &center, int cw_ccw);

/// round angle to [0, 360]
double RoundAngle(double angle);
/// angle unit: degree
void RotatePoint(double &x, double &y, double angle);

#endif // MATH_OBJECT_H

