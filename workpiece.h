#ifndef WORKPIECE_H
#define WORKPIECE_H

#include <QtCore/QRectF>
#include <QGraphicsItemGroup>

#include "gcodepath.h"
#include "workpiecedata.h"

#include "librecad/lib/engine/rs_entitycontainer.h"
#include "librecad/lib/gui/rs_pen.h"

class Workpiece : public QObject
{
  Q_OBJECT
public:
  Workpiece(int id, WorkpieceData &data, RS_EntityContainer *container);
  ~Workpiece();

  int WorkpieceId () const {
    return id_;
  }

  //QRectF WorkpieceSize() const {
  //  return cutting_path_->boundingRect().united(move_path_->boundingRect());
  //}
  void Draw();

signals:

public slots:

private:
  int id_;
  WorkpieceData &data_;
  RS_EntityContainer *container_;

  RS_Pen move_path_pen_;
  RS_Pen cutting_path_pen_;

  void AddCutLine(double x0, double y0, double x1, double y1);
  void AddMoveLine(double x0, double y0, double x1, double y1);
  void AddLine(double x0, double y0, double x1, double y1, const RS_Pen &pen);
  void AddArc(const Point_2D &start, const Point_2D &end, const Point_2D &center, int direction);

};

#endif // WORKPIECE_H
