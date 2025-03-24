#include "state.h"
#include <variant>

void DrawState(Env const &env, State const &state) {
  if (std::holds_alternative<MenuState>(state))
    DrawMenuState(env, std::get<MenuState>(state));
  else if (std::holds_alternative<GameState>(state))
    DrawGameState(env, std::get<GameState>(state));
  else if (std::holds_alternative<GameOverState>(state))
    DrawGameOverState(env, std::get<GameOverState>(state));
}

void TickState(Env const &env, State &state) {
  if (std::holds_alternative<MenuState>(state))
    TickMenuState(env, state, std::get<MenuState>(state));
  else if (std::holds_alternative<GameState>(state))
    TickGameState(env, state, std::get<GameState>(state));
  else if (std::holds_alternative<GameOverState>(state))
    TickGameOverState(env, state, std::get<GameOverState>(state));
}
