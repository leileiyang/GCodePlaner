#include "gcodepath.h"

#include <QtGui/QPainter>

GCodePath::GCodePath(QColor color, double width, QGraphicsItem *parent):
    QGraphicsItem(parent),
    color_(color),
    width_(width) {

  setFlags(ItemIsSelectable);
  setAcceptHoverEvents(true);
}

void GCodePath::AddLine(double x1, double y1, double x2, double y2) {
    path_.moveTo(x1, y1);
    path_.lineTo(x2, y2);
}

void GCodePath::AddArc(const QPointF &start_point, const QPointF &end_point,
                       const QPointF &center, int cw_ccw) {

  Point_2D start_point_2d = {start_point.x(), start_point.y()};
  Point_2D end_point_2d = {end_point.x(), end_point.y()};
  Point_2D center_2d = {center.x(), center.y()};

  AddArc(start_point_2d, end_point_2d, center_2d, cw_ccw);
}

void GCodePath::AddArc(const Point_2D &start_point, const Point_2D &end_point,
                const Point_2D &center, int cw_ccw) {

  double start_ang = CenterAngle(start_point, center);
  double end_ang = CenterAngle(end_point, center);
  double span_ang = SpanCenterAngle(start_ang, end_ang, cw_ccw);

  double r = sqrt(pow(end_point.x - center.x, 2)
      + pow(end_point.y - center.y, 2));

  path_.arcTo(center.x - r, center.y - r, 2 * r, 2 * r, start_ang, span_ang);
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
