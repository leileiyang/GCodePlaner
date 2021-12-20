#ifndef DESLAGGINGCODE_H
#define DESLAGGINGCODE_H

#include <vector>

#include "GCommand.h"

class DeslaggingCode {
 public:
  DeslaggingCode();
  std::vector<GCommand> GetDeslaggingCode(double radius, int count);
};

#endif // DESLAGGINGCODE_H
