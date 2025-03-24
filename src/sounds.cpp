#include "sounds.h"
#include "raylib.h"
#include <array>

std::array<Sound, 3> soundMove;
Sound soundEat;

void LoadSounds() {
  soundMove[0] = LoadSound("res/move.ogg");
  soundMove[1] = LoadSoundAlias(soundMove[0]);
  soundMove[2] = LoadSoundAlias(soundMove[0]);
  soundEat = LoadSound("res/eat.ogg");
}

void UnloadSounds() {
  UnloadSoundAlias(soundMove[1]);
  UnloadSoundAlias(soundMove[2]);
  UnloadSound(soundMove[0]);
  UnloadSound(soundEat);
}

Sound GetSound(SoundID id) {
  switch (id) {
  case SOUND_MOVE:
    for (Sound &sound : soundMove)
      if (!IsSoundPlaying(sound))
        return sound;
    return soundMove[0];
  case SOUND_EAT:
    return soundEat;
  }
}
