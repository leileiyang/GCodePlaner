#ifndef GCODE_GCODEPARSER_H_
#define GCODE_GCODEPARSER_H_

#include <string>
#include <vector>

#include "GCommand.h"

class PathManager;

enum PARSE_STATUS {
  PARSE_OK,
  PARSE_SYNTAX_ERROR,
};

class GCodeParser {
 public:
  GCodeParser();
  int ParseGCodeFromFile(const std::string &file_name);

  friend class PathManager;

 private:
  std::vector<GCommand> gcodes_;
  GCommand current_cmd_;
  bool g90_;
  bool g21_;
  int parse_status_;

  double scale_;
  double rotate_angle_;
  int x_mirror_;
  int y_mirror_;

  bool IsWithLineNo(const std::string line, char *content);
  void ParseCommand(char *content);

  int GetCmdType(char *content, int &cmd_index);
  void GetCmdName(int cmd_type, int cmd_index);
  void ParseGCommand(int cmd_index, const char *content);
  void ParseMCommand(int cmd_index, const char *content);

  void ParseOneArgument(const char *content);
  void ParseFourArguments(const char *content);
  void ParseLine(const char *content);
  void ParseArc(const char *content);
  void ProcessArgs(char arg_name, double arg_value);
};

#endif // GCODE_GCODEPARSER_H_
