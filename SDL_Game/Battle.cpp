#include <stdio.h>
#include <stdlib.h>
#include "Models.h"
#include "Leveling.h"
#include "Ability.h"
#include "Battle.h"
#include "Quest.h"
#include <SDL.h>
#include <SDL_image.h>
#include <SDL_ttf.h>
#define BATTLE 1
#define ABILITY 2
#define ESCAPE 3
#define ChanceEscape 65
#define FIREBOLT 1
#define LIGHTING 2
#define POISON 3


int abilityDamageLightning = 48, abilityDamageFireball = 30, abilityDamagePoison = 6;
extern bool posionEffect = false;
extern bool lightingEffect = false;
extern int choiceEnemy = 0;
int amountEnemy;
int livedEnemies = 1;
int ratio;
bool isEnterPressed = 0, wasEnterPressed = 0, isPressed = 0, isPressedEscape = 0;
Character hero;
Enemy opponent;
ClassMage mage;
ClassWarrior warrior;
genEnemy enemy1, enemy2, enemy3, enemy4;
SDL_Rect srcrectDeadEnemy = { 0, 0, 100, 140 };
SDL_Rect srcrectBat = { 0, 0, 100, 140 };
SDL_Rect dstrectDeadEnemy1; SDL_Rect dstrectDeadEnemy2; SDL_Rect dstrectDeadEnemy3; SDL_Rect dstrectDeadEnemy4;
SDL_Rect dstrectBat; SDL_Rect dstrectBat2; SDL_Rect dstrectBat3; SDL_Rect dstrectBat4;
int xEnemy1 = 500, yEnemy1 = 100;
int xEnemy2 = 700, yEnemy2 = 100;
int xEnemy3 = 900, yEnemy3 = 100;
int xEnemy4 = 900, yEnemy4 = 100;
int xDeadEnemy1 = 500, yDeadEnemy1 = 100;
int xDeadEnemy2 = 700, yDeadEnemy2 = 100;
int xDeadEnemy3 = 900, yDeadEnemy3 = 100;
int xDeadEnemy4 = 700, yDeadEnemy4 = 100;
int flag = 0;

int pressedEnter() {
	const Uint8* enterState = SDL_GetKeyboardState(NULL);
	wasEnterPressed = 0;
	if (!enterState[SDL_SCANCODE_RETURN]) isEnterPressed = 0;

	if (enterState[SDL_SCANCODE_RETURN] and wasEnterPressed == 0 and isEnterPressed == 0) {
		isEnterPressed = 1;
		return 1;
	}
	else return 0;	
}

int pressedEscape() {
	const Uint8* enterState = SDL_GetKeyboardState(NULL);
	wasEnterPressed = 0;
	if (!enterState[SDL_SCANCODE_ESCAPE]) isEnterPressed = 0;

	if (enterState[SDL_SCANCODE_ESCAPE] and wasEnterPressed == 0 and isEnterPressed == 0) {
		isEnterPressed = 1;
		return 1;
	}
	else return 0;
}

void MenuBattle(SDL_Renderer* ren); void StartBattle(); void Battle(); int escape();

void MenuBattle(SDL_Renderer* ren) {
	#pragma region Texture
		//Battle menu
		SDL_Surface* surfBattle = IMG_Load("sprites\\menu\\battle.png");
		SDL_Texture* textBattle = SDL_CreateTextureFromSurface(ren, surfBattle);
		SDL_FreeSurface(surfBattle);
		//Arrow
		SDL_Surface* surfArrow = IMG_Load("sprites\\menu\\arrow.png");
		SDL_Texture* textArrow = SDL_CreateTextureFromSurface(ren, surfArrow);
		SDL_FreeSurface(surfArrow);
		//
		SDL_Surface* surfdeadEnemy = IMG_Load("sprites\\enemy\\deadEnemy.png");
		SDL_Texture* textdeadEenemy = SDL_CreateTextureFromSurface(ren, surfdeadEnemy);
		SDL_FreeSurface(surfdeadEnemy);
		//
		SDL_Surface* surfBat = IMG_Load("sprites\\enemy\\bat.png");
		SDL_Texture* textBat = SDL_CreateTextureFromSurface(ren, surfBat);
		SDL_FreeSurface(surfBat);
		//
		TTF_Font* enemyTTF = TTF_OpenFont("fonts\\BAUHS93.TTF", 75);
		char enemyHealth[100] = "Points";
		SDL_Surface* surfEnemyHealthTTF = TTF_RenderText_Blended(enemyTTF, enemyHealth, { 255, 255, 255, 255 });
		SDL_Texture* textEnemyHealthTTF = SDL_CreateTextureFromSurface(ren, surfEnemyHealthTTF);
		SDL_Rect size = { 0, 0, surfEnemyHealthTTF->w, surfEnemyHealthTTF->h };
		int xPoint = 500, yPoint = 50;
		SDL_Rect pointsTTF = { xPoint, yPoint, 55, 60 };
		SDL_FreeSurface(surfEnemyHealthTTF);
		//
		SDL_Surface* surfCharacter = IMG_Load("sprites\\character\\character.png");
		SDL_Texture* textCharacter = SDL_CreateTextureFromSurface(ren, surfCharacter);
		SDL_FreeSurface(surfCharacter);
		int xCharacter = 130, yCharacter = 90;
		SDL_Rect srcrectCharacter = { 10, 10, 100, 140 };
		SDL_Rect dstrectCharacter = {xCharacter, yCharacter, 75, 75};
		#pragma endregion
	SDL_Event ev;
	SDL_PollEvent(&ev);
	StartBattle();
	if (flag == 0) {
		generateEnemy();
		amountEnemy = randomAmountEnemy();
		livedEnemies = amountEnemy;
	}
	if (livedEnemies < 1) {
		SDL_DestroyTexture(textBat);
		SDL_DestroyTexture(textArrow);
		SDL_DestroyTexture(textBattle);
		SDL_DestroyTexture(textdeadEenemy);
		SDL_DestroyTexture(textCharacter);
		flag = 1;
		if (questFlag)
			counterKilledEnemies += 1;
		return;
	}

	SDL_SetRenderDrawColor(ren, 200, 200, 200, 0);
	SDL_RenderClear(ren);
	SDL_RenderCopy(ren, textBattle, NULL, NULL);

	while ((hero.Health > 0) and (livedEnemies >= 1)) {
		int choiche = 0;
		int xArrow = 10, yArrow = 310;
		const Uint8* arrowState = SDL_GetKeyboardState(NULL);
		SDL_Rect srcrectArrow = { 0, 0, 100, 140 };
		SDL_Rect dstrectArrow;
		int pointer = 1;
		printf("Health %d, Attack %d, Mana %d, Defense %.2f\n", hero.Health, hero.Attack, hero.Mana, hero.Defense);
		printf("1 - Battle\n2 - Ability\n3 - Escape\n");
		while (choiche == 0) {
			dstrectArrow = { xArrow, yArrow, 75, 75 };
			SDL_RenderCopy(ren, textCharacter, &srcrectCharacter, &dstrectCharacter);
			if (amountEnemy == 2) {
				dstrectBat = { xEnemy1, yEnemy1, 75, 75 };
				dstrectBat2 = { xEnemy2, yEnemy2, 75, 75 };
				SDL_RenderCopy(ren, textBat, &srcrectBat, &dstrectBat);
				SDL_RenderCopy(ren, textBat, &srcrectBat, &dstrectBat2);
			}
			if (amountEnemy == 3) {
				dstrectBat = { xEnemy1, yEnemy1, 75, 75 };
				dstrectBat2 = { xEnemy2, yEnemy2, 75, 75 };
				dstrectBat3 = { xEnemy3, yEnemy3, 75, 75 };
				SDL_RenderCopy(ren, textBat, &srcrectBat, &dstrectBat);
				SDL_RenderCopy(ren, textBat, &srcrectBat, &dstrectBat2);
				SDL_RenderCopy(ren, textBat, &srcrectBat, &dstrectBat3);
			}
			if (enemy1.health <= 0) {
				dstrectDeadEnemy1 = { xDeadEnemy1, yDeadEnemy1, 75, 75 };
				SDL_RenderCopy(ren, textdeadEenemy, &srcrectDeadEnemy, &dstrectDeadEnemy1);
			}
			if (enemy2.health <= 0) {
				dstrectDeadEnemy2 = { xDeadEnemy2, yDeadEnemy2, 75, 75 };
				SDL_RenderCopy(ren, textdeadEenemy, &srcrectDeadEnemy, &dstrectDeadEnemy2);
			}
			if (enemy3.health <= 0) {
				dstrectDeadEnemy3 = { xDeadEnemy3, yDeadEnemy3, 75, 75 };
				SDL_RenderCopy(ren, textdeadEenemy, &srcrectDeadEnemy, &dstrectDeadEnemy3);
			}
			

			SDL_RenderPresent(ren);
			while (SDL_PollEvent(&ev) != NULL) {
				switch (ev.type) {
				case SDL_KEYDOWN:
					switch (ev.key.keysym.scancode) {
					case SDL_SCANCODE_UP:
						if (pointer != 1) {
							yArrow -= 125;
							pointer--;
						}
						break;
					case SDL_SCANCODE_W:
						if (pointer != 1) {
							yArrow -= 125;
							pointer--;
						}
						break;
					case SDL_SCANCODE_DOWN:
						if (pointer != 3) {
							yArrow += 125;
							pointer++;
						}
						break;
					case SDL_SCANCODE_S:
						if (pointer != 3) {
							yArrow += 125;
							pointer++;
						}
						break;
					}
				}
				isPressed = pressedEnter();

				SDL_RenderClear(ren);
				SDL_RenderCopy(ren, textBattle, NULL, NULL);
				if (amountEnemy == 2) {
					if (enemy1.health <= 0) enemy1.health = 0;
					if (enemy2.health <= 0) enemy2.health = 0;
					xPoint = 500, yPoint = 50;
					pointsTTF = { xPoint, yPoint, 55, 60 };
					sprintf_s(enemyHealth, "%d", enemy1.health);
					surfEnemyHealthTTF = TTF_RenderText_Blended(enemyTTF, enemyHealth, { 255, 255, 255, 255 });
					size = { 0, 0, surfEnemyHealthTTF->w, surfEnemyHealthTTF->h };
					textEnemyHealthTTF = SDL_CreateTextureFromSurface(ren, surfEnemyHealthTTF);
					SDL_RenderCopy(ren, textEnemyHealthTTF, &size, &pointsTTF);
					SDL_FreeSurface(surfEnemyHealthTTF);
					SDL_DestroyTexture(textEnemyHealthTTF);

					xPoint = 700, yPoint = 50;
					pointsTTF = { xPoint, yPoint, 55, 60 };
					sprintf_s(enemyHealth, "%d", enemy2.health);
					surfEnemyHealthTTF = TTF_RenderText_Blended(enemyTTF, enemyHealth, { 255, 255, 255, 255 });
					size = { 0, 0, surfEnemyHealthTTF->w, surfEnemyHealthTTF->h };
					textEnemyHealthTTF = SDL_CreateTextureFromSurface(ren, surfEnemyHealthTTF);
					SDL_RenderCopy(ren, textEnemyHealthTTF, &size, &pointsTTF);
					SDL_FreeSurface(surfEnemyHealthTTF);
					SDL_DestroyTexture(textEnemyHealthTTF);

					xPoint = 65, yPoint = 50;
					pointsTTF = { xPoint, yPoint, 75, 60 };
					sprintf_s(enemyHealth, "h %d", hero.Health);
					surfEnemyHealthTTF = TTF_RenderText_Blended(enemyTTF, enemyHealth, { 255, 255, 255, 255 });
					size = { 0, 0, surfEnemyHealthTTF->w, surfEnemyHealthTTF->h };
					textEnemyHealthTTF = SDL_CreateTextureFromSurface(ren, surfEnemyHealthTTF);
					SDL_RenderCopy(ren, textEnemyHealthTTF, &size, &pointsTTF);
					SDL_FreeSurface(surfEnemyHealthTTF);
					SDL_DestroyTexture(textEnemyHealthTTF);

					xPoint = 65, yPoint = 90;
					pointsTTF = { xPoint, yPoint, 75, 60 };
					sprintf_s(enemyHealth, "m %d", hero.Mana);
					surfEnemyHealthTTF = TTF_RenderText_Blended(enemyTTF, enemyHealth, { 255, 255, 255, 255 });
					size = { 0, 0, surfEnemyHealthTTF->w, surfEnemyHealthTTF->h };
					textEnemyHealthTTF = SDL_CreateTextureFromSurface(ren, surfEnemyHealthTTF);
					SDL_RenderCopy(ren, textEnemyHealthTTF, &size, &pointsTTF);
					SDL_FreeSurface(surfEnemyHealthTTF);
					SDL_DestroyTexture(textEnemyHealthTTF);
				}
				if (amountEnemy == 3) {
					if (enemy1.health <= 0) enemy1.health = 0;
					if (enemy2.health <= 0) enemy2.health = 0;
					if (enemy3.health <= 0) enemy3.health = 0;
					xPoint = 500, yPoint = 50;
					pointsTTF = { xPoint, yPoint, 55, 60 };
					sprintf_s(enemyHealth, "%d", enemy1.health);
					surfEnemyHealthTTF = TTF_RenderText_Blended(enemyTTF, enemyHealth, { 255, 255, 255, 255 });
					size = { 0, 0, surfEnemyHealthTTF->w, surfEnemyHealthTTF->h };
					textEnemyHealthTTF = SDL_CreateTextureFromSurface(ren, surfEnemyHealthTTF);
					SDL_RenderCopy(ren, textEnemyHealthTTF, &size, &pointsTTF);
					SDL_FreeSurface(surfEnemyHealthTTF);
					SDL_DestroyTexture(textEnemyHealthTTF);


					xPoint = 700, yPoint = 50;
					pointsTTF = { xPoint, yPoint, 55, 60 };
					sprintf_s(enemyHealth, "%d", enemy2.health);
					surfEnemyHealthTTF = TTF_RenderText_Blended(enemyTTF, enemyHealth, { 255, 255, 255, 255 });
					size = { 0, 0, surfEnemyHealthTTF->w, surfEnemyHealthTTF->h };
					textEnemyHealthTTF = SDL_CreateTextureFromSurface(ren, surfEnemyHealthTTF);
					SDL_RenderCopy(ren, textEnemyHealthTTF, &size, &pointsTTF);
					SDL_FreeSurface(surfEnemyHealthTTF);
					SDL_DestroyTexture(textEnemyHealthTTF);


					xPoint = 900, yPoint = 50;
					pointsTTF = { xPoint, yPoint, 55, 60 };
					sprintf_s(enemyHealth, "%d", enemy3.health);
					surfEnemyHealthTTF = TTF_RenderText_Blended(enemyTTF, enemyHealth, { 255, 255, 255, 255 });
					size = { 0, 0, surfEnemyHealthTTF->w, surfEnemyHealthTTF->h };
					textEnemyHealthTTF = SDL_CreateTextureFromSurface(ren, surfEnemyHealthTTF);
					SDL_RenderCopy(ren, textEnemyHealthTTF, &size, &pointsTTF);
					SDL_FreeSurface(surfEnemyHealthTTF);
					SDL_DestroyTexture(textEnemyHealthTTF);

					xPoint = 65, yPoint = 50;
					pointsTTF = { xPoint, yPoint, 75, 60 };
					sprintf_s(enemyHealth, "h %d", hero.Health);
					surfEnemyHealthTTF = TTF_RenderText_Blended(enemyTTF, enemyHealth, { 255, 255, 255, 255 });
					size = { 0, 0, surfEnemyHealthTTF->w, surfEnemyHealthTTF->h };
					textEnemyHealthTTF = SDL_CreateTextureFromSurface(ren, surfEnemyHealthTTF);
					SDL_RenderCopy(ren, textEnemyHealthTTF, &size, &pointsTTF);
					SDL_FreeSurface(surfEnemyHealthTTF);
					SDL_DestroyTexture(textEnemyHealthTTF);

					xPoint = 65, yPoint = 90;
					pointsTTF = { xPoint, yPoint, 75, 60 };
					sprintf_s(enemyHealth, "m %d", hero.Mana);
					surfEnemyHealthTTF = TTF_RenderText_Blended(enemyTTF, enemyHealth, { 255, 255, 255, 255 });
					size = { 0, 0, surfEnemyHealthTTF->w, surfEnemyHealthTTF->h };
					textEnemyHealthTTF = SDL_CreateTextureFromSurface(ren, surfEnemyHealthTTF);
					SDL_RenderCopy(ren, textEnemyHealthTTF, &size, &pointsTTF);
					SDL_FreeSurface(surfEnemyHealthTTF);
					SDL_DestroyTexture(textEnemyHealthTTF);
				}

				SDL_RenderCopy(ren, textArrow, &srcrectArrow, &dstrectArrow);
				SDL_RenderPresent(ren);
				SDL_DestroyTexture(textEnemyHealthTTF);

			}

			if (pointer == 1 and arrowState[SDL_SCANCODE_RETURN] and isPressed == 1) choiche = BATTLE;
			if (pointer == 2 and arrowState[SDL_SCANCODE_RETURN] and isPressed == 1) choiche = ABILITY;
			if (pointer == 3 and arrowState[SDL_SCANCODE_RETURN] and isPressed == 1) choiche = ESCAPE;
			isPressed = 0;
		}
			if (choiche == BATTLE) {
				//SDL_Delay(250);
				system("cls");
				Battler(ren);
				if (enemy1.isPoison == true or enemy2.isPoison == true or enemy3.isPoison == true) Poison();
				printf("%d\n", opponent.Health);
			}
			else if (choiche == ABILITY) {
				flag = 1;
				system("cls");
				//SDL_Delay(250);
				int choiceSpell = 0;
				printf("1 - Firebolt\n2 - Lightning\n3 - Posion\n");
				pointer = 1;
				xArrow = 310, yArrow = 310;
				while (choiceSpell == 0) {
					dstrectArrow = { xArrow, yArrow, 75, 75 };
					SDL_SetRenderDrawColor(ren, 200, 200, 200, 0);
					SDL_RenderClear(ren);
					SDL_RenderCopy(ren, textBattle, NULL, NULL);
					SDL_RenderCopy(ren, textCharacter, &srcrectCharacter, &dstrectCharacter);
					if (amountEnemy == 2) {
						dstrectBat = { xEnemy1, yEnemy1, 75, 75 };
						dstrectBat2 = { xEnemy2, yEnemy2, 75, 75 };
						SDL_RenderCopy(ren, textBat, &srcrectBat, &dstrectBat);
						SDL_RenderCopy(ren, textBat, &srcrectBat, &dstrectBat2);
					}
					if (amountEnemy == 3) {
						dstrectBat = { xEnemy1, yEnemy1, 75, 75 };
						dstrectBat2 = { xEnemy2, yEnemy2, 75, 75 };
						dstrectBat3 = { xEnemy3, yEnemy3, 75, 75 };
						SDL_RenderCopy(ren, textBat, &srcrectBat, &dstrectBat);
						SDL_RenderCopy(ren, textBat, &srcrectBat, &dstrectBat2);
						SDL_RenderCopy(ren, textBat, &srcrectBat, &dstrectBat3);
					}
					if (enemy1.health <= 0) {
						dstrectDeadEnemy1 = { xDeadEnemy1, yDeadEnemy1, 75, 75 };
						SDL_RenderCopy(ren, textdeadEenemy, &srcrectDeadEnemy, &dstrectDeadEnemy1);
					}
					if (enemy2.health <= 0) {
						dstrectDeadEnemy2 = { xDeadEnemy2, yDeadEnemy2, 75, 75 };
						SDL_RenderCopy(ren, textdeadEenemy, &srcrectDeadEnemy, &dstrectDeadEnemy2);
					}
					if (enemy3.health <= 0) {
						dstrectDeadEnemy3 = { xDeadEnemy3, yDeadEnemy3, 75, 75 };
						SDL_RenderCopy(ren, textdeadEenemy, &srcrectDeadEnemy, &dstrectDeadEnemy3);
					}
					SDL_RenderCopy(ren, textArrow, &srcrectArrow, &dstrectArrow);
					if (amountEnemy == 2) {
						if (enemy1.health <= 0) enemy1.health = 0;
						if (enemy2.health <= 0) enemy2.health = 0;
						xPoint = 500, yPoint = 50;
						pointsTTF = { xPoint, yPoint, 55, 60 };
						sprintf_s(enemyHealth, "%d", enemy1.health);
						surfEnemyHealthTTF = TTF_RenderText_Blended(enemyTTF, enemyHealth, { 255, 255, 255, 255 });
						size = { 0, 0, surfEnemyHealthTTF->w, surfEnemyHealthTTF->h };
						textEnemyHealthTTF = SDL_CreateTextureFromSurface(ren, surfEnemyHealthTTF);
						SDL_RenderCopy(ren, textEnemyHealthTTF, &size, &pointsTTF);
						SDL_FreeSurface(surfEnemyHealthTTF);
						SDL_DestroyTexture(textEnemyHealthTTF);

						xPoint = 700, yPoint = 50;
						pointsTTF = { xPoint, yPoint, 55, 60 };
						sprintf_s(enemyHealth, "%d", enemy2.health);
						surfEnemyHealthTTF = TTF_RenderText_Blended(enemyTTF, enemyHealth, { 255, 255, 255, 255 });
						size = { 0, 0, surfEnemyHealthTTF->w, surfEnemyHealthTTF->h };
						textEnemyHealthTTF = SDL_CreateTextureFromSurface(ren, surfEnemyHealthTTF);
						SDL_RenderCopy(ren, textEnemyHealthTTF, &size, &pointsTTF);
						SDL_FreeSurface(surfEnemyHealthTTF);
						SDL_DestroyTexture(textEnemyHealthTTF);

						xPoint = 65, yPoint = 50;
						pointsTTF = { xPoint, yPoint, 75, 60 };
						sprintf_s(enemyHealth, "h %d", hero.Health);
						surfEnemyHealthTTF = TTF_RenderText_Blended(enemyTTF, enemyHealth, { 255, 255, 255, 255 });
						size = { 0, 0, surfEnemyHealthTTF->w, surfEnemyHealthTTF->h };
						textEnemyHealthTTF = SDL_CreateTextureFromSurface(ren, surfEnemyHealthTTF);
						SDL_RenderCopy(ren, textEnemyHealthTTF, &size, &pointsTTF);
						SDL_FreeSurface(surfEnemyHealthTTF);
						SDL_DestroyTexture(textEnemyHealthTTF);

						xPoint = 65, yPoint = 90;
						pointsTTF = { xPoint, yPoint, 75, 60 };
						sprintf_s(enemyHealth, "m %d", hero.Mana);
						surfEnemyHealthTTF = TTF_RenderText_Blended(enemyTTF, enemyHealth, { 255, 255, 255, 255 });
						size = { 0, 0, surfEnemyHealthTTF->w, surfEnemyHealthTTF->h };
						textEnemyHealthTTF = SDL_CreateTextureFromSurface(ren, surfEnemyHealthTTF);
						SDL_RenderCopy(ren, textEnemyHealthTTF, &size, &pointsTTF);
						SDL_FreeSurface(surfEnemyHealthTTF);
						SDL_DestroyTexture(textEnemyHealthTTF);
					}
					if (amountEnemy == 3) {
						if (enemy1.health <= 0) enemy1.health = 0;
						if (enemy2.health <= 0) enemy2.health = 0;
						if (enemy3.health <= 0) enemy3.health = 0;
						xPoint = 500, yPoint = 50;
						pointsTTF = { xPoint, yPoint, 55, 60 };
						sprintf_s(enemyHealth, "%d", enemy1.health);
						surfEnemyHealthTTF = TTF_RenderText_Blended(enemyTTF, enemyHealth, { 255, 255, 255, 255 });
						size = { 0, 0, surfEnemyHealthTTF->w, surfEnemyHealthTTF->h };
						textEnemyHealthTTF = SDL_CreateTextureFromSurface(ren, surfEnemyHealthTTF);
						SDL_RenderCopy(ren, textEnemyHealthTTF, &size, &pointsTTF);
						SDL_FreeSurface(surfEnemyHealthTTF);
						SDL_DestroyTexture(textEnemyHealthTTF);


						xPoint = 700, yPoint = 50;
						pointsTTF = { xPoint, yPoint, 55, 60 };
						sprintf_s(enemyHealth, "%d", enemy2.health);
						surfEnemyHealthTTF = TTF_RenderText_Blended(enemyTTF, enemyHealth, { 255, 255, 255, 255 });
						size = { 0, 0, surfEnemyHealthTTF->w, surfEnemyHealthTTF->h };
						textEnemyHealthTTF = SDL_CreateTextureFromSurface(ren, surfEnemyHealthTTF);
						SDL_RenderCopy(ren, textEnemyHealthTTF, &size, &pointsTTF);
						SDL_FreeSurface(surfEnemyHealthTTF);
						SDL_DestroyTexture(textEnemyHealthTTF);


						xPoint = 900, yPoint = 50;
						pointsTTF = { xPoint, yPoint, 55, 60 };
						sprintf_s(enemyHealth, "%d", enemy3.health);
						surfEnemyHealthTTF = TTF_RenderText_Blended(enemyTTF, enemyHealth, { 255, 255, 255, 255 });
						size = { 0, 0, surfEnemyHealthTTF->w, surfEnemyHealthTTF->h };
						textEnemyHealthTTF = SDL_CreateTextureFromSurface(ren, surfEnemyHealthTTF);
						SDL_RenderCopy(ren, textEnemyHealthTTF, &size, &pointsTTF);
						SDL_FreeSurface(surfEnemyHealthTTF);
						SDL_DestroyTexture(textEnemyHealthTTF);

						xPoint = 65, yPoint = 50;
						pointsTTF = { xPoint, yPoint, 75, 60 };
						sprintf_s(enemyHealth, "h %d", hero.Health);
						surfEnemyHealthTTF = TTF_RenderText_Blended(enemyTTF, enemyHealth, { 255, 255, 255, 255 });
						size = { 0, 0, surfEnemyHealthTTF->w, surfEnemyHealthTTF->h };
						textEnemyHealthTTF = SDL_CreateTextureFromSurface(ren, surfEnemyHealthTTF);
						SDL_RenderCopy(ren, textEnemyHealthTTF, &size, &pointsTTF);
						SDL_FreeSurface(surfEnemyHealthTTF);
						SDL_DestroyTexture(textEnemyHealthTTF);

						xPoint = 65, yPoint = 90;
						pointsTTF = { xPoint, yPoint, 75, 60 };
						sprintf_s(enemyHealth, "m %d", hero.Mana);
						surfEnemyHealthTTF = TTF_RenderText_Blended(enemyTTF, enemyHealth, { 255, 255, 255, 255 });
						size = { 0, 0, surfEnemyHealthTTF->w, surfEnemyHealthTTF->h };
						textEnemyHealthTTF = SDL_CreateTextureFromSurface(ren, surfEnemyHealthTTF);
						SDL_RenderCopy(ren, textEnemyHealthTTF, &size, &pointsTTF);
						SDL_FreeSurface(surfEnemyHealthTTF);
						SDL_DestroyTexture(textEnemyHealthTTF);
					}

					SDL_RenderPresent(ren);
					while (SDL_PollEvent(&ev) != NULL) {
						switch (ev.type) {
						case SDL_KEYDOWN:
							switch (ev.key.keysym.scancode) {
							case SDL_SCANCODE_UP:
								if (pointer != 1) {
									yArrow -= 125;
									pointer--;
								}
								break;
							case SDL_SCANCODE_W:
								if (pointer != 1) {
									yArrow -= 125;
									pointer--;
								}
								break;
							case SDL_SCANCODE_DOWN:
								if (pointer != 3) {
									yArrow += 125;
									pointer++;
								}
								break;
							case SDL_SCANCODE_S:
								if (pointer != 3) {
									yArrow += 125;
									pointer++;
								}
								break;
							}
						}
						isPressed = pressedEnter();

					}
					if (pointer == 1 and arrowState[SDL_SCANCODE_RETURN] and isPressed) choiceSpell = FIREBOLT;
					if (pointer == 2 and arrowState[SDL_SCANCODE_RETURN] and isPressed) choiceSpell = LIGHTING;
					if (pointer == 3 and arrowState[SDL_SCANCODE_RETURN] and isPressed) choiceSpell = POISON;
					isPressed = 0;
				}
				//SDL_Delay(300);
				choiceEnemy = 0;
				xArrow = 450, yArrow = 100;
				pointer = 1;
				if (amountEnemy == 2) {
					while (choiceEnemy == 0) {
						srcrectArrow = { 0, 0, 100, 140 };
						dstrectArrow = { xArrow, yArrow, 75, 75 };
						SDL_SetRenderDrawColor(ren, 200, 200, 200, 0);
						SDL_RenderClear(ren);
						SDL_RenderCopy(ren, textBattle, NULL, NULL);
						SDL_RenderCopy(ren, textCharacter, &srcrectCharacter, &dstrectCharacter);

						if (amountEnemy == 2) {
							if (enemy1.health <= 0) enemy1.health = 0;
							if (enemy2.health <= 0) enemy2.health = 0;
							xPoint = 500, yPoint = 50;
							pointsTTF = { xPoint, yPoint, 55, 60 };
							sprintf_s(enemyHealth, "%d", enemy1.health);
							surfEnemyHealthTTF = TTF_RenderText_Blended(enemyTTF, enemyHealth, { 255, 255, 255, 255 });
							size = { 0, 0, surfEnemyHealthTTF->w, surfEnemyHealthTTF->h };
							textEnemyHealthTTF = SDL_CreateTextureFromSurface(ren, surfEnemyHealthTTF);
							SDL_RenderCopy(ren, textEnemyHealthTTF, &size, &pointsTTF);
							SDL_FreeSurface(surfEnemyHealthTTF);
							SDL_DestroyTexture(textEnemyHealthTTF);

							xPoint = 700, yPoint = 50;
							pointsTTF = { xPoint, yPoint, 55, 60 };
							sprintf_s(enemyHealth, "%d", enemy2.health);
							surfEnemyHealthTTF = TTF_RenderText_Blended(enemyTTF, enemyHealth, { 255, 255, 255, 255 });
							size = { 0, 0, surfEnemyHealthTTF->w, surfEnemyHealthTTF->h };
							textEnemyHealthTTF = SDL_CreateTextureFromSurface(ren, surfEnemyHealthTTF);
							SDL_RenderCopy(ren, textEnemyHealthTTF, &size, &pointsTTF);
							SDL_FreeSurface(surfEnemyHealthTTF);
							SDL_DestroyTexture(textEnemyHealthTTF);

							xPoint = 65, yPoint = 50;
							pointsTTF = { xPoint, yPoint, 75, 60 };
							sprintf_s(enemyHealth, "h %d", hero.Health);
							surfEnemyHealthTTF = TTF_RenderText_Blended(enemyTTF, enemyHealth, { 255, 255, 255, 255 });
							size = { 0, 0, surfEnemyHealthTTF->w, surfEnemyHealthTTF->h };
							textEnemyHealthTTF = SDL_CreateTextureFromSurface(ren, surfEnemyHealthTTF);
							SDL_RenderCopy(ren, textEnemyHealthTTF, &size, &pointsTTF);
							SDL_FreeSurface(surfEnemyHealthTTF);
							SDL_DestroyTexture(textEnemyHealthTTF);

							xPoint = 65, yPoint = 90;
							pointsTTF = { xPoint, yPoint, 75, 60 };
							sprintf_s(enemyHealth, "m %d", hero.Mana);
							surfEnemyHealthTTF = TTF_RenderText_Blended(enemyTTF, enemyHealth, { 255, 255, 255, 255 });
							size = { 0, 0, surfEnemyHealthTTF->w, surfEnemyHealthTTF->h };
							textEnemyHealthTTF = SDL_CreateTextureFromSurface(ren, surfEnemyHealthTTF);
							SDL_RenderCopy(ren, textEnemyHealthTTF, &size, &pointsTTF);
							SDL_FreeSurface(surfEnemyHealthTTF);
							SDL_DestroyTexture(textEnemyHealthTTF);
						}
						dstrectBat = { xEnemy1, yEnemy1, 75, 75 };
						dstrectBat2 = { xEnemy2, yEnemy2, 75, 75 };
						SDL_RenderCopy(ren, textBat, &srcrectBat, &dstrectBat);
						SDL_RenderCopy(ren, textBat, &srcrectBat, &dstrectBat2);
						if (enemy1.health <= 0) {
							dstrectDeadEnemy1 = { xDeadEnemy1, yDeadEnemy1, 75, 75 };
							SDL_RenderCopy(ren, textdeadEenemy, &srcrectDeadEnemy, &dstrectDeadEnemy1);
							
						}
						if (enemy2.health <= 0) {
							dstrectDeadEnemy2 = { xDeadEnemy2, yDeadEnemy2, 75, 75 };
							SDL_RenderCopy(ren, textdeadEenemy, &srcrectDeadEnemy, &dstrectDeadEnemy2);
							
						}
						if (enemy1.health <= 0) {
							pointer = 2;
							xArrow = 650, yArrow = 100;
						}
						if (enemy2.health <= 0) {
							pointer = 1;
							xArrow = 450, yArrow = 100;
						}
						SDL_RenderCopy(ren, textArrow, &srcrectArrow, &dstrectArrow);
						SDL_RenderPresent(ren);
						while (SDL_PollEvent(&ev) != NULL) {
							switch (ev.type) {
							case SDL_KEYDOWN:
								switch (ev.key.keysym.scancode) {
								case SDL_SCANCODE_LEFT:
									if (pointer != 1 and enemy1.health > 0) {
										xArrow -= 200;
										pointer--;
									}
									break;
								case SDL_SCANCODE_A:
									if (pointer != 1 and enemy1.health > 0) {
										xArrow -= 200;
										pointer--;
									}
									break;
								case SDL_SCANCODE_RIGHT:
									if (pointer != 2 and enemy2.health > 0) {
										xArrow += 200;
										pointer++;
									}
									break;
								case SDL_SCANCODE_D:
									if (pointer != 2 and enemy2.health > 0) {
										xArrow += 200;
										pointer++;
									}
									break;
								}

							}
							isPressed = pressedEnter();

						}
						if (pointer == 1 and arrowState[SDL_SCANCODE_RETURN] and isPressed) choiceEnemy = 1;
						if (pointer == 2 and arrowState[SDL_SCANCODE_RETURN] and isPressed) choiceEnemy = 2;
						isPressed = 0;
					}
					if (choiceEnemy == 1) {
						//SDL_Delay(150);
						if (choiceSpell == FIREBOLT) {
							Fireball();
							if (enemy1.health > 0) 
								hero.Health = hero.Health - (enemy1.atk - (enemy1.atk * hero.Defense));
							else {
								enemy1.atk = 0;
								livedEnemies--;
							}
						}
						else if (choiceSpell == LIGHTING) {
							Lightning();
							if (enemy1.health > 0)
								hero.Health = hero.Health - (enemy1.atk - (enemy1.atk * hero.Defense));
							else {
								enemy1.atk = 0;
								livedEnemies--;
							}
						}
						else if (choiceSpell == POISON) {
							Poison();
							if (enemy1.health > 0)
								hero.Health = hero.Health - (enemy1.atk - (enemy1.atk * hero.Defense));
							else {
								enemy1.atk = 0;
								livedEnemies--;
							}
						}
					}
					else if (choiceEnemy == 2) {
						//SDL_Delay(150);
						if (choiceSpell == FIREBOLT) {
							Fireball();
							if (enemy2.health > 0)
								hero.Health = hero.Health - (enemy2.atk - (enemy2.atk * hero.Defense));
							else {
								enemy2.atk = 0;
								livedEnemies--;
							}
						}
						if (choiceSpell == LIGHTING) {
							Lightning();
							if (enemy2.health > 0)
								hero.Health = hero.Health - (enemy2.atk - (enemy2.atk * hero.Defense));
							else {
								enemy2.atk = 0;
								livedEnemies--;
							}
						}
						if (choiceSpell == POISON) {
							Poison();
							if (enemy2.health > 0)
								hero.Health = hero.Health - (enemy2.atk - (enemy2.atk * hero.Defense));
							else {
								enemy2.atk = 0;
								livedEnemies--;
							}
						}
					}
				}
				if (amountEnemy == 3) {
					if (enemy2.health > 0) {
						pointer = 2;
						xArrow = 650, yArrow = 100;
					}
					if (enemy2.health <= 0 and enemy3.health > 0) {
						pointer = 3;
						xArrow = 850, yArrow = 100;
					}
					if (enemy1.health > 0) {
						pointer = 1;
						xArrow = 450, yArrow = 100;
					}
					if (enemy1.health <= 0 and enemy3.health > 0) {
						pointer = 3;
						xArrow = 850, yArrow = 100;
					}
					if (enemy1.health <= 0 and enemy2.health > 0) {
						pointer = 2;
						xArrow = 650, yArrow = 100;
					}
					while (choiceEnemy == 0) {
						//SDL_Delay(150);
						dstrectArrow = { xArrow, yArrow, 75, 75 };
						SDL_SetRenderDrawColor(ren, 200, 200, 200, 0);
						SDL_RenderClear(ren);
						SDL_RenderCopy(ren, textBattle, NULL, NULL);
						SDL_RenderCopy(ren, textCharacter, &srcrectCharacter, &dstrectCharacter);

						if (amountEnemy == 3) {
							if (enemy1.health <= 0) enemy1.health = 0;
							if (enemy2.health <= 0) enemy2.health = 0;
							if (enemy3.health <= 0) enemy3.health = 0;
							xPoint = 500, yPoint = 50;
							pointsTTF = { xPoint, yPoint, 55, 60 };
							sprintf_s(enemyHealth, "%d", enemy1.health);
							surfEnemyHealthTTF = TTF_RenderText_Blended(enemyTTF, enemyHealth, { 255, 255, 255, 255 });
							size = { 0, 0, surfEnemyHealthTTF->w, surfEnemyHealthTTF->h };
							textEnemyHealthTTF = SDL_CreateTextureFromSurface(ren, surfEnemyHealthTTF);
							SDL_RenderCopy(ren, textEnemyHealthTTF, &size, &pointsTTF);
							SDL_FreeSurface(surfEnemyHealthTTF);
							SDL_DestroyTexture(textEnemyHealthTTF);


							xPoint = 700, yPoint = 50;
							pointsTTF = { xPoint, yPoint, 55, 60 };
							sprintf_s(enemyHealth, "%d", enemy2.health);
							surfEnemyHealthTTF = TTF_RenderText_Blended(enemyTTF, enemyHealth, { 255, 255, 255, 255 });
							size = { 0, 0, surfEnemyHealthTTF->w, surfEnemyHealthTTF->h };
							textEnemyHealthTTF = SDL_CreateTextureFromSurface(ren, surfEnemyHealthTTF);
							SDL_RenderCopy(ren, textEnemyHealthTTF, &size, &pointsTTF);
							SDL_FreeSurface(surfEnemyHealthTTF);
							SDL_DestroyTexture(textEnemyHealthTTF);


							xPoint = 900, yPoint = 50;
							pointsTTF = { xPoint, yPoint, 55, 60 };
							sprintf_s(enemyHealth, "%d", enemy3.health);
							surfEnemyHealthTTF = TTF_RenderText_Blended(enemyTTF, enemyHealth, { 255, 255, 255, 255 });
							size = { 0, 0, surfEnemyHealthTTF->w, surfEnemyHealthTTF->h };
							textEnemyHealthTTF = SDL_CreateTextureFromSurface(ren, surfEnemyHealthTTF);
							SDL_RenderCopy(ren, textEnemyHealthTTF, &size, &pointsTTF);
							SDL_FreeSurface(surfEnemyHealthTTF);
							SDL_DestroyTexture(textEnemyHealthTTF);

							xPoint = 65, yPoint = 50;
							pointsTTF = { xPoint, yPoint, 75, 60 };
							sprintf_s(enemyHealth, "h %d", hero.Health);
							surfEnemyHealthTTF = TTF_RenderText_Blended(enemyTTF, enemyHealth, { 255, 255, 255, 255 });
							size = { 0, 0, surfEnemyHealthTTF->w, surfEnemyHealthTTF->h };
							textEnemyHealthTTF = SDL_CreateTextureFromSurface(ren, surfEnemyHealthTTF);
							SDL_RenderCopy(ren, textEnemyHealthTTF, &size, &pointsTTF);
							SDL_FreeSurface(surfEnemyHealthTTF);
							SDL_DestroyTexture(textEnemyHealthTTF);

							xPoint = 65, yPoint = 90;
							pointsTTF = { xPoint, yPoint, 75, 60 };
							sprintf_s(enemyHealth, "m %d", hero.Mana);
							surfEnemyHealthTTF = TTF_RenderText_Blended(enemyTTF, enemyHealth, { 255, 255, 255, 255 });
							size = { 0, 0, surfEnemyHealthTTF->w, surfEnemyHealthTTF->h };
							textEnemyHealthTTF = SDL_CreateTextureFromSurface(ren, surfEnemyHealthTTF);
							SDL_RenderCopy(ren, textEnemyHealthTTF, &size, &pointsTTF);
							SDL_FreeSurface(surfEnemyHealthTTF);
							SDL_DestroyTexture(textEnemyHealthTTF);
						}

						dstrectBat = { xEnemy1, yEnemy1, 75, 75 };
						dstrectBat2 = { xEnemy2, yEnemy2, 75, 75 };
						SDL_RenderCopy(ren, textBat, &srcrectBat, &dstrectBat);
						SDL_RenderCopy(ren, textBat, &srcrectBat, &dstrectBat2);
						SDL_RenderCopy(ren, textBat, &srcrectBat, &dstrectBat3);
						if (enemy1.health <= 0) {
							dstrectDeadEnemy1 = { xDeadEnemy1, yDeadEnemy1, 75, 75 };
							SDL_RenderCopy(ren, textdeadEenemy, &srcrectDeadEnemy, &dstrectDeadEnemy1);
							
						}
						if (enemy2.health <= 0) {
							dstrectDeadEnemy2 = { xDeadEnemy2, yDeadEnemy2, 75, 75 };
							SDL_RenderCopy(ren, textdeadEenemy, &srcrectDeadEnemy, &dstrectDeadEnemy2);
							
						}
						if (enemy3.health <= 0) {
							dstrectDeadEnemy3 = { xDeadEnemy3, yDeadEnemy3, 75, 75 };
							SDL_RenderCopy(ren, textdeadEenemy, &srcrectDeadEnemy, &dstrectDeadEnemy3);
							
						}
						SDL_RenderCopy(ren, textArrow, &srcrectArrow, &dstrectArrow);
						SDL_RenderPresent(ren);
						while (SDL_PollEvent(&ev) != NULL) {
							switch (ev.type) {
							case SDL_KEYDOWN:
								switch (ev.key.keysym.scancode) {
								case SDL_SCANCODE_LEFT:
									if (pointer != 1) {
										xArrow -= 200;
										pointer--;
									}
									if (pointer == 1 and enemy1.health <= 0) {
										xArrow = 650, pointer = 2;
										if (pointer == 2 and enemy2.health <= 0) {
											xArrow = 850, pointer = 3;
										}
									}
									if (pointer == 2 and enemy2.health <= 0) {
										xArrow = 450, pointer = 1;
										if (pointer == 1 and enemy1.health <= 0) {
											xArrow = 850, pointer = 3;
										}
									}
									if (pointer == 3 and enemy3.health <= 0) {
										xArrow = 450, pointer = 1;
										if (pointer == 1 and enemy1.health <= 0) {
											xArrow = 650, pointer = 2;
										}
									}
									break;
								case SDL_SCANCODE_A:
									if (pointer != 1) {
										xArrow -= 200;
										pointer--;
									}
									if (pointer == 1 and enemy1.health <= 0) {
										xArrow = 650, pointer = 2;
										if (pointer == 2 and enemy2.health <= 0) {
											xArrow = 850, pointer = 3;
										}
									}
									if (pointer == 2 and enemy2.health <= 0) {
										xArrow = 450, pointer = 1;
										if (pointer == 1 and enemy1.health <= 0) {
											xArrow = 850, pointer = 3;
										}
									}
									if (pointer == 3 and enemy3.health <= 0) {
										xArrow = 450, pointer = 1;
										if (pointer == 1 and enemy1.health <= 0) {
											xArrow = 650, pointer = 2;
										}
									}
									break;
								case SDL_SCANCODE_RIGHT:
									if (pointer != 3) {
										xArrow += 200, pointer++;
									}
									if (pointer == 1 and enemy1.health <= 0) {
										xArrow = 650, pointer = 2;
										if (pointer == 2 and enemy2.health <= 0) {
											xArrow = 850, pointer = 3;
										}
									}
									if (pointer == 2 and enemy2.health <= 0) {
										xArrow = 850, pointer = 3;
										if (pointer == 3 and enemy3.health <= 0) {
											xArrow = 450, pointer = 1;
										}
									}
									if (pointer == 3 and enemy3.health <= 0) {
										xArrow = 450, pointer = 1;
										if (pointer == 1 and enemy1.health <= 0) {
											xArrow = 650, pointer = 2;
										}
									}
									break;
								case SDL_SCANCODE_D:
									if (pointer != 3) {
										xArrow += 200, pointer++;
									}
									if (pointer == 1 and enemy1.health <= 0) {
										xArrow = 650, pointer = 2;
										if (pointer == 2 and enemy2.health <= 0) {
											xArrow = 850, pointer = 3;
										}
									}
									if (pointer == 2 and enemy2.health <= 0) {
										xArrow = 850, pointer = 3;
										if (pointer == 3 and enemy3.health <= 0) {
											xArrow = 450, pointer = 1;
										}
									}
									if (pointer == 3 and enemy3.health <= 0) {
										xArrow = 450, pointer = 1;
										if (pointer == 1 and enemy1.health <= 0) {
											xArrow = 650, pointer = 2;
										}
									}
									break;
								}

							}
							isPressed = pressedEnter();

						}
						if (pointer == 1 and arrowState[SDL_SCANCODE_RETURN] and isPressed) choiceEnemy = 1;
						if (pointer == 2 and arrowState[SDL_SCANCODE_RETURN] and isPressed) choiceEnemy = 2;
						if (pointer == 3 and arrowState[SDL_SCANCODE_RETURN] and isPressed) choiceEnemy = 3;
						isPressed = 0;
					}
					if (choiceEnemy == 1) {
						//SDL_Delay(150);
						if (choiceSpell == FIREBOLT) {
							Fireball();
							if (enemy1.health > 0)
								hero.Health = hero.Health - (enemy1.atk - (enemy1.atk * hero.Defense));
							else {
								enemy1.atk = 0;
								livedEnemies--;
							}
						}
						if (choiceSpell == LIGHTING) {
							Lightning();
							if (enemy1.health > 0)
								hero.Health = hero.Health - (enemy1.atk - (enemy1.atk * hero.Defense));
							else {
								enemy1.atk = 0;
								livedEnemies--;
							}
						}
						if (choiceSpell == POISON) {
							Poison();
							if (enemy1.health > 0)
								hero.Health = hero.Health - (enemy1.atk - (enemy1.atk * hero.Defense));
							else {
								enemy1.atk = 0;
								livedEnemies--;
							}
						}
					}
					if (choiceEnemy == 2) {
						//SDL_Delay(150);
						if (choiceSpell == FIREBOLT) {
							Fireball();
							if (enemy2.health > 0)
								hero.Health = hero.Health - (enemy2.atk - (enemy2.atk * hero.Defense));
							else {
								enemy1.atk = 0;
								livedEnemies--;
							}
						}
						if (choiceSpell == LIGHTING) {
							Lightning();
							if (enemy2.health > 0)
								hero.Health = hero.Health - (enemy2.atk - (enemy2.atk * hero.Defense));
							else {
								enemy1.atk = 0;
								livedEnemies--;
							}
						}
						if (choiceSpell == POISON) {
							Poison();
							if (enemy2.health > 0)
								hero.Health = hero.Health - (enemy2.atk - (enemy2.atk * hero.Defense));
							else {
								enemy1.atk = 0;
								livedEnemies--;
							}
						}
					}
					if (choiceEnemy == 3) {
						//SDL_Delay(150);
						if (choiceSpell == FIREBOLT) {
							Fireball();
							if (enemy3.health > 0)
								hero.Health = hero.Health - (enemy3.atk - (enemy3.atk * hero.Defense));

							else {
								enemy1.atk = 0;
								livedEnemies--;
							}
						}
						if (choiceSpell == LIGHTING) {
							Lightning();
							if (enemy3.health > 0)
								hero.Health = hero.Health - (enemy3.atk - (enemy3.atk * hero.Defense));
							else {
								enemy1.atk = 0;
								livedEnemies--;
							}
						}
						if (choiceSpell == POISON) {
							Poison();
							if (enemy3.health > 0)
								hero.Health = hero.Health - (enemy3.atk - (enemy3.atk * hero.Defense));
							else {
								enemy1.atk = 0;
								livedEnemies--;
							}
						}
					}
				}
				if (livedEnemies < 1) {
					SDL_DestroyTexture(textBat);
					SDL_DestroyTexture(textArrow);
					SDL_DestroyTexture(textBattle);
					SDL_DestroyTexture(textdeadEenemy);
					SDL_DestroyTexture(textCharacter);

					flag = 1;
					abilityDamagePoison = 6;
					hero.experience += (enemy1.level * amountEnemy);
					recovery_character();
					if (hero.experience >= hero.levelUp)
						level_up();
					if (questFlag)
						counterKilledEnemies += 1;


					return;
				}
				
			}
			else if (choiche == ESCAPE) {
				//SDL_Delay(250);
				int storageEscape = escape();
				if (ChanceEscape >= storageEscape) {
					printf("You managed to escape\n");
					livedEnemies = 0;
					SDL_DestroyTexture(textdeadEenemy);
					SDL_DestroyTexture(textArrow);
					SDL_DestroyTexture(textBattle);
					SDL_DestroyTexture(textBat);
					SDL_DestroyTexture(textCharacter);

					return;
				}
				else {
					printf("You failed to escape\n");
					hero.Health -= opponent.Attack;
					printf("the enemy has damaged you %d\n", opponent.Attack);
					if (hero.Health <= 0)
						exit(1);
				}
			}
	}
	SDL_DestroyTexture(textdeadEenemy);
	SDL_DestroyTexture(textArrow);
	SDL_DestroyTexture(textBattle);
	SDL_DestroyTexture(textBat);
	SDL_DestroyTexture(textEnemyHealthTTF);
	SDL_DestroyTexture(textCharacter);
	TTF_CloseFont(enemyTTF);

	if (livedEnemies < 1) {
		abilityDamagePoison = 6;
		hero.experience += (enemy1.level * amountEnemy);
		recovery_character();
		if (hero.experience >= hero.levelUp)
			level_up();
		if (questFlag)
			counterKilledEnemies += 1;


	}
}

void StartBattle() {
	/*printf("Fast attack\n");
	ratio = hero.AtSpeed / opponent.AtSpeed;
	if (hero.AtSpeed > opponent.AtSpeed) {
		if (ratio >= 2)
			opponent.Health -= hero.Attack * ratio;
		else if (ratio == 1)
			opponent.Health -= hero.Attack;
		printf("Health Enemy %d\n", opponent.Health);
		if (opponent.Health <= 0) {
			printf("%d\n", opponent.Health);
			hero.experience += opponent.experienceEnemy;
			if (hero.experience >= hero.levelUp)
				level_up();
		}
	}
	if (hero.AtSpeed < opponent.AtSpeed) {
		if (ratio >= 2)
			hero.Health -= opponent.Attack * ratio;
		else if (ratio == 1)
			hero.Health -= opponent.Attack;
	}*/

}

void recovery_character() {
	hero.Health = hero.maxHealth;
	hero.Mana = hero.maxMana;
}

int escape() {
	return rand() % 100;
}

int randomAmountEnemy() {
	return rand() % (3 - 2 + 1) + 2;
}

void generateEnemy() {
	enemy1.atk = opponent.Attack; enemy1.health = opponent.Health; enemy1.gold = opponent.Gold,
		enemy1.level = opponent.experienceEnemy, enemy1.isPoison = 0, enemy1.maxHealth = opponent.Health;
	enemy2.atk = opponent.Attack; enemy2.health = opponent.Health; enemy2.gold = opponent.Gold,
		enemy2.level = opponent.experienceEnemy, enemy2.isPoison = 0, enemy2.maxHealth = opponent.Health;
	enemy3.atk = opponent.Attack; enemy3.health = opponent.Health; enemy3.gold = opponent.Gold,
		enemy3.level = opponent.experienceEnemy, enemy3.isPoison = 0, enemy3.maxHealth = opponent.Health;
	enemy4.atk = opponent.Attack; enemy4.health = opponent.Health; enemy4.gold = opponent.Gold,
		enemy4.level = opponent.experienceEnemy, enemy4.isPoison = 0, enemy4.maxHealth = opponent.Health;

}

void Battler(SDL_Renderer* ren) {
#pragma region Texture
	//Battle menu
	SDL_Surface* surfBattle = IMG_Load("sprites\\menu\\battle.png");
	SDL_Texture* textBattle = SDL_CreateTextureFromSurface(ren, surfBattle);
	SDL_FreeSurface(surfBattle);
	//
	SDL_Surface* surfBat = IMG_Load("sprites\\enemy\\bat.png");
	SDL_Texture* textBat = SDL_CreateTextureFromSurface(ren, surfBat);
	SDL_FreeSurface(surfBat);
	//Arrow
	SDL_Surface* surfArrow = IMG_Load("sprites\\menu\\arrow.png");
	SDL_Texture* textArrow = SDL_CreateTextureFromSurface(ren, surfArrow);
	SDL_FreeSurface(surfArrow);
	//
	SDL_Surface* surfAtk = IMG_Load("sprites\\attack\\attack.png");
	SDL_Texture* textAtk = SDL_CreateTextureFromSurface(ren, surfAtk);
	SDL_FreeSurface(surfAtk);
	//
	SDL_Surface* surfdeadEnemy = IMG_Load("sprites\\enemy\\deadEnemy.png");
	SDL_Texture* textdeadEenemy = SDL_CreateTextureFromSurface(ren, surfdeadEnemy);
	SDL_FreeSurface(surfdeadEnemy);
	//
	TTF_Font* enemyTTF = TTF_OpenFont("fonts\\BAUHS93.TTF", 75);
	char enemyHealth[100] = "Points";
	SDL_Surface* surfEnemyHealthTTF = TTF_RenderText_Blended(enemyTTF, enemyHealth, { 255, 255, 255, 255 });
	SDL_Texture* textEnemyHealthTTF = SDL_CreateTextureFromSurface(ren, surfEnemyHealthTTF);
	SDL_Rect size = { 0, 0, surfEnemyHealthTTF->w, surfEnemyHealthTTF->h };
	int xPoint = 500, yPoint = 50;
	SDL_Rect pointsTTF = { xPoint, yPoint, 55, 60 };
	SDL_FreeSurface(surfEnemyHealthTTF);
	//
	SDL_Surface* surfCharacter = IMG_Load("sprites\\character\\character.png");
	SDL_Texture* textCharacter = SDL_CreateTextureFromSurface(ren, surfCharacter);
	SDL_FreeSurface(surfCharacter);
	int xCharacter = 130, yCharacter = 90;
	SDL_Rect srcrectCharacter = { 10, 10, 100, 140 };
	SDL_Rect dstrectCharacter = { xCharacter, yCharacter, 75, 75 };
#pragma endregion
	SDL_Event ev;
	SDL_PollEvent(&ev);
	int xArrow = 450, yArrow = 100;
	int pointer = 1;
	const Uint8* arrowState = SDL_GetKeyboardState(NULL);
	SDL_Rect srcrectArrow = { 0, 0, 100, 140 };
	SDL_Rect dstrectArrow;
	
	SDL_Rect srcrectDeadEnemy = { 0, 0, 100, 140 };
	SDL_Rect dstrectDeadEnemy1; SDL_Rect dstrectDeadEnemy2; SDL_Rect dstrectDeadEnemy3; SDL_Rect dstrectDeadEnemy4;

	//animation
	int frame = 0, frame_count = 3, cur_frametime = 0, max_frametime = 1000 / 12;
	int lasttime = SDL_GetTicks(); int newtime = SDL_GetTicks();
	int	dt = 0;
	int animation = 1;
	int frameFlag = 0;

	SDL_Rect srcrectAtk = { 200,200,0,0 };
	SDL_Rect dstrectAtk = { 120, 50, 200, 160 };

	if (livedEnemies < 1) {
		SDL_DestroyTexture(textBat);
		SDL_DestroyTexture(textArrow);
		SDL_DestroyTexture(textBattle);
		SDL_DestroyTexture(textdeadEenemy);
		SDL_DestroyTexture(textCharacter);

		hero.experience += enemy1.level * amountEnemy;
		if (hero.experience >= hero.levelUp)
			level_up();
		flag = 1;
		return;
	}

	if (amountEnemy == 2 and livedEnemies >= 1 and hero.Health > 0) {
			int hitEnemy = 0;
			while (hitEnemy == 0) {
				dstrectArrow = { xArrow, yArrow, 75, 75 };
				dstrectBat = { xEnemy1, yEnemy1, 75, 75 };
				dstrectBat2 = { xEnemy2, yEnemy2, 75, 75 };
				SDL_SetRenderDrawColor(ren, 200, 200, 200, 0);
				SDL_RenderClear(ren);
				SDL_RenderCopy(ren, textBattle, NULL, NULL);
				SDL_RenderCopy(ren, textCharacter, &srcrectCharacter, &dstrectCharacter);
				SDL_RenderCopy(ren, textBat, &srcrectBat, &dstrectBat);
				SDL_RenderCopy(ren, textBat, &srcrectBat, &dstrectBat2);
				if (amountEnemy == 2) {
					if (enemy1.health <= 0) enemy1.health = 0;
					if (enemy2.health <= 0) enemy2.health = 0;
					xPoint = 500, yPoint = 50;
					pointsTTF = { xPoint, yPoint, 55, 60 };
					sprintf_s(enemyHealth, "%d", enemy1.health);
					surfEnemyHealthTTF = TTF_RenderText_Blended(enemyTTF, enemyHealth, { 255, 255, 255, 255 });
					size = { 0, 0, surfEnemyHealthTTF->w, surfEnemyHealthTTF->h };
					textEnemyHealthTTF = SDL_CreateTextureFromSurface(ren, surfEnemyHealthTTF);
					SDL_RenderCopy(ren, textEnemyHealthTTF, &size, &pointsTTF);
					SDL_FreeSurface(surfEnemyHealthTTF);
					SDL_DestroyTexture(textEnemyHealthTTF);

					xPoint = 700, yPoint = 50;
					pointsTTF = { xPoint, yPoint, 55, 60 };
					sprintf_s(enemyHealth, "%d", enemy2.health);
					surfEnemyHealthTTF = TTF_RenderText_Blended(enemyTTF, enemyHealth, { 255, 255, 255, 255 });
					size = { 0, 0, surfEnemyHealthTTF->w, surfEnemyHealthTTF->h };
					textEnemyHealthTTF = SDL_CreateTextureFromSurface(ren, surfEnemyHealthTTF);
					SDL_RenderCopy(ren, textEnemyHealthTTF, &size, &pointsTTF);
					SDL_FreeSurface(surfEnemyHealthTTF);
					SDL_DestroyTexture(textEnemyHealthTTF);

					xPoint = 65, yPoint = 50;
					pointsTTF = { xPoint, yPoint, 75, 60 };
					sprintf_s(enemyHealth, "h %d", hero.Health);
					surfEnemyHealthTTF = TTF_RenderText_Blended(enemyTTF, enemyHealth, { 255, 255, 255, 255 });
					size = { 0, 0, surfEnemyHealthTTF->w, surfEnemyHealthTTF->h };
					textEnemyHealthTTF = SDL_CreateTextureFromSurface(ren, surfEnemyHealthTTF);
					SDL_RenderCopy(ren, textEnemyHealthTTF, &size, &pointsTTF);
					SDL_FreeSurface(surfEnemyHealthTTF);
					SDL_DestroyTexture(textEnemyHealthTTF);

					xPoint = 65, yPoint = 90;
					pointsTTF = { xPoint, yPoint, 75, 60 };
					sprintf_s(enemyHealth, "m %d", hero.Mana);
					surfEnemyHealthTTF = TTF_RenderText_Blended(enemyTTF, enemyHealth, { 255, 255, 255, 255 });
					size = { 0, 0, surfEnemyHealthTTF->w, surfEnemyHealthTTF->h };
					textEnemyHealthTTF = SDL_CreateTextureFromSurface(ren, surfEnemyHealthTTF);
					SDL_RenderCopy(ren, textEnemyHealthTTF, &size, &pointsTTF);
					SDL_FreeSurface(surfEnemyHealthTTF);
					SDL_DestroyTexture(textEnemyHealthTTF);
				}
				SDL_RenderCopy(ren, textArrow, &srcrectArrow, &dstrectArrow);
				if (enemy1.health <= 0) {
					dstrectDeadEnemy1 = { xDeadEnemy1, yDeadEnemy1, 75, 75 };
					SDL_RenderCopy(ren, textdeadEenemy, &srcrectDeadEnemy, &dstrectDeadEnemy1);
					pointer = 2;
					xArrow = 650, yArrow = 100;
				}
				if (enemy2.health <= 0) {
					dstrectDeadEnemy2 = { xDeadEnemy2, yDeadEnemy2, 75, 75 };
					SDL_RenderCopy(ren, textdeadEenemy, &srcrectDeadEnemy, &dstrectDeadEnemy2);

					pointer = 1;
					xArrow = 450, yArrow = 100;
				}

				SDL_RenderPresent(ren);
				SDL_DestroyTexture(textEnemyHealthTTF);
				while (SDL_PollEvent(&ev) != NULL) {
					switch (ev.type) {
					case SDL_KEYDOWN:
						switch (ev.key.keysym.scancode) {
						case SDL_SCANCODE_LEFT:
							if (pointer != 1 and enemy1.health > 0) {
								xArrow -= 200;
								pointer--;
							}
							break;
						case SDL_SCANCODE_A:
							if (pointer != 1 and enemy1.health > 0) {
								xArrow -= 200;
								pointer--;
							}
							break;
						case SDL_SCANCODE_RIGHT:
							if (pointer != 2 and enemy2.health > 0) {
								xArrow += 200;
								pointer++;
							}
							break;
						case SDL_SCANCODE_D:
							if (pointer != 2 and enemy2.health > 0) {
								xArrow += 200;
								pointer++;
							}
							break;
						}

					}

				}
				isPressed = pressedEnter();

				if (pointer == 1 and arrowState[SDL_SCANCODE_RETURN] and isPressed == 1) hitEnemy = 1;
				if (pointer == 2 and arrowState[SDL_SCANCODE_RETURN] and isPressed == 1) hitEnemy = 2;

				isPressed = 0;
			}
			if (hitEnemy == 1 and enemy1.health > 0) {
				//SDL_Delay(200);
				enemy1.health = enemy1.health - hero.Attack;
				if (enemy1.health <= 0) {
					enemy1.atk = 0;
					livedEnemies -= 1;
					hero.Gold += enemy1.gold;
					hero.experience += enemy1.level;
				}
			}
			if (hitEnemy == 2 and enemy2.health > 0) {
				//SDL_Delay(200);
				enemy2.health = enemy2.health - hero.Attack;
				if (enemy2.health <= 0) {
					enemy2.atk = 0;
					livedEnemies -= 1;
					hero.Gold += enemy2.gold;
					hero.experience += enemy2.level;
				}
			}

			newtime = SDL_GetTicks();
			dt = newtime - lasttime;
			lasttime = newtime;

			while (animation == 1) {
				cur_frametime += dt;
				if (cur_frametime >= max_frametime) {
					cur_frametime -= max_frametime;
					frame = (frame + 1) % frame_count;
					srcrectAtk.x = 530 * frameFlag;
					frameFlag += 1;
				}
				if (animation == 1) {
					srcrectAtk.x, srcrectAtk.y = 140, srcrectAtk.w = 513, srcrectAtk.h = 380;
					SDL_RenderClear(ren);
					SDL_RenderCopy(ren, textBattle, NULL, NULL);
					SDL_RenderCopy(ren, textCharacter, &srcrectCharacter, &dstrectCharacter);
					SDL_RenderCopy(ren, textBat, &srcrectBat, &dstrectBat);
					SDL_RenderCopy(ren, textBat, &srcrectBat, &dstrectBat2);
					SDL_RenderCopy(ren, textAtk, &srcrectAtk, &dstrectAtk);
					SDL_RenderPresent(ren);
					SDL_Delay(70);
				}
				if (frameFlag == 4) {
					animation = 0;
					frameFlag = 0;
				}
			}

			hero.Health = hero.Health - (enemy1.atk - (enemy1.atk * hero.Defense));
			if (hero.Health <= 0) de_init(1);
			hero.Health = hero.Health - (enemy2.atk - (enemy2.atk * hero.Defense));
			if (hero.Health <= 0) de_init(1);

			SDL_DestroyTexture(textBat);
			SDL_DestroyTexture(textArrow);
			SDL_DestroyTexture(textBattle);
			SDL_DestroyTexture(textdeadEenemy);
			SDL_DestroyTexture(textEnemyHealthTTF);
			SDL_DestroyTexture(textAtk);
			TTF_CloseFont(enemyTTF);
			SDL_DestroyTexture(textCharacter);
		}

	if (amountEnemy == 3 and livedEnemies >= 1 and hero.Health > 0) {
			int hitEnemy = 0;
			if (enemy2.health > 0) {
				pointer = 2;
				xArrow = 650, yArrow = 100;
			}
			if (enemy2.health <= 0 and enemy3.health > 0) {
				pointer = 3;
				xArrow = 850, yArrow = 100;
			}
			if (enemy1.health > 0) {
				pointer = 1;
				xArrow = 450, yArrow = 100;
			}
			if (enemy1.health <= 0 and enemy3.health > 0) {
				pointer = 3;
				xArrow = 850, yArrow = 100;
			}
			if (enemy1.health <= 0 and enemy2.health > 0) {
				pointer = 2;
				xArrow = 650, yArrow = 100;
			}



			while (hitEnemy == 0) {
				dstrectArrow = { xArrow, yArrow, 75, 75 };
				dstrectBat = { xEnemy1, yEnemy1, 75, 75 };
				dstrectBat2 = { xEnemy2, yEnemy2, 75, 75 };
				dstrectBat3 = { xEnemy3, yEnemy3, 75, 75 };
				SDL_SetRenderDrawColor(ren, 200, 200, 200, 0);
				SDL_RenderClear(ren);
				SDL_RenderCopy(ren, textBattle, NULL, NULL);
				SDL_RenderCopy(ren, textCharacter, &srcrectCharacter, &dstrectCharacter);
				SDL_RenderCopy(ren, textBat, &srcrectBat, &dstrectBat);
				SDL_RenderCopy(ren, textBat, &srcrectBat, &dstrectBat2);
				SDL_RenderCopy(ren, textBat, &srcrectBat, &dstrectBat3);
				if (amountEnemy == 3) {
					if (enemy1.health <= 0) enemy1.health = 0;
					if (enemy2.health <= 0) enemy2.health = 0;
					if (enemy3.health <= 0) enemy3.health = 0;
					xPoint = 500, yPoint = 50;
					pointsTTF = { xPoint, yPoint, 55, 60 };
					sprintf_s(enemyHealth, "%d", enemy1.health);
					surfEnemyHealthTTF = TTF_RenderText_Blended(enemyTTF, enemyHealth, { 255, 255, 255, 255 });
					size = { 0, 0, surfEnemyHealthTTF->w, surfEnemyHealthTTF->h };
					textEnemyHealthTTF = SDL_CreateTextureFromSurface(ren, surfEnemyHealthTTF);
					SDL_RenderCopy(ren, textEnemyHealthTTF, &size, &pointsTTF);
					SDL_FreeSurface(surfEnemyHealthTTF);
					SDL_DestroyTexture(textEnemyHealthTTF);


					xPoint = 700, yPoint = 50;
					pointsTTF = { xPoint, yPoint, 55, 60 };
					sprintf_s(enemyHealth, "%d", enemy2.health);
					surfEnemyHealthTTF = TTF_RenderText_Blended(enemyTTF, enemyHealth, { 255, 255, 255, 255 });
					size = { 0, 0, surfEnemyHealthTTF->w, surfEnemyHealthTTF->h };
					textEnemyHealthTTF = SDL_CreateTextureFromSurface(ren, surfEnemyHealthTTF);
					SDL_RenderCopy(ren, textEnemyHealthTTF, &size, &pointsTTF);
					SDL_FreeSurface(surfEnemyHealthTTF);
					SDL_DestroyTexture(textEnemyHealthTTF);


					xPoint = 900, yPoint = 50;
					pointsTTF = { xPoint, yPoint, 55, 60 };
					sprintf_s(enemyHealth, "%d", enemy3.health);
					surfEnemyHealthTTF = TTF_RenderText_Blended(enemyTTF, enemyHealth, { 255, 255, 255, 255 });
					size = { 0, 0, surfEnemyHealthTTF->w, surfEnemyHealthTTF->h };
					textEnemyHealthTTF = SDL_CreateTextureFromSurface(ren, surfEnemyHealthTTF);
					SDL_RenderCopy(ren, textEnemyHealthTTF, &size, &pointsTTF);
					SDL_FreeSurface(surfEnemyHealthTTF);
					SDL_DestroyTexture(textEnemyHealthTTF);

					xPoint = 65, yPoint = 50;
					pointsTTF = { xPoint, yPoint, 75, 60 };
					sprintf_s(enemyHealth, "h %d", hero.Health);
					surfEnemyHealthTTF = TTF_RenderText_Blended(enemyTTF, enemyHealth, { 255, 255, 255, 255 });
					size = { 0, 0, surfEnemyHealthTTF->w, surfEnemyHealthTTF->h };
					textEnemyHealthTTF = SDL_CreateTextureFromSurface(ren, surfEnemyHealthTTF);
					SDL_RenderCopy(ren, textEnemyHealthTTF, &size, &pointsTTF);
					SDL_FreeSurface(surfEnemyHealthTTF);
					SDL_DestroyTexture(textEnemyHealthTTF);

					xPoint = 65, yPoint = 90;
					pointsTTF = { xPoint, yPoint, 75, 60 };
					sprintf_s(enemyHealth, "m %d", hero.Mana);
					surfEnemyHealthTTF = TTF_RenderText_Blended(enemyTTF, enemyHealth, { 255, 255, 255, 255 });
					size = { 0, 0, surfEnemyHealthTTF->w, surfEnemyHealthTTF->h };
					textEnemyHealthTTF = SDL_CreateTextureFromSurface(ren, surfEnemyHealthTTF);
					SDL_RenderCopy(ren, textEnemyHealthTTF, &size, &pointsTTF);
					SDL_FreeSurface(surfEnemyHealthTTF);
					SDL_DestroyTexture(textEnemyHealthTTF);
				}
				SDL_RenderCopy(ren, textArrow, &srcrectArrow, &dstrectArrow);
				if (enemy1.health <= 0) {
					dstrectDeadEnemy1 = { xDeadEnemy1, yDeadEnemy1, 75, 75 };
					SDL_RenderCopy(ren, textdeadEenemy, &srcrectDeadEnemy, &dstrectDeadEnemy1);
					
				}
				if (enemy2.health <= 0) {
					dstrectDeadEnemy2 = { xDeadEnemy2, yDeadEnemy2, 75, 75 };
					SDL_RenderCopy(ren, textdeadEenemy, &srcrectDeadEnemy, &dstrectDeadEnemy2);
					
				}
				if (enemy3.health <= 0) {
					dstrectDeadEnemy3 = { xDeadEnemy3, yDeadEnemy3, 75, 75 };
					SDL_RenderCopy(ren, textdeadEenemy, &srcrectDeadEnemy, &dstrectDeadEnemy3);
					
				}

				SDL_RenderPresent(ren);
				SDL_DestroyTexture(textEnemyHealthTTF);

				while (SDL_PollEvent(&ev) != NULL) {
					switch (ev.type) {
					case SDL_KEYDOWN:
						switch (ev.key.keysym.scancode) {
						case SDL_SCANCODE_LEFT:
							if (pointer != 1) {
								xArrow -= 200;
								pointer--;
							}
							if (pointer == 1 and enemy1.health <= 0) {
								xArrow = 650, pointer = 2;
								if (pointer == 2 and enemy2.health <= 0) {
									xArrow = 850, pointer = 3;
								}
							}
							if (pointer == 2 and enemy2.health <= 0) {
								xArrow = 450, pointer = 1;
								if (pointer == 1 and enemy1.health <= 0) {
									xArrow = 850, pointer = 3;
								}
							}
							if (pointer == 3 and enemy3.health <= 0) {
								xArrow = 450, pointer = 1;
								if (pointer == 1 and enemy1.health <= 0) {
									xArrow = 650, pointer = 2;
								}
							}
							break;
						case SDL_SCANCODE_A:
							if (pointer != 1) {
								xArrow -= 200;
								pointer--;
							}
							if (pointer == 1 and enemy1.health <= 0) {
								xArrow = 650, pointer = 2;
								if (pointer == 2 and enemy2.health <= 0) {
									xArrow = 850, pointer = 3;
								}
							}
							if (pointer == 2 and enemy2.health <= 0) {
								xArrow = 450, pointer = 1;
								if (pointer == 1 and enemy1.health <= 0) {
									xArrow = 850, pointer = 3;
								}
							}
							if (pointer == 3 and enemy3.health <= 0) {
								xArrow = 450, pointer = 1;
								if (pointer == 1 and enemy1.health <= 0) {
									xArrow = 650, pointer = 2;
								}
							}
							break;
						case SDL_SCANCODE_RIGHT:
							if (pointer != 3) {
								xArrow += 200, pointer++;
							}
							if (pointer == 1 and enemy1.health <= 0) {
								xArrow = 650, pointer = 2;
								if (pointer == 2 and enemy2.health <= 0) {
									xArrow = 850, pointer = 3;
								}
							}
							if (pointer == 2 and enemy2.health <= 0) {
								xArrow = 850, pointer = 3;
								if (pointer == 3 and enemy3.health <= 0) {
									xArrow = 450, pointer = 1;
								}
							}
							if (pointer == 3 and enemy3.health <= 0) {
								xArrow = 450, pointer = 1;
								if (pointer == 1 and enemy1.health <= 0) {
									xArrow = 650, pointer = 2;
								}
							}
							break;
						case SDL_SCANCODE_D:
							if (pointer != 3) {
								xArrow += 200, pointer++;
							}
							if (pointer == 1 and enemy1.health <= 0) {
								xArrow = 650, pointer = 2;
								if (pointer == 2 and enemy2.health <= 0) {
									xArrow = 850, pointer = 3;
								}
							}
							if (pointer == 2 and enemy2.health <= 0) {
								xArrow = 850, pointer = 3;
								if (pointer == 3 and enemy3.health <= 0) {
									xArrow = 450, pointer = 1;
								}
							}
							if (pointer == 3 and enemy3.health <= 0) {
								xArrow = 650, pointer = 2;
								if (pointer == 2 and enemy2.health <= 0) {
									xArrow = 450, pointer = 1;
								}
							}
							break;
						}

					}
				}
				isPressed = pressedEnter();

				if (pointer == 1 and arrowState[SDL_SCANCODE_RETURN] and isPressed == 1) hitEnemy = 1;
				if (pointer == 2 and arrowState[SDL_SCANCODE_RETURN] and isPressed == 1) hitEnemy = 2;
				if (pointer == 3 and arrowState[SDL_SCANCODE_RETURN] and isPressed == 1) hitEnemy = 3;

				isPressed = 0;
			}
			if (hitEnemy == 1 and enemy1.health > 0) {
				//SDL_Delay(200);
				enemy1.health = enemy1.health - hero.Attack;
				if (enemy1.health <= 0) {
					enemy1.atk = 0;
					livedEnemies -= 1;
					hero.Gold += enemy1.gold;
					hero.experience += enemy1.level;
				}
			}
			if (hitEnemy == 2 and enemy2.health > 0) {
				//SDL_Delay(200);
				enemy2.health = enemy2.health - hero.Attack;
				if (enemy2.health <= 0) {
					enemy2.atk = 0;
					livedEnemies -= 1;
					hero.Gold += enemy2.gold;
					hero.experience += enemy2.level;
				}
			}
			if (hitEnemy == 3 and enemy3.health > 0) {
				//SDL_Delay(200);
				enemy3.health = enemy3.health - hero.Attack;
				if (enemy3.health <= 0) {
					enemy3.atk = 0;
					livedEnemies -= 1;
					hero.Gold += enemy3.gold;
					hero.experience += enemy3.level;
				}
			}

			newtime = SDL_GetTicks();
			dt = newtime - lasttime;
			lasttime = newtime;

			while (animation == 1) {
				cur_frametime += dt;
				if (cur_frametime >= max_frametime) {
					cur_frametime -= max_frametime;
					frame = (frame + 1) % frame_count;
					srcrectAtk.x = 530 * frameFlag;
					frameFlag += 1;
				}
				if (animation == 1) {
					srcrectAtk.x, srcrectAtk.y = 140, srcrectAtk.w = 513, srcrectAtk.h = 380;
					SDL_RenderClear(ren);
					SDL_RenderCopy(ren, textBattle, NULL, NULL);
					SDL_RenderCopy(ren, textCharacter, &srcrectCharacter, &dstrectCharacter);
					SDL_RenderCopy(ren, textBat, &srcrectBat, &dstrectBat);
					SDL_RenderCopy(ren, textBat, &srcrectBat, &dstrectBat2);
					SDL_RenderCopy(ren, textBat, &srcrectBat, &dstrectBat3);
					SDL_RenderCopy(ren, textAtk, &srcrectAtk, &dstrectAtk);
					SDL_RenderPresent(ren);
					SDL_Delay(70);
				}
				if (frameFlag == 4) {
					animation = 0;
					frameFlag = 0;
				}
			}

			hero.Health = hero.Health - (enemy1.atk - (enemy1.atk * hero.Defense));
			if (hero.Health <= 0) de_init(1);
			hero.Health = hero.Health - (enemy2.atk - (enemy2.atk * hero.Defense));
			if (hero.Health <= 0) de_init(1);
			hero.Health = hero.Health - (enemy3.atk - (enemy3.atk * hero.Defense));
			if (hero.Health <= 0) de_init(1);

			SDL_DestroyTexture(textBat);
			SDL_DestroyTexture(textArrow);
			SDL_DestroyTexture(textBattle);
			SDL_DestroyTexture(textdeadEenemy);
			SDL_DestroyTexture(textEnemyHealthTTF);
			SDL_DestroyTexture(textAtk);
			TTF_CloseFont(enemyTTF);
			SDL_DestroyTexture(textCharacter);
		}


	

	flag = 1;
}

void Fireball() {
	abilityDamageFireball;
	if (hero.Mana >= 15) {
		hero.Mana -= 15;
		if (choiceEnemy == 1) {
			enemy1.health -= abilityDamageFireball;

		}
		else if (choiceEnemy == 2) {
			enemy2.health -= abilityDamageFireball;
		}
		else if (choiceEnemy == 3) {
			enemy3.health -= abilityDamageFireball;
		}
	}
	else printf("not enough mana\n");
}

void Lightning() {
	abilityDamageLightning;
	if (hero.Mana >= 25 and lightingEffect == false) {
		hero.Mana -= 25;
		if (choiceEnemy == 1)
			enemy1.health -= abilityDamageLightning;
		else if (choiceEnemy == 2)
			enemy2.health -= abilityDamageLightning;
		else if (choiceEnemy == 3)
			enemy3.health -= abilityDamageLightning;
	}
}

void Poison() {
	abilityDamagePoison;
	if (hero.Mana >= 18 and choiceEnemy == 1 and enemy1.isPoison == false) {
		hero.Mana -= 18;
		enemy1.isPoison = true;
	}
	if (hero.Mana >= 18 and choiceEnemy == 2 and enemy2.isPoison == false) {
		hero.Mana -= 18;
		enemy2.isPoison = true;
	}
	if (hero.Mana >= 18 and choiceEnemy == 3 and enemy3.isPoison == false) {
		hero.Mana -= 18;
		enemy3.isPoison = true;
	}
	
	else if (hero.Mana < 18) printf("not enough mana\n");

	if (enemy1.isPoison == true and enemy1.health <= 0)
		enemy1.isPoison = false;
	if (enemy2.isPoison == true and enemy2.health <= 0)
		enemy2.isPoison = false;
	if (enemy3.isPoison == true and enemy3.health <= 0)
		enemy3.isPoison = false;

	if (enemy1.isPoison == true) {
		enemy1.health -= abilityDamagePoison;
		abilityDamagePoison--;
	}
	if (enemy2.isPoison == true) {
		enemy2.health -= abilityDamagePoison;
		abilityDamagePoison--;
	}
	if (enemy3.isPoison == true) {
		enemy3.health -= abilityDamagePoison;
		abilityDamagePoison--;
	}

	if (abilityDamagePoison == 0)
		enemy1.isPoison, enemy2.isPoison, enemy3.isPoison = false;
}