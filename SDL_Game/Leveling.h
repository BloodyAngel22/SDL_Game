#pragma once
#include "SDL_general.h"

void level_up();
void character_leveling(SDL_Renderer* ren);
void set_runes(bool& runeWater, bool& runeFire, bool& runeEarth);
void remove_the_rune(bool& runeWater, bool& runeFire, bool& runeEarth);
