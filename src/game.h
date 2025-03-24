#pragma once

#include "common.h"
#include "env.h"
#include <optional>
#include <vector>

struct GameState {
  Pos foodPos;
  Pos headPos;
  Direction headDir;
  std::optional<Direction> nextDir;
  std::vector<Direction> tail;
  unsigned idleTicks;
  unsigned score;
};

void DrawGameState(Env const &, GameState const &);

GameState NewGameState();
