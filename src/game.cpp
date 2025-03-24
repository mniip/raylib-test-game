#include "common.h"
#include "gameover.h"
#include "raylib.h"
#include "sounds.h"
#include "sprites.h"
#include "state.h"
#include <optional>
#include <vector>

Pos RandomFoodPos(GameState const &state) {
  Pos foodPos = {GetRandomValue(0, screenWidthTiles - 1),
                 GetRandomValue(0, screenHeightTiles - 1)};
  Pos pos = state.headPos;
  bool hit = false;
  for (Direction d : state.tail) {
    if (pos == foodPos) {
      hit = true;
      break;
    }
    pos = DirectionAdvance(d, pos);
  }
  if (pos == foodPos) {
    hit = true;
  }
  return hit ? RandomFoodPos(state) : foodPos;
}

unsigned diffTable[] = {40, 36, 33, 30, 27, 25, 23, 21, 19, 17, 15, 14, 13, 12};

void TickGameState(Env const &env, State &state, GameState &gameState) {
  unsigned difficulty = gameState.score / 5;
  unsigned frameLimit = diffTable[std::min(
      difficulty, unsigned(sizeof diffTable / sizeof *diffTable - 1))];

  switch (gameState.headDir) {
  case RIGHT:
    if (env.downHeld)
      gameState.nextDir = DOWN;
    else if (env.upHeld)
      gameState.nextDir = UP;
    break;
  case DOWN:
    if (env.leftHeld)
      gameState.nextDir = LEFT;
    else if (env.rightHeld)
      gameState.nextDir = RIGHT;
    break;
  case LEFT:
    if (env.upHeld)
      gameState.nextDir = UP;
    else if (env.downHeld)
      gameState.nextDir = DOWN;
    break;
  case UP:
    if (env.rightHeld)
      gameState.nextDir = RIGHT;
    else if (env.leftHeld)
      gameState.nextDir = LEFT;
    break;
  }

  gameState.idleTicks++;

  if (gameState.idleTicks >= frameLimit) {
    gameState.idleTicks = 0;

    Direction nextDir =
        gameState.nextDir ? *gameState.nextDir : gameState.headDir;
    gameState.nextDir = std::nullopt;
    Pos nextPos = DirectionAdvance(nextDir, gameState.headPos);
    if (nextPos == gameState.foodPos) {
      gameState.headPos = nextPos;
      gameState.tail.insert(gameState.tail.begin(), DirectionInverse(nextDir));
      gameState.headDir = nextDir;

      gameState.foodPos = RandomFoodPos(gameState);
      gameState.score++;

      PlaySound(GetSound(SOUND_EAT));
    } else {
      Pos pos = gameState.headPos;
      bool hit =
          !(nextPos.x >= 0 && nextPos.y >= 0 && nextPos.x < screenWidthTiles &&
            nextPos.y < screenHeightTiles);
      if (!hit)
        for (Direction d : gameState.tail) {
          if (pos == nextPos) {
            hit = true;
            break;
          }
          pos = DirectionAdvance(d, pos);
        }
      if (hit) {
        state = GameOverState{gameState.score};
      } else {
        gameState.headPos = nextPos;
        gameState.tail.insert(gameState.tail.begin(),
                              DirectionInverse(nextDir));
        gameState.tail.pop_back();
        gameState.headDir = nextDir;

        PlaySound(GetSound(SOUND_MOVE));
      }
    }
  }
}

SpriteID headSpriteTable[4][4] = {
    {SPRITE_HEAD_RR, SPRITE_HEAD_RD, SpriteID(-1), SPRITE_HEAD_RU},
    {SPRITE_HEAD_DR, SPRITE_HEAD_DD, SPRITE_HEAD_DL, SpriteID(-1)},
    {SpriteID(-1), SPRITE_HEAD_LD, SPRITE_HEAD_LL, SPRITE_HEAD_LU},
    {SPRITE_HEAD_UR, SpriteID(-1), SPRITE_HEAD_UL, SPRITE_HEAD_UU},
};

SpriteID bodySpriteTable[4][4] = {
    {SPRITE_BODY_RR, SPRITE_BODY_RD, SpriteID(-1), SPRITE_BODY_RU},
    {SPRITE_BODY_DR, SPRITE_BODY_DD, SPRITE_BODY_DL, SpriteID(-1)},
    {SpriteID(-1), SPRITE_BODY_LD, SPRITE_BODY_LL, SPRITE_BODY_LU},
    {SPRITE_BODY_UR, SpriteID(-1), SPRITE_BODY_UL, SPRITE_BODY_UU},
};

SpriteID tailSpriteTable[4] = {
    SPRITE_TAIL_R,
    SPRITE_TAIL_D,
    SPRITE_TAIL_L,
    SPRITE_TAIL_U,
};

void DrawGameState(Env const &env, GameState const &state) {
  ClearBackground(DARKGREEN);

  DrawSprite(state.foodPos, SPRITE_APPLE);

  Pos pos = state.headPos;
  DrawSprite(pos,
             headSpriteTable[state.headDir]
                            [state.nextDir ? *state.nextDir : state.headDir]);
  for (int i = 0; i < state.tail.size(); i++) {
    Direction d1 = state.tail[i];
    pos = DirectionAdvance(d1, pos);
    if (i + 1 < state.tail.size()) {
      Direction d2 = state.tail[i + 1];
      DrawSprite(pos, bodySpriteTable[d1][d2]);

    } else {
      DrawSprite(pos, tailSpriteTable[d1]);
    }
  }
}

GameState NewGameState() {
  GameState state;

  state.headPos = {0, 0};
  state.headDir = RIGHT;
  state.nextDir = std::nullopt;
  state.tail = std::vector{LEFT};

  state.foodPos = RandomFoodPos(state);

  state.idleTicks = 0;
  state.score = 0;

  return state;
}
