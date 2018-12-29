#ifndef GCODE_GCOMMAND_H_
#define GCODE_GCOMMAND_H_

#include <string>

#include "GCodeDefine.h"

class GCommand {
 public:
  GCommand();
  GCommand(const GCommand &other);
  GCommand& operator=(const GCommand &other);

  void Scale(double scale);
  // angle unit: degree
  void Rotate(double angle);
  void XMirror();
  void YMirror();

  unsigned int line_no_;
  unsigned int name_;

  double x0_;
  double y0_;
  double x_;
  double y_;
  double i_;
  double j_;
  double f_;
  double r_;

  double length_;
  double start_angle_;
  double end_angle_;

  std::string ext_args_;
 private:
  void MirrorName();

};

#endif
