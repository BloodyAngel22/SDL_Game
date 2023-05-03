#pragma once
#include <SDL.h>
void MenuBattle(SDL_Renderer* ren); void StartBattle(); void Battle(); void recovery_character(); int escape();
void generateEnemy(); void Battler(SDL_Renderer* ren); int randomAmountEnemy();

extern int flag;
extern int livedEnemies;