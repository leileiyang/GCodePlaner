#ifndef PATHMANAGER_H
#define PATHMANAGER_H

#include <QObject>
#include <QtGui/QGraphicsScene>

#include "gcode/GCodeParser.h"
#include "gcodepath.h"

class PathManager : public QObject
{
    Q_OBJECT
public:
    explicit PathManager(QObject *parent = 0);

    void DrawGCode(const GCodeParser &gcode_parser);

    QGraphicsScene *Scene () {
      return scene_;
    }

signals:
    void newScene(QGraphicsScene *scene);

public slots:

private:
  QGraphicsScene *scene_;
  GCodePath move_path_;
  GCodePath cutting_path_;

};

#endif // PATHMANAGER_H
