#ifndef PATHMANAGER_H
#define PATHMANAGER_H

#include <QObject>
#include <QtGui/QGraphicsScene>

#include "gcode/GCodeParser.h"

class PathManager : public QObject
{
    Q_OBJECT
public:
    explicit PathManager(QObject *parent = 0);

    // opt:0, draw the original gcode
    //     1. draw the gcode with kerf
    //void DrawGCode(const GCodeParser &gcode_parser, int opt);

signals:
    void newScene(QGraphicsScene *scene);

public slots:

private:
  QGraphicsScene *scene_;

};

#endif // PATHMANAGER_H
