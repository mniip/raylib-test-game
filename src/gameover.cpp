#include "gameover.h"
#include "common.h"
#include "raylib.h"
#include "state.h"
#include <format>

Rectangle exitButton{240, 200, 160, 80};

void DrawGameOverState(Env const &env, GameOverState const &state) {
  ClearBackground(BLACK);

  if (PosInRectangle(env.mousePos, exitButton))
    DrawRectangleRec(exitButton, GRAY);
  DrawRectangleLinesEx(exitButton, 3, LIGHTGRAY);
  char const *exitLabel = "Exit";
  int fontSize = 32;
  int exitWidth = MeasureText(exitLabel, fontSize);
  DrawText(exitLabel, exitButton.x + exitButton.width / 2 - exitWidth / 2.0,
           exitButton.y + exitButton.height / 2 - fontSize / 2.0, fontSize,
           WHITE);

  std::string scoreLabel = std::format("Score: {}", state.score);
  int scoreWidth = MeasureText(scoreLabel.c_str(), fontSize);
  DrawText(scoreLabel.c_str(),
           exitButton.x + exitButton.width / 2 - scoreWidth / 2.0,
           exitButton.y + exitButton.height + exitButton.height / 2 -
               fontSize / 2.0,
           fontSize, WHITE);
}

void TickGameOverState(const Env &env, State &state, GameOverState &menuState) {
  if (env.mouseLeftPressed && PosInRectangle(env.mousePos, exitButton))
    state = MenuState{};
}
