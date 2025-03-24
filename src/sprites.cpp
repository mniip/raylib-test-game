#include "sprites.h"
#include "common.h"
#include "raylib.h"

Texture2D sprites;

void LoadSprites() {
  Image image = LoadImage("res/sprites.png");
  sprites = LoadTextureFromImage(image);
  UnloadImage(image);
}

void UnloadSprites() { UnloadTexture(sprites); }

constexpr int spritesPerRow = 8;

void DrawSprite(Pos pos, SpriteID index) {
  unsigned sx = unsigned(index) % spritesPerRow;
  unsigned sy = unsigned(index) / spritesPerRow;
  Rectangle rect = {float(sx * tileSize), float(sy * tileSize), tileSize,
                    tileSize};
  DrawTextureRec(sprites, rect,
                 Vector2{float(pos.x * tileSize), float(pos.y * tileSize)},
                 WHITE);
}
