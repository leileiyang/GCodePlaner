#include "deslaggingcode.h"

#include <math.h>

DeslaggingCode::DeslaggingCode() {}

std::vector<GCommand> DeslaggingCode::GetDeslaggingCode(double radius,
                                                        int count) {
  double segment_r = radius / count;

  std::vector<GCommand> code;

  GCommand gcmd;
  gcmd.name_ = G03;

  for (int i = 0; i < 2 * count; ++i) {
    gcmd.x0_ = gcmd.x_;
    gcmd.y0_ = gcmd.y_;

    gcmd.x_ = segment_r * (i / 2 + 1) * pow(-1, i);
    gcmd.y_ = gcmd.y0_;

    gcmd.i_ = (gcmd.x0_ + gcmd.x_) / 2;
    gcmd.j_ = (gcmd.y0_ + gcmd.y_) / 2;
    code.push_back(gcmd);
  }

  gcmd.x0_ = gcmd.x_;
  gcmd.y0_ = gcmd.y_;
  gcmd.x_ = segment_r * count;
  gcmd.i_ = (gcmd.x0_ + gcmd.x_) / 2;
  gcmd.j_ = (gcmd.y0_ + gcmd.y_) / 2;
  code.push_back(gcmd);

  gcmd.x0_ = gcmd.x_;
  gcmd.y0_ = gcmd.y_;
  gcmd.x_ = 0;
  gcmd.i_ = (gcmd.x0_ + gcmd.x_) / 2;
  gcmd.j_ = (gcmd.y0_ + gcmd.y_) / 2;
  code.push_back(gcmd);

  return code;
}
