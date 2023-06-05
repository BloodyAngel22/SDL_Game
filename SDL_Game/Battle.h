#pragma once
#include <SDL.h>
void MenuBattle(SDL_Renderer* ren, int enemy); 
void StartBattle(); 
void Battle(); 
void recovery_character(); 
int escape();
void generateEnemy(int enemy);
void Battler(SDL_Renderer* ren, int enemy);
int randomAmountEnemy();
extern bool isEnterPressed, wasEnterPressed, isPressed;
extern bool wasEscapePressed, isEscapePressed, isPressedEscape;
int pressedEnter();
int pressedEscape();
void enemy_patterns(int enemy);

#define Bat 1
#define Goblin 2

extern int flag;
extern int livedEnemies;
extern int counterKilledEnemies;