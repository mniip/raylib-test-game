#pragma once

#include "env.h"

struct GameOverState {
  unsigned score;
};

void DrawGameOverState(Env const &, GameOverState const &);
