#include "pathmanager.h"

PathManager::PathManager(QObject *parent) : QObject(parent)
{
  scene_ = new QGraphicsScene(this);
}

//void PathManager::DrawGCode(const GCodeParser &gcode_parser, int opt) {
//  if (opt) {

 // } else {

 // }
//}
