#ifndef WORKPIECE_H
#define WORKPIECE_H

#include <vector>

#include <QtCore/QRectF>
#include <QtGui/QGraphicsItemGroup>

#include "gcodepath.h"
#include "gcode/GCommand.h"

class Workpiece : public QObject
{
  Q_OBJECT
public:
  explicit Workpiece(QObject *parent = 0);
  Workpiece(int id, QObject *parent = 0);

  int WorkpieceId () const {
    return id_;
  }

  std::vector<GCommand>& WorkpieceGCodes () {
    return gcodes_;
  }

  QGraphicsItemGroup *GetWorkpiece() {
    return group_;
  }

  QRectF WorkpieceSize() const {
    return group_->boundingRect();
  }
  void Draw();

signals:

public slots:

private:
  int id_;
  GCodePath *move_path_;
  GCodePath *cutting_path_;
  QGraphicsItemGroup *group_;

  std::vector<GCommand> gcodes_;

};

#endif // WORKPIECE_H
