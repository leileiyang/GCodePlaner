#ifndef WORKPIECE_H
#define WORKPIECE_H

#include <QtCore/QRectF>
#include <QtGui/QGraphicsScene>
#include <QtGui/QGraphicsItemGroup>

#include "gcodepath.h"
#include "workpiecedata.h"

class Workpiece : public QObject
{
  Q_OBJECT
public:
  Workpiece(int id, WorkpieceData &data, QObject *parent = 0);
  ~Workpiece();

  int WorkpieceId () const {
    return id_;
  }

  void AddToScene(QGraphicsScene *scene);
  void RemoveFromScene(QGraphicsScene *scene);

  QRectF WorkpieceSize() const {
    return cutting_path_->boundingRect().united(move_path_->boundingRect());
  }
  void Draw();

signals:

public slots:

private:
  int id_;
  WorkpieceData &data_;
  bool ownership_;

  GCodePath *move_path_;
  GCodePath *cutting_path_;
  QGraphicsItemGroup *group_;

};

#endif // WORKPIECE_H
