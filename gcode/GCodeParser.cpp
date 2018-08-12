#include "GCodeParser.h"

#include <stdio.h>
#include <string.h>
#include <math.h>

#include <fstream>

const static double RATIO_G20_TO_G21 = 25.4;


bool GCodeParser::IsWithLineNo(const std::string line, char *content) {
  int n = 0;
  int match_num = sscanf(line.c_str(), " %*[Nn]%d %255[^\001]", &n, content);
  if (match_num >= 1) {
    return true;
  } else {
    return false;
  }
}

int GCodeParser::GetCmdType(char *content, int &cmd_index) {
  char cmd_type;
  char args[256] = {0};
  int match_num = sscanf(content, " %[GgMm]%d %255[^\001]", &cmd_type, &cmd_index,
                         args);

  if (match_num >= 1) {
    memset(content, 0, 256);
    memcpy(content, args, 256);
    return cmd_type;
  } else {
    return 0;
  }
}


void GCodeParser::ProcessArgs(char arg_name, double arg_value) {
  switch (arg_name) {
  case 'x':
  case 'X':
      if (g90_) {
        current_cmd_.x_ = arg_value;
      } else {
        current_cmd_.x_ += arg_value;
      }
      break;
  case 'y':
  case 'Y':
      if (g90_) {
        current_cmd_.y_ = arg_value;
      } else {
        current_cmd_.y_ += arg_value;
      }
      break;
  case 'u':
  case 'U':
      current_cmd_.x_ += arg_value;
      break;
  case 'v':
  case 'V':
      current_cmd_.y_ += arg_value;
      break;
  case 'f':
  case 'F':
      current_cmd_.f_ = arg_value;
      break;
  case 'i':
  case 'I':
      current_cmd_.i_ = current_cmd_.x0_ + arg_value;
      break;
  case 'j':
  case 'J':
      current_cmd_.j_ = current_cmd_.y0_ + arg_value;
      break;
  case 'r':
  case 'R':
      current_cmd_.r_ = fabs(arg_value);
      break;
  case 'P':
  case 'L':
      current_cmd_.length_ = arg_value;
      break;
  default:
      break;
  }
}

void GCodeParser::ParseOneArgument(const char *content) {
  char arg_name = '0';
  double arg_value = 0.;
  sscanf(content, "%c%lf", &arg_name, &arg_value);
  ProcessArgs(arg_name, arg_value);
}

void GCodeParser::ParseLine(const char *content) {
  char arg_names[3] = {0};
  double arg_values[3]  = {0.};
  sscanf(content, "%c%lf %c%lf %c%lf",
         &arg_names[0], &arg_values[0],
         &arg_names[1], &arg_values[1],
         &arg_names[2], &arg_values[2]);

  for (int i = 0; i < 3; i++) {
    if (!g21_) {
      arg_values[i] *= RATIO_G20_TO_G21;
    }
    ProcessArgs(arg_names[i], arg_values[i]);
  }
}

void GCodeParser::ParseArc(const char *content) {
  char arg_names[5] = {0};
  double arg_values[5] = {0.};
  sscanf(content, "%c%lf %c%lf %c%lf %c%lf %c%lf",
         &arg_names[0], &arg_values[0],
         &arg_names[1], &arg_values[1],
         &arg_names[2], &arg_values[2],
         &arg_names[3], &arg_values[3],
         &arg_names[4], &arg_values[4]);

  for (int i = 0; i < 5; i++) {
    if (!g21_) {
      arg_values[i] *= RATIO_G20_TO_G21;
    }
    ProcessArgs(arg_names[i], arg_values[i]);
  }
}

void GCodeParser::GetCmdName(int cmd_type, int cmd_index) {
  if (cmd_type == 'g' || cmd_type == 'G') {
    switch (cmd_index) {
    case 0: current_cmd_.name_ = G00; break;
    case 1: current_cmd_.name_ = G01; break;
    case 2: current_cmd_.name_ = G02; break;
    case 3: current_cmd_.name_ = G03; break;
    case 4: current_cmd_.name_ = G04; break;
    }
  } else if (cmd_type == 'm' || cmd_type == 'M') {
    switch (cmd_index) {
    case 0: current_cmd_.name_ = M00; break;
    case 2: current_cmd_.name_ = M02; break;
    case 7: current_cmd_.name_ = M07; break;
    case 8: current_cmd_.name_ = M08; break;
    }
  }
}

void GCodeParser::ParseGCommand(int cmd_index, const char *content) {
  if (cmd_index == -1) { // default command
    switch (current_cmd_.name_) {
    case G00:
    case G01:
      ParseLine(content);
      break;
    case G02:
    case G03:
      ParseArc(content);
      break;
    default:
      break;
    }
  } else {
    GetCmdName('G', cmd_index);
    // get command arguments
    switch (cmd_index) {
    case 0:
    case 1:
      ParseLine(content);
      break;
    case 2:
    case 3:
      ParseArc(content);
      break;
    case 4:
      ParseOneArgument(content);
    default:
      break;
    }
  }
}

void GCodeParser::ParseMCommand(int cmd_index, const char */*content*/) {
  GetCmdName('M', cmd_index);
}

void GCodeParser::ParseCommand(char *content) {
  int cmd_index = 0;
  char cmd_type = GetCmdType(content, cmd_index);
  switch (cmd_type) {
  case 0:
    if (current_cmd_.name_ >= G00 && current_cmd_.name_ <= G03) {
      ParseGCommand(-1, content);
    } else {
      parse_status_ = PARSE_SYNTAX_ERROR;
    }
    break;
  case 'g':
  case 'G':
    ParseGCommand(cmd_index, content);
    break;
  case 'm':
  case 'M':
    ParseMCommand(cmd_index, content);
    break;
  default:
    break;
  }
}

int GCodeParser::ParseGCodeFromFile(const std::string &file_name) {
  std::ifstream input_file(file_name.c_str());
  std::string line;
  char content[256] = {0};
  while (std::getline(input_file, line)) {
    memset(content, 0, 256);
    if (IsWithLineNo(line, content)) {  // with line number "N"
      ParseCommand(content);
    } else { // without line nubmer
      memset(content, 0, 256);
      strcpy(content, line.c_str());
      ParseCommand(content);
    }
    gcodes_.push_back(current_cmd_);
    current_cmd_.line_no_++;
  }
  return PARSE_OK;
}
