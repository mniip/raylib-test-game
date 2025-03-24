#pragma once

#include "raylib.h"

void LoadSounds();
void UnloadSounds();

enum SoundID {
  SOUND_MOVE = 0,
  SOUND_EAT,
};

Sound GetSound(SoundID);
