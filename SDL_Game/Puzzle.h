#pragma once
#include "SDL_general.h"

extern int flagCode;
extern int flagLamps;
extern int flagRunes;
extern int checkChest;
extern int checkChest2;

void code_lock(SDL_Renderer* ren);
void lamps(SDL_Renderer* ren, SDL_Rect& dstLamp);
void runes_puzzle(SDL_Renderer* ren);
void nameplate(SDL_Renderer* ren);
void hint(SDL_Renderer* ren);
bool object_collision(SDL_Rect a, SDL_Rect b);