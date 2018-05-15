#ifndef GCODE_GCODEPARSER_H_
#define GCODE_GCODEPARSER_H_

#include <string>
#include <vector>

struct GCode {
  char type;
  int index;

  double x_start;
  double y_start;
  double x_end;
  double y_end;

  double i_center;
  double j_center;
  double r_radius;
  double f_speed;
  double length;
};


class GCodeParser {
 public:
  int ParseGCode(const std::string &file_name);

 private:
  std::vector<GCode> gcodes_;

};

#endif // GCODE_GCODEPARSER_H_
