#ifndef GCODEPATH_H
#define GCODEPATH_H

#include <QGraphicsItem>
#include <QtGui/QPen>

#include "neomath/neomath.h"

class Workpiece;

class GCodePath: public QGraphicsItem  {
public:
    GCodePath(QColor color, double width, QGraphicsItem *parent = 0);
    virtual ~GCodePath() {}

    friend class Workpiece;

    bool IsEmpty() const;
    void SetColor(const QColor &color) {
        color_ = color;
    }

    void SetWidth(double width) {
        width_ = width;
    }

    void MoveTo(double x, double y) {
      path_.moveTo(x, y);
    }

    void MoveTo(const QPointF &pos) {
      path_.moveTo(pos);
    }

    void AddPoint(double x, double y);
    void AddPoint(const QPointF &pos);

    void AddLine(double x1, double y1, double x2, double y2);
    void AddArc(const QPointF &start_point, const QPointF &end_point,
                const QPointF &center, int cw_ccw);

    void AddArc(const Point_2D &start_point, const Point_2D &end_point,
                const Point_2D &center, int cw_ccw);

    void Clear();

protected:
    void paint(QPainter *painter, const QStyleOptionGraphicsItem *option,
               QWidget *widget);

    QRectF boundingRect() const;

private:
    QPainterPath path_;
    QColor color_;
    double width_;

    GCodePath(const GCodePath &other);
    GCodePath& operator=(const GCodePath &other);

};

#endif // GCODEPATH_H
