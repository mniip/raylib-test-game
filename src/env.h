#pragma once

#include "common.h"

struct Env {
  Pos mousePos;
  bool mouseLeftPressed;
  bool rightHeld;
  bool downHeld;
  bool leftHeld;
  bool upHeld;
};

Env GetEnv();
