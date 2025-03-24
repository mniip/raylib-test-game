#include "env.h"

Env GetEnv() {
  Env env;
  env.mousePos = Pos{GetMouseX(), GetMouseY()};
  env.mouseLeftPressed = IsMouseButtonPressed(MOUSE_BUTTON_LEFT);
  env.rightHeld = IsKeyDown(KEY_RIGHT);
  env.downHeld = IsKeyDown(KEY_DOWN);
  env.leftHeld = IsKeyDown(KEY_LEFT);
  env.upHeld = IsKeyDown(KEY_UP);
  return env;
}
