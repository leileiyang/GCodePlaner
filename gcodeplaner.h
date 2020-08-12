#ifndef GCODEPLANER_H
#define GCODEPLANER_H

#include <QMainWindow>
#include <QGraphicsScene>

#include "neomath/neomath.h"

#include "workpiece.h"
#include "workpiecedata.h"

#include "librecad/lib/engine/rs_graphic.h"

namespace Ui {
class GCodePlaner;
}

class GCodePlaner : public QMainWindow
{
    Q_OBJECT

public:
    explicit GCodePlaner(QWidget *parent = 0);
    ~GCodePlaner();

private slots:
  void on_actionOpen_triggered();

  void on_actionXMirror_triggered();

  void on_actionYMirror_triggered();

  void on_actionRotate_triggered();

  void on_actionRestore_triggered();

private:
    Ui::GCodePlaner *ui;
    QGraphicsScene scene_;

    RS_Document *document_;

    WorkpieceData workpiece_data_;
};

#endif // GCODEPLANER_H
