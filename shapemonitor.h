#ifndef SHAPEMONITOR_H
#define SHAPEMONITOR_H

#include <QWidget>
#include <QtGui/QGraphicsScene>
#include <QtGui/QGraphicsItem>

namespace Ui {
class ShapeMonitor;
}

class ShapeMonitor : public QWidget
{
    Q_OBJECT

public:
  explicit ShapeMonitor(QWidget *parent = 0);
  ~ShapeMonitor();


  void setSceneRect(const QRectF &rect);
public slots:
  void setScene(QGraphicsScene *scene);

private:
    Ui::ShapeMonitor *ui;

};

#endif // SHAPEMONITOR_H
