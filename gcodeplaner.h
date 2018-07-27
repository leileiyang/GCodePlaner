#ifndef GCODEPLANER_H
#define GCODEPLANER_H

#include <QMainWindow>

#include "gcode_math/math_object.h"

namespace Ui {
class GCodePlaner;
}

class GCodePlaner : public QMainWindow
{
    Q_OBJECT

public:
    explicit GCodePlaner(QWidget *parent = 0);
    ~GCodePlaner();

  Point_2D IntersectPoint(const GCodeArc &arc, const GCodeCircle &circle);
  Point_2D IntersectPoint(const GCodeLine &line, const GCodeCircle &circle);
  Point_2D GetDVector(const GCodeLine &line);
  Point_2D GetDVector(const Point_2D &start_point, const Point_2D &end_point);
  Point_2D GetDotPerpVector(const Point_2D &vec);

  double VectorDot(const Point_2D &vec_a, const Point_2D &vec_b);
  double VectorLengthSquare(const Point_2D &vec);
  double GetTArgument(const Point_2D &d_vector, const Point_2D &delta, double lower_delta);
  int ValueInZeroToOne(double value);
  bool PointOnArc(const Point_2D &point, const GCodeArc &arc);


private:
    Ui::GCodePlaner *ui;
};

#endif // GCODEPLANER_H
