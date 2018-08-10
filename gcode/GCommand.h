#ifndef GCODE_GCOMMAND_H_
#define GCODE_GCOMMAND_H_

#include <string>

enum GMID {
  M02, G00, G01, G02, G03, G04, G92, G40, G41, G42, 
  G20, G21, G90, G91, G99, G26, G27, G28, G22, G80, 
  M00, M30, M07, M08, M09, M10, M11, M12, M50, M52,
  M80, G62, G63, G64, GGG
};

class GCommand {
 public:
  GCommand();
  GCommand(const GCommand &other);
  GCommand& operator=(const GCommand &other);

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
};

#endif
