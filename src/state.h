#pragma once

#include "game.h"
#include "gameover.h"
#include "menu.h"
#include <variant>

using State = std::variant<MenuState, GameState, GameOverState>;

void TickMenuState(Env const &, State &, MenuState &);
void TickGameState(Env const &, State &, GameState &);
void TickGameOverState(Env const &, State &, GameOverState &);
void TickState(Env const &, State &);
void DrawState(Env const &, State const &);
