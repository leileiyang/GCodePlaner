#include "torch.h"

#include <QtGui/QPen>
#include <QtGui/QPainter>

Torch::Torch(double x, double y, QGraphicsItem *parent): QGraphicsItem(parent),
    x_(x), y_(y) {

  setPos(x_, y_);
  setFlag(QGraphicsItem::ItemIgnoresTransformations);
}


void Torch::paint(QPainter *painter, const QStyleOptionGraphicsItem * /*option*/,
           QWidget * /*widget*/) {

  QPen old_pen = painter->pen();
  QPen pen = old_pen;
  pen.setColor(Qt::red);
  pen.setWidth(2);
  pen.setCosmetic(true);
  painter->setPen(pen);
  QLineF line_h(-10, 0, 10, 0);
  QLineF line_v(0, -10, 0, 10);
  painter->drawLine(line_h);
  painter->drawLine(line_v);
  painter->drawEllipse(QRectF(-8, -8, 16, 16));

}

QRectF Torch::boundingRect() const {
  return QRectF(-10, -10, 20, 20);
}
