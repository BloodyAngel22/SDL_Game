#pragma once
#include "SDL_general.h"

extern int flagCode;
extern int flagLamps;

void code_lock(SDL_Renderer* ren);
void lamps(SDL_Renderer* ren, SDL_Rect& dstLamp);
bool object_collision(SDL_Rect a, SDL_Rect b);