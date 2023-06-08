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
void render_enemy(int enemy, SDL_Renderer* ren, SDL_Texture* textBat, SDL_Texture* textGoblin, SDL_Texture* textSlime, SDL_Texture* textWerewolf, SDL_Texture* textRat);
void check_pattern(SDL_Renderer* ren, SDL_Texture* textIcons);
void render_dead_enemy(SDL_Renderer* ren, SDL_Texture* textdeadEenemy);

#define Bat 1
#define Goblin 2
#define Slime 3
#define Werewolf 4
#define Rat 5

extern int flag;
extern int livedEnemies;
extern int counterKilledEnemies;