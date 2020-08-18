#ifndef GCODEPLANER_H
#define GCODEPLANER_H

#include <QMainWindow>
#include <QMap>

#include "neomath/neomath.h"

#include "workpiece.h"
#include "workpiecedata.h"

#include "librecad/lib/engine/rs_graphic.h"
#include "librecad/ui/qg_actionhandler.h"

class LC_ActionGroupManager;

namespace Ui {
class GCodePlaner;
}

class GCodePlaner : public QMainWindow
{
    Q_OBJECT

 public:
  explicit GCodePlaner(QWidget *parent = 0);
  ~GCodePlaner();

 QMap<QString, QAction*> a_map_;
 LC_ActionGroupManager *ag_manager_{nullptr};

private slots:
  void on_actionOpen_triggered();

  void on_actionXMirror_triggered();

  void on_actionYMirror_triggered();

  void on_actionRotate_triggered();

  void on_actionRestore_triggered();

private:
    Ui::GCodePlaner *ui;

    RS_Document *document_;

    QG_ActionHandler *action_handler_{nullptr};

    WorkpieceData workpiece_data_;
};

#endif // GCODEPLANER_H
