#include "common.h"
#include "raylib.h"
#include "sounds.h"
#include "sprites.h"
#include "state.h"

#if defined(PLATFORM_WEB)
#include <emscripten.h>
#endif

void MainLoopFrame(void *arg) {
  State &state = *static_cast<State *>(arg);
  Env env = GetEnv();
  TickState(env, state);
  BeginDrawing();
  DrawState(env, state);
  EndDrawing();
}

int main() {
  State state = MenuState{};
  InitWindow(screenWidthPx, screenHeightPx, "raygame");
  LoadSprites();
  InitAudioDevice();
  LoadSounds();
  const int fps = 60;
#if defined(PLATFORM_WEB)
  emscripten_set_main_loop_arg(MainLoopFrame, &state, fps, 1);
#else
  SetTargetFPS(fps);
  while (!WindowShouldClose())
    MainLoopFrame(&state);
#endif
  UnloadSounds();
  CloseAudioDevice();
  CloseWindow();
  return 0;
}
