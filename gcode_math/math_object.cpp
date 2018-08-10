#include "math_object.h"

#include <math.h>

#include "ecnc2math.h"

double CenterAngle(const Point_2D &point, const Point_2D &center) {
  Point_2D op = {point.x - center.x, point.y - center.y};
  return CenterAngle(op);
}

double CenterAngle(const Point_2D &vec_oa) {
  Point_2D vec_ox = {3, 0};
  double sign = 1;
  double cos_angle = (vec_oa.x * vec_ox.x + vec_oa.y * vec_ox.y) /
      (sqrt(vec_oa.x * vec_oa.x + vec_oa.y * vec_oa.y)
      * sqrt(vec_ox.x * vec_ox.x + vec_ox.y * vec_ox.y));

  if (IsLesserEqual(cos_angle, -1)) {
    cos_angle = -1;
  }
  if (IsGreaterEqual(cos_angle, 1)) {
    cos_angle = 1;
  }
  if (IsGreaterEqual(vec_oa.y,0)) {
    sign = -1;
  } else {
    sign = 1;
  }
  double angle = acos(cos_angle) * 180 / PI * sign;
  angle = IsGreaterEqual(angle, 0) ? angle : 360 + angle;
  return angle;
}

double SpanCenterAngle(const Point_2D &start_pos, const Point_2D &end_pos,
                       const Point_2D &center, int cw_ccw) {

  double start_ang = CenterAngle(start_pos, center);
  double end_ang = CenterAngle(end_pos, center);
  return SpanCenterAngle(start_ang, end_ang, cw_ccw);
}

double SpanCenterAngle(double start_angle, double end_angle, int cw_ccw) {
  double span_ang = end_angle - start_angle;
  if (cw_ccw) { // clockwise
    if (IsLesser(span_ang,0) || IsEqual(span_ang, 0)) {
      span_ang += 360;
    }
  } else { // counter-clockwise
    if (IsGreater(span_ang ,0) || IsEqual(span_ang, 0)) {
      span_ang -= 360;
    }
  }
  return span_ang;
}

double RoundAngle(double angle) {
  if (IsLesser(angle, 0)) {
    double n = ceil(angle / -360);
    angle -= (-360 * n);
  } else if (IsGreater(angle, 360)) {
    angle = fmod(angle, 360);
  }
  return angle;
}
