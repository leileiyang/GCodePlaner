#include "GCommand.h"

GCommand::GCommand(): line_no_(0), name_(0), x0_(0.), y0_(0.), x_(0.), y_(0.),
    i_(0.), j_(0.), f_(0.), r_(0.),
    length_(0.), start_angle_(0.), end_angle_(0.) {}

GCommand::GCommand(const GCommand &other) {
  line_no_ = other.line_no_;
  name_ = other.name_;

  x0_ = other.x0_;
  y0_ = other.y0_;
  x_ = other.x_;
  y_ = other.y_;
  i_ = other.i_;
  j_ = other.j_;
  f_ = other.f_;
  r_ = other.r_;

  length_ = other.length_;
  start_angle_ = other.start_angle_;
  end_angle_ = other.end_angle_;
}

GCommand& GCommand::operator=(const GCommand &other) {
  line_no_ = other.line_no_;
  name_ = other.name_;

  x0_ = other.x0_;
  y0_ = other.y0_;
  x_ = other.x_;
  y_ = other.y_;
  i_ = other.i_;
  j_ = other.j_;
  f_ = other.f_;
  r_ = other.r_;

  length_ = other.length_;
  start_angle_ = other.start_angle_;
  end_angle_ = other.end_angle_;
  return *this;
}
