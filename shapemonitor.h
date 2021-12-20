#ifndef SHAPEMONITOR_H
#define SHAPEMONITOR_H

#include <QWidget>
#include <QGraphicsScene>
#include <QGraphicsItem>
#include <QWheelEvent>
#include <QtGui/QMatrix>

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
  void StepZoomIn();
  void StepZoomOut();
  void onRestore();
public slots:
  void setScene(QGraphicsScene *scene);

protected:
  void wheelEvent(QWheelEvent *);

private:
    Ui::ShapeMonitor *ui;
    QMatrix matrix_;

};

#endif // SHAPEMONITOR_H
