#pragma once
#include "SDL_general.h"
#include <iostream>

void rock_scissors_paper_menu(SDL_Renderer* ren);
int random();
void render_result(SDL_Renderer* ren);
void dialogue(SDL_Renderer* ren);
extern int winningStreak;