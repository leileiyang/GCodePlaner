#include "gcodepath.h"

#include <math.h>

#include <QtGui/QPainter>

#include "ecnc2math.h"

GCodePath::GCodePath(QColor color, double width, QGraphicsItem *parent):
    QGraphicsItem(parent),
    color_(color),
    width_(width) {

  setFlags(ItemIsSelectable);
  setAcceptHoverEvents(true);
}

GCodePath::GCodePath(const GCodePath &other) {
    path_ = other.path_;
    color_ = other.color_;
    width_ = other.width_;
}

GCodePath& GCodePath::operator =(const GCodePath &other) {
    path_ = other.path_;
    color_ = other.color_;
    width_ = other.width_;
    return *this;
}

void GCodePath::AddLine(double x1, double y1, double x2, double y2) {
    path_.moveTo(x1, y1);
    path_.lineTo(x2, y2);
}

void GCodePath::AddArc(const QPointF &start_point, const QPointF &end_point,
                       const QPointF &center, int cw_ccw) {

  double start_ang;
  double span_ang;
  ThreePoint2Angle(start_point, end_point, center, cw_ccw, start_ang, span_ang);

  double r = sqrt(pow(end_point.x() - center.x(), 2)
      + pow(end_point.y() - center.y(), 2));

  path_.arcTo(center.x() - r, center.y() - r, 2 * r, 2 * r, start_ang, span_ang);
}

void GCodePath::ThreePoint2Angle(const QPointF &start_pos,
                               const QPointF &end_pos,
                               const QPointF &center, int cw_ccw,
                               double &start_ang, double &span_ang) {

  QPointF vec_oa(start_pos.x() - center.x(), start_pos.y() - center.y());
  QPointF vec_ob(end_pos.x() - center.x(), end_pos.y() - center.y());
  start_ang = CalcuAngle(vec_oa);
  double end_ang = CalcuAngle(vec_ob);
  start_ang = start_ang >= 0 ? start_ang : 360 + start_ang;
  end_ang = end_ang >= 0? end_ang : 360 + end_ang;
  span_ang = end_ang - start_ang;

  if (cw_ccw) { // clockwise
    if (IsLesser(span_ang,0) || IsEqual(span_ang, 0)) {
      span_ang += 360;
    }
  } else { // counter-clockwise
    if (IsGreater(span_ang ,0) || IsEqual(span_ang, 0)) {
      span_ang -= 360;
    }
  }
}

double GCodePath::CalcuAngle(const QPointF &vec_oa) {
  QPointF vec_ox(3, 0);
  double sign = 1;
  double cos_angle = (vec_oa.x() * vec_ox.x() + vec_oa.y() * vec_ox.y()) /
      (sqrt(vec_oa.x() * vec_oa.x() + vec_oa.y() * vec_oa.y())
      * sqrt(vec_ox.x() * vec_ox.x() + vec_ox.y() * vec_ox.y()));

  if (IsLesser(vec_oa.y(), 0)) {
    sign = 1;
  } else {
    sign = -1;
  }
  return acos(cos_angle) * 180 / PI * sign;
}


void GCodePath::paint(QPainter *painter,
                      const QStyleOptionGraphicsItem * /*option*/,
                      QWidget * /*widget*/) {

    QPen old_pen = painter->pen();
    QPen pen = old_pen;
    pen.setColor(color_);
    pen.setWidth(width_);
    pen.setCosmetic(true);
    painter->setPen(pen);
    painter->drawPath(path_);
}

QRectF GCodePath::boundingRect() const {
    return path_.boundingRect();
}

bool GCodePath::IsEmpty() const {
    return path_.isEmpty();
}

void GCodePath::Clear() {
    prepareGeometryChange();
    path_ = QPainterPath();
}
