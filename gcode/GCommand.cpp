#include "GCommand.h"

#include <math.h>

#include "neomath/ecnc2math.h"
#include "neomath/neomath.h"

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
  ext_args_ = other.ext_args_;
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
  ext_args_ = other.ext_args_;
  return *this;
}

void GCommand::Scale(double scale) {
  x0_ *= scale;
  y0_ *= scale;
  x_ *= scale;
  y_ *= scale;
  i_ *= scale;
  j_ *= scale;
  r_ *= scale;
}

void GCommand::Rotate(double angle) {
  RotatePoint(x0_, y0_, angle);
  RotatePoint(x_, y_, angle);
  RotatePoint(i_, j_, angle);
}

void GCommand::MirrorName() {
  switch (name_) {
    case G41:
      name_ = G42;
      break;
    case G42:
      name_ = G41;
      break;
    case G02:
      name_ = G03;
      break;
    case G03:
      name_ = G02;
      break;
  }
}

void GCommand::XMirror() {
  y0_ = -y0_;
  y_ = -y_;
  j_ = -j_;
  MirrorName();
}

void GCommand::YMirror() {
  x0_ = -x0_;
  x_ = -x_;
  i_ = -i_;
  MirrorName();
}
