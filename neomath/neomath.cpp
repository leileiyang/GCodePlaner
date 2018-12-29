#include "neomath.h"

#include "ecnc2math.h"

double CenterAngle(const Point_2D &point, const Point_2D &center) {
  Point_2D op = {point.x - center.x, point.y - center.y};
  return CenterAngle(op);
}

double CenterAngle(const Point_2D &vec_oa) {
  /*
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
  */

  if (IsEqual(vec_oa.x, 0) && IsEqual(vec_oa.y, 0)) {
    return 0;
  }
  double angle = -(float)(atan2((float)vec_oa.y, (float)vec_oa.x) * 180 / PI);
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

void RotatePoint(double &x, double &y, double angle) {
  double cos_theta = cos(angle * PI / 180);
  double sin_theta = sin(angle * PI / 180);
  double temp = x;
  x = x * cos_theta - y * sin_theta;
  y = y * cos_theta + temp * sin_theta;
}

double VectorLengthSquare(const Point_2D &vec) {
  return pow(vec.x, 2) + pow(vec.y, 2);
}

Point_2D GetDotPerpVector(const Point_2D &vec) {
  Point_2D dot_perp_vec = {vec.y, -vec.x};
  return dot_perp_vec;
}

double VectorDot(const Point_2D &vec_a, const Point_2D &vec_b) {
  return vec_a.x * vec_b.x + vec_a.y * vec_b.y;
}

Point_2D DirectionVector(const Point_2D &start_point, const Point_2D &end_point) {
  Point_2D d = {end_point.x - start_point.x, end_point.y - start_point.y};
  return d;
}

Point_2D DirectionVector(const GCodeLine &line) {
  return DirectionVector(line.start_point, line.end_point);
}

int ValueInZeroToOne(double value) {
  return IsZero(value) || \
         (IsGreater(value, 0) && IsLesser(value, 1)) || \
         IsEqual(value, 1);

}

bool PointOnArc(const Point_2D &point, const GCodeArc &arc) {
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

/// arc C0
/// circle C1
Point_2D IntersectPoint(const GCodeArc &arc, const GCodeCircle &circle) {
  Point_2D u_vector = {circle.center.x - arc.center.x,
                       circle.center.y - arc.center.y};

  Point_2D v_vector = {u_vector.y, -u_vector.x};

  double s = 0.5 * ((pow(arc.r,2) - pow(circle.r,2)) / \
      VectorLengthSquare(u_vector) + 1);

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

Point_2D IntersectPoint(const GCodeLine &line, const GCodeCircle &circle) {
  Point_2D d_vector = DirectionVector(line);
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
