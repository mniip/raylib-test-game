#pragma once

#include "raylib.h"
#include <compare>

struct Pos {
  int x, y;

  std::strong_ordering operator<=>(const Pos &) const = default;
};

inline bool PosInRectangle(Pos pos, Rectangle rect) {
  return pos.x >= rect.x && pos.x < rect.x + rect.width && pos.y >= rect.y &&
         pos.y < rect.y + rect.height;
}

enum Direction {
  RIGHT,
  DOWN,
  LEFT,
  UP,
};

inline Pos DirectionAdvance(Direction d, Pos pos) {
  switch (d) {
  case RIGHT:
    pos.x++;
    break;
  case LEFT:
    pos.x--;
    break;
  case DOWN:
    pos.y++;
    break;
  case UP:
    pos.y--;
    break;
  }
  return pos;
}

inline Direction DirectionInverse(Direction d) {
  switch (d) {
  case RIGHT:
    return LEFT;
  case LEFT:
    return RIGHT;
  case DOWN:
    return UP;
  case UP:
    return DOWN;
  }
}

constexpr unsigned screenWidthPx = 640;
constexpr unsigned screenHeightPx = 480;
constexpr unsigned tileSize = 16;
constexpr unsigned screenWidthTiles = screenWidthPx / tileSize;
constexpr unsigned screenHeightTiles = screenHeightPx / tileSize;
