#ifndef GCODE_GCODEPARSER_H_
#define GCODE_GCODEPARSER_H_

#include <string>
#include <vector>

#include "GCommand.h"

class GCodeParser {
 public:
  int ParseGCode(const std::string &file_name);

 private:
  std::vector<GCommand> gcodes_;

};

#endif // GCODE_GCODEPARSER_H_
