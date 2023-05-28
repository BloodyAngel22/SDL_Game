#pragma once
#include <SDL.h>
void MenuBattle(SDL_Renderer* ren); 
void StartBattle(); 
void Battle(); 
void recovery_character(); 
int escape();
void generateEnemy(); 
void Battler(SDL_Renderer* ren); 
int randomAmountEnemy();
extern bool isEnterPressed, wasEnterPressed, isPressed;
int pressedEnter();
int pressedEscape();

extern int flag;
extern int livedEnemies;
extern int counterKilledEnemies;