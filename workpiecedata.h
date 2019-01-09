#ifndef WORKPIECEDATA_H
#define WORKPIECEDATA_H

#include <vector>

#include "gcode/GCommand.h"

class GCodeParser;
class Workpiece;

class WorkpieceData
{
public:
  WorkpieceData();

  friend class GCodeParser;
  friend class Workpiece;

  void Rotate(double angle);
  void XMirror();
  void YMirror();
  void Clear() {
    gcodes_.clear();
  }

private:
  std::vector<GCommand> gcodes_;
};

#endif // WORKPIECEDATA_H
