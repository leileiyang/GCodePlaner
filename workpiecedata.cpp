#include "workpiecedata.h"

#include <algorithm>

WorkpieceData::WorkpieceData() {}

void XMirrorCmd(GCommand &cmd) {
  cmd.XMirror();
}

void YMirrorCmd(GCommand &cmd) {
  cmd.YMirror();
}

void WorkpieceData::Rotate(double angle) {
  std::vector<GCommand>::iterator iter = gcodes_.begin();
  for (; iter != gcodes_.end(); iter++) {
    iter->Rotate(angle);
  }
}

void WorkpieceData::XMirror() {
  std::for_each(gcodes_.begin(), gcodes_.end(), XMirrorCmd);
}

void WorkpieceData::YMirror() {
  std::for_each(gcodes_.begin(), gcodes_.end(), YMirrorCmd);
}
