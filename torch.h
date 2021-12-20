#ifndef TORCH_H
#define TORCH_H

#include <QGraphicsItem>

class Torch : public QGraphicsItem {
 public:
  Torch(double x, double y, QGraphicsItem *parent = 0);
  virtual ~Torch() {}

 private:
  double x_;
  double y_;

 protected:
  void paint(QPainter *painter, const QStyleOptionGraphicsItem *option,
             QWidget *widget);

  QRectF boundingRect() const;

};

#endif // TORCH_H
