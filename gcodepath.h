#ifndef GCODEPATH_H
#define GCODEPATH_H

#include <QtGui/QGraphicsItem>
#include <QtGui/QPen>

class GCodePath: public QGraphicsItem  {
public:
    GCodePath(QColor color, double width, QGraphicsItem *parent = 0);

    GCodePath(const GCodePath &other);
    GCodePath& operator=(const GCodePath &other);

    bool IsEmpty() const;
    void SetColor(const QColor &color) {
        color_ = color;
    }

    void SetWidth(double width) {
        width_ = width;
    }

    void MoveTo(double x, double y);
    void MoveTo(const QPointF &pos);

    void AddPoint(double x, double y);
    void AddPoint(const QPointF &pos);

    void AddLine(double x1, double y1, double x2, double y2);
    void AddArc(const QPointF &start_point, const QPointF &end_point,
                const QPointF &center, int cw_ccw);

    void Clear();

    static double CalcuAngle(const QPointF &vec_oa);
    static void ThreePoint2Angle(const QPointF &start_pos,
                                 const QPointF &end_pos,
                                 const QPointF &center, int cw_ccw,
                                 double &start_ang, double &span_ang);

protected:
    void paint(QPainter *painter, const QStyleOptionGraphicsItem *option,
               QWidget *widget);

    QRectF boundingRect() const;

private:
    QPainterPath path_;
    QColor color_;
    double width_;

};

#endif // GCODEPATH_H
