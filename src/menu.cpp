#include "common.h"
#include "raylib.h"
#include "state.h"

Rectangle startButton{240, 200, 160, 80};

void DrawMenuState(Env const &env, MenuState const &state) {
  ClearBackground(BLACK);
  if (PosInRectangle(env.mousePos, startButton))
    DrawRectangleRec(startButton, GRAY);
  DrawRectangleLinesEx(startButton, 3, LIGHTGRAY);
  char const *newLabel = "New Game";
  int fontSize = 32;
  int newWidth = MeasureText(newLabel, fontSize);
  DrawText(newLabel, startButton.x + startButton.width / 2 - newWidth / 2.0,
           startButton.y + startButton.height / 2 - fontSize / 2.0, fontSize,
           WHITE);
}

void TickMenuState(const Env &env, State &state, MenuState &menuState) {
  if (env.mouseLeftPressed && PosInRectangle(env.mousePos, startButton))
    state = NewGameState();
}
