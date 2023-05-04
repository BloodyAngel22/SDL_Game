#include <stdio.h>
#include <stdlib.h>
#include "Models.h"
#include "Leveling.h"
#include "Ability.h"
#include "Battle.h"
#include <SDL.h>
#include <SDL_image.h>
#define BATTLE 1
#define ABILITY 2
#define ESCAPE 3
#define ChanceEscape 40
#define FIREBOLT 1
#define LIGHTING 2
#define POISON 3



int abilityDamageLighting = 48, abilityDamageFireball = 30, abilityDamagePosion = 6;
extern bool posionEffect = false;
extern bool lightingEffect = false;
extern int choiceEnemy = 0;
int amountEnemy;
int livedEnemies = 1;
int ratio;
Character hero;
Enemy opponent;
ClassMage mage;
ClassWarrior warrior;
genEnemy enemy1, enemy2, enemy3, enemy4;
SDL_Rect srcrectDeadEnemy = { 0, 0, 100, 140 };
SDL_Rect srcrectBat = { 0, 0, 100, 140 };
SDL_Rect dstrectDeadEnemy1; SDL_Rect dstrectDeadEnemy2; SDL_Rect dstrectDeadEnemy3; SDL_Rect dstrectDeadEnemy4;
SDL_Rect dstrectBat; SDL_Rect dstrectBat2; SDL_Rect dstrectBat3; SDL_Rect dstrectBat4;
int xEnemy1 = 600, yEnemy1 = 100;
int xEnemy2 = 700, yEnemy2 = 100;
int xEnemy3 = 800, yEnemy3 = 100;
int xEnemy4 = 900, yEnemy4 = 100;
int xDeadEnemy1 = 600, yDeadEnemy1 = 100;
int xDeadEnemy2 = 700, yDeadEnemy2 = 100;
int xDeadEnemy3 = 700, yDeadEnemy3 = 100;
int xDeadEnemy4 = 700, yDeadEnemy4 = 100;
int flag = 0;

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
	#pragma endregion
	SDL_Event ev;
	SDL_PollEvent(&ev);
	StartBattle();
	if (flag == 0) {
		generateEnemy();
		amountEnemy = randomAmountEnemy();
		livedEnemies = amountEnemy;
	}
		SDL_SetRenderDrawColor(ren, 200, 200, 200, 0);
		SDL_RenderClear(ren);
		SDL_RenderCopy(ren, textBattle, NULL, NULL);
	while ((hero.Health > 0) and (livedEnemies >= 1)) {
		if (livedEnemies < 1) {
			SDL_DestroyTexture(textBat);
			SDL_DestroyTexture(textArrow);
			SDL_DestroyTexture(textBattle);
			SDL_DestroyTexture(textdeadEenemy);
			flag = 1;
			return;
		}
		int choiche = 0;
		int xArrow = 10, yArrow = 310;
		const Uint8* arrowState = SDL_GetKeyboardState(NULL);
		SDL_Rect srcrectArrow = { 0, 0, 100, 140 };
		SDL_Rect dstrectArrow;
		int pointer = 1;
		printf("Health %d, Attack %d, Mana %d\n", hero.Health, hero.Attack, hero.Mana);
		printf("1 - Battle\n2 - Ability\n3 - Escape\n");
		while (choiche == 0) {
			dstrectArrow = { xArrow, yArrow, 75, 75 };
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
				SDL_RenderPresent(ren);
			}
			if (enemy2.health <= 0) {
				dstrectDeadEnemy2 = { xDeadEnemy2, yDeadEnemy2, 75, 75 };
				SDL_RenderCopy(ren, textdeadEenemy, &srcrectDeadEnemy, &dstrectDeadEnemy2);
				SDL_RenderPresent(ren);
			}
			if (enemy3.health <= 0) {
				dstrectDeadEnemy3 = { xDeadEnemy3, yDeadEnemy3, 75, 75 };
				SDL_RenderCopy(ren, textdeadEenemy, &srcrectDeadEnemy, &dstrectDeadEnemy3);
				SDL_RenderPresent(ren);
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
				SDL_RenderClear(ren);
				SDL_RenderCopy(ren, textBattle, NULL, NULL);
				SDL_RenderCopy(ren, textArrow, &srcrectArrow, &dstrectArrow);
				SDL_RenderPresent(ren);
			}

			if (pointer == 1 and arrowState[SDL_SCANCODE_RETURN]) choiche = BATTLE;
			if (pointer == 2 and arrowState[SDL_SCANCODE_RETURN]) choiche = ABILITY;
			if (pointer == 3 and arrowState[SDL_SCANCODE_RETURN]) choiche = ESCAPE;

		}
			if (choiche == BATTLE) {
				SDL_Delay(250);
				system("cls");
				Battler(ren);
				/*if (posionEffect == true) Poison();*/
				printf("%d\n", opponent.Health);
			}
			else if (choiche == ABILITY) {
				flag = 1;
				system("cls");
				SDL_Delay(250);
				int choiceSpell = 0;
				printf("1 - Firebolt\n2 - Lightning\n3 - Posion\n");
				pointer = 1;
				xArrow = 310, yArrow = 310;
				while (choiceSpell == 0) {
					dstrectArrow = { xArrow, yArrow, 75, 75 };
					SDL_SetRenderDrawColor(ren, 200, 200, 200, 0);
					SDL_RenderClear(ren);
					SDL_RenderCopy(ren, textBattle, NULL, NULL);
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
						SDL_RenderPresent(ren);
					}
					if (enemy2.health <= 0) {
						dstrectDeadEnemy2 = { xDeadEnemy2, yDeadEnemy2, 75, 75 };
						SDL_RenderCopy(ren, textdeadEenemy, &srcrectDeadEnemy, &dstrectDeadEnemy2);
						SDL_RenderPresent(ren);
					}
					if (enemy3.health <= 0) {
						dstrectDeadEnemy3 = { xDeadEnemy3, yDeadEnemy3, 75, 75 };
						SDL_RenderCopy(ren, textdeadEenemy, &srcrectDeadEnemy, &dstrectDeadEnemy3);
						SDL_RenderPresent(ren);
					}
					SDL_RenderCopy(ren, textArrow, &srcrectArrow, &dstrectArrow);
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

						SDL_RenderClear(ren);
						SDL_RenderCopy(ren, textBattle, NULL, NULL);
						SDL_RenderCopy(ren, textArrow, &srcrectArrow, &dstrectArrow);
						SDL_RenderPresent(ren);
					}
					if (pointer == 1 and arrowState[SDL_SCANCODE_RETURN]) choiceSpell = FIREBOLT;
					if (pointer == 2 and arrowState[SDL_SCANCODE_RETURN]) choiceSpell = LIGHTING;
					if (pointer == 3 and arrowState[SDL_SCANCODE_RETURN]) choiceSpell = POISON;

				}
				SDL_Delay(300);
				choiceEnemy = 0;
				xArrow = 550, yArrow = 100;
				pointer = 1;
				if (amountEnemy == 2) {
					while (choiceEnemy == 0) {
						srcrectArrow = { 0, 0, 100, 140 };
						dstrectArrow = { xArrow, yArrow, 75, 75 };
						SDL_SetRenderDrawColor(ren, 200, 200, 200, 0);
						SDL_RenderClear(ren);
						SDL_RenderCopy(ren, textBattle, NULL, NULL);
						dstrectBat = { xEnemy1, yEnemy1, 75, 75 };
						dstrectBat2 = { xEnemy2, yEnemy2, 75, 75 };
						SDL_RenderCopy(ren, textBat, &srcrectBat, &dstrectBat);
						SDL_RenderCopy(ren, textBat, &srcrectBat, &dstrectBat2);
						if (enemy1.health <= 0) {
							dstrectDeadEnemy1 = { xDeadEnemy1, yDeadEnemy1, 75, 75 };
							SDL_RenderCopy(ren, textdeadEenemy, &srcrectDeadEnemy, &dstrectDeadEnemy1);
							SDL_RenderPresent(ren);
						}
						if (enemy2.health <= 0) {
							dstrectDeadEnemy2 = { xDeadEnemy2, yDeadEnemy2, 75, 75 };
							SDL_RenderCopy(ren, textdeadEenemy, &srcrectDeadEnemy, &dstrectDeadEnemy2);
							SDL_RenderPresent(ren);
						}
						SDL_RenderCopy(ren, textArrow, &srcrectArrow, &dstrectArrow);
						SDL_RenderPresent(ren);
						while (SDL_PollEvent(&ev) != NULL) {
							switch (ev.type) {
							case SDL_KEYDOWN:
								switch (ev.key.keysym.scancode) {
								case SDL_SCANCODE_LEFT:
									if (pointer != 1) {
										xArrow -= 125;
										pointer--;
									}
									break;
								case SDL_SCANCODE_A:
									if (pointer != 1) {
										xArrow -= 125;
										pointer--;
									}
									break;
								case SDL_SCANCODE_RIGHT:
									if (pointer != 2) {
										xArrow += 125;
										pointer++;
									}
									break;
								case SDL_SCANCODE_D:
									if (pointer != 2) {
										xArrow += 125;
										pointer++;
									}
									break;
								}

							}
						}
						if (pointer == 1 and arrowState[SDL_SCANCODE_RETURN]) choiceEnemy = 1;
						if (pointer == 2 and arrowState[SDL_SCANCODE_RETURN]) choiceEnemy = 2;
					}
					if (choiceEnemy == 1) {
						SDL_Delay(150);
						if (choiceSpell == FIREBOLT) {
							Fireball();
							if (enemy1.health > 0) 
								hero.Health -= enemy1.atk;
							else {
								enemy1.atk = 0;
								livedEnemies--;
							}
						}
						else if (choiceSpell == LIGHTING) {
							Lightning();
							if (enemy1.health > 0)
								hero.Health -= enemy1.atk;
							else {
								enemy1.atk = 0;
								livedEnemies--;
							}
						}
						else if (choiceSpell == POISON) {
							Poison();
							if (enemy1.health > 0)
								hero.Health -= enemy1.atk;
							else {
								enemy1.atk = 0;
								livedEnemies--;
							}
						}
					}
					else if (choiceEnemy == 2) {
						SDL_Delay(150);
						if (choiceSpell == FIREBOLT) {
							Fireball();
							if (enemy2.health > 0)
								hero.Health -= enemy2.atk;
							else {
								enemy2.atk = 0;
								livedEnemies--;
							}
						}
						if (choiceSpell == LIGHTING) {
							Lightning();
							if (enemy2.health > 0)
								hero.Health -= enemy2.atk;
							else {
								enemy2.atk = 0;
								livedEnemies--;
							}
						}
						if (choiceSpell == POISON) {
							Poison();
							if (enemy2.health > 0)
								hero.Health -= enemy2.atk;
							else {
								enemy2.atk = 0;
								livedEnemies--;
							}
						}
					}
				}
				else if (amountEnemy == 3) {
					while (choiceEnemy == 0) {
						SDL_Delay(150);
						dstrectArrow = { xArrow, yArrow, 75, 75 };
						SDL_SetRenderDrawColor(ren, 200, 200, 200, 0);
						SDL_RenderClear(ren);
						SDL_RenderCopy(ren, textBattle, NULL, NULL);
						dstrectBat = { xEnemy1, yEnemy1, 75, 75 };
						dstrectBat2 = { xEnemy2, yEnemy2, 75, 75 };
						SDL_RenderCopy(ren, textBat, &srcrectBat, &dstrectBat);
						SDL_RenderCopy(ren, textBat, &srcrectBat, &dstrectBat2);
						SDL_RenderCopy(ren, textBat, &srcrectBat, &dstrectBat3);
						if (enemy1.health <= 0) {
							dstrectDeadEnemy1 = { xDeadEnemy1, yDeadEnemy1, 75, 75 };
							SDL_RenderCopy(ren, textdeadEenemy, &srcrectDeadEnemy, &dstrectDeadEnemy1);
							SDL_RenderPresent(ren);
						}
						if (enemy2.health <= 0) {
							dstrectDeadEnemy2 = { xDeadEnemy2, yDeadEnemy2, 75, 75 };
							SDL_RenderCopy(ren, textdeadEenemy, &srcrectDeadEnemy, &dstrectDeadEnemy2);
							SDL_RenderPresent(ren);
						}
						if (enemy3.health <= 0) {
							dstrectDeadEnemy3 = { xDeadEnemy3, yDeadEnemy3, 75, 75 };
							SDL_RenderCopy(ren, textdeadEenemy, &srcrectDeadEnemy, &dstrectDeadEnemy3);
							SDL_RenderPresent(ren);
						}
						SDL_RenderCopy(ren, textArrow, &srcrectArrow, &dstrectArrow);
						SDL_RenderPresent(ren);
						while (SDL_PollEvent(&ev) != NULL) {
							switch (ev.type) {
							case SDL_KEYDOWN:
								switch (ev.key.keysym.scancode) {
								case SDL_SCANCODE_LEFT:
									if (pointer != 1) {
										xArrow -= 125;
										pointer--;
									}
									break;
								case SDL_SCANCODE_A:
									if (pointer != 1) {
										xArrow -= 125;
										pointer--;
									}
									break;
								case SDL_SCANCODE_RIGHT:
									if (pointer != 3) {
										xArrow += 125;
										pointer++;
									}
									break;
								case SDL_SCANCODE_D:
									if (pointer != 3) {
										xArrow += 125;
										pointer++;
									}
									break;
								}

							}
						}
						if (pointer == 1 and arrowState[SDL_SCANCODE_RETURN]) choiceEnemy = 1;
						if (pointer == 2 and arrowState[SDL_SCANCODE_RETURN]) choiceEnemy = 2;
						if (pointer == 3 and arrowState[SDL_SCANCODE_RETURN]) choiceEnemy = 3;
					}
					if (choiceEnemy == 1) {
						SDL_Delay(150);
						if (choiceSpell == FIREBOLT) {
							Fireball();
							if (enemy1.health > 0)
								hero.Health -= enemy1.atk;
							else {
								enemy1.atk = 0;
								livedEnemies--;
							}
						}
						if (choiceSpell == LIGHTING) {
							Lightning();
							if (enemy1.health > 0)
								hero.Health -= enemy1.atk;
							else {
								enemy1.atk = 0;
								livedEnemies--;
							}
						}
						if (choiceSpell == POISON) {
							Poison();
							if (enemy1.health > 0)
								hero.Health -= enemy1.atk;
							else {
								enemy1.atk = 0;
								livedEnemies--;
							}
						}
					}
					if (choiceEnemy == 2) {
						SDL_Delay(150);
						if (choiceSpell == FIREBOLT) {
							Fireball();
							if (enemy2.health > 0)
								hero.Health -= enemy2.atk;
							else {
								enemy1.atk = 0;
								livedEnemies--;
							}
						}
						if (choiceSpell == LIGHTING) {
							Lightning();
							if (enemy2.health > 0)
								hero.Health -= enemy2.atk;
							else {
								enemy1.atk = 0;
								livedEnemies--;
							}
						}
						if (choiceSpell == POISON) {
							Poison();
							if (enemy2.health > 0)
								hero.Health -= enemy2.atk;
							else {
								enemy1.atk = 0;
								livedEnemies--;
							}
						}
					}
					if (choiceEnemy == 3) {
						SDL_Delay(150);
						if (choiceSpell == FIREBOLT) {
							Fireball();
							if (enemy3.health > 0)
								hero.Health -= enemy3.atk;
							else {
								enemy1.atk = 0;
								livedEnemies--;
							}
						}
						if (choiceSpell == LIGHTING) {
							Lightning();
							if (enemy3.health > 0)
								hero.Health -= enemy3.atk;
							else {
								enemy1.atk = 0;
								livedEnemies--;
							}
						}
						if (choiceSpell == POISON) {
							Poison();
							if (enemy3.health > 0)
								hero.Health -= enemy3.atk;
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
					flag = 1;
					return;
				}
			}
			else if (choiche == ESCAPE) {
				SDL_Delay(250);
				int storageEscape = escape();
				if (ChanceEscape >= storageEscape) {
					printf("You managed to escape\n");
					livedEnemies = 0;
					SDL_DestroyTexture(textdeadEenemy);
					SDL_DestroyTexture(textArrow);
					SDL_DestroyTexture(textBattle);
					SDL_DestroyTexture(textBat);
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
}

void Battle() {
	if (hero.Health > 0)
		opponent.Health -= hero.Attack;
	if (opponent.Health <= 0) {
		printf("%d\n", opponent.Health);
		hero.experience += opponent.experienceEnemy;
		if (hero.experience >= hero.levelUp)
			level_up();
	}
	if (opponent.Health > 0)
		hero.Health -= opponent.Attack;
	if (hero.Health <= 0)
		exit(1);
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
	enemy1.atk = opponent.Attack; enemy1.health = opponent.Health; enemy1.gold = opponent.Gold, enemy1.level = opponent.level, enemy1.isPoison = 0;
	enemy2.atk = opponent.Attack; enemy2.health = opponent.Health; enemy2.gold = opponent.Gold, enemy2.level = opponent.level, enemy2.isPoison = 0;
	enemy3.atk = opponent.Attack; enemy3.health = opponent.Health; enemy3.gold = opponent.Gold, enemy3.level = opponent.level, enemy3.isPoison = 0;
	enemy4.atk = opponent.Attack; enemy4.health = opponent.Health; enemy4.gold = opponent.Gold, enemy4.level = opponent.level, enemy4.isPoison = 0;

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
	SDL_Surface* surfdeadEnemy = IMG_Load("sprites\\enemy\\deadEnemy.png");
	SDL_Texture* textdeadEenemy = SDL_CreateTextureFromSurface(ren, surfdeadEnemy);
	SDL_FreeSurface(surfdeadEnemy);
#pragma endregion
	SDL_Event ev;
	SDL_PollEvent(&ev);
	int xArrow = 550, yArrow = 100;
	int pointer = 1;
	const Uint8* arrowState = SDL_GetKeyboardState(NULL);
	SDL_Rect srcrectArrow = { 0, 0, 100, 140 };
	SDL_Rect dstrectArrow;
	
	SDL_Rect srcrectDeadEnemy = { 0, 0, 100, 140 };
	SDL_Rect dstrectDeadEnemy1; SDL_Rect dstrectDeadEnemy2; SDL_Rect dstrectDeadEnemy3; SDL_Rect dstrectDeadEnemy4;
	if (livedEnemies < 1) {
		SDL_DestroyTexture(textBat);
		SDL_DestroyTexture(textArrow);
		SDL_DestroyTexture(textBattle);
		SDL_DestroyTexture(textdeadEenemy);
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
				SDL_RenderCopy(ren, textBat, &srcrectBat, &dstrectBat);
				SDL_RenderCopy(ren, textBat, &srcrectBat, &dstrectBat2);
				SDL_RenderCopy(ren, textArrow, &srcrectArrow, &dstrectArrow);
				if (enemy1.health <= 0) {
					dstrectDeadEnemy1 = { xDeadEnemy1, yDeadEnemy1, 75, 75 };
					SDL_RenderCopy(ren, textdeadEenemy, &srcrectDeadEnemy, &dstrectDeadEnemy1);
				}
				else if (enemy2.health <= 0) {
					dstrectDeadEnemy2 = { xDeadEnemy2, yDeadEnemy2, 75, 75 };
					SDL_RenderCopy(ren, textdeadEenemy, &srcrectDeadEnemy, &dstrectDeadEnemy2);
				}
				SDL_RenderPresent(ren);

				while (SDL_PollEvent(&ev) != NULL) {
					switch (ev.type) {
					case SDL_KEYDOWN:
						switch (ev.key.keysym.scancode) {
						case SDL_SCANCODE_LEFT:
							if (pointer != 1) {
								xArrow -= 125;
								pointer--;
							}
							break;
						case SDL_SCANCODE_A:
							if (pointer != 1) {
								xArrow -= 125;
								pointer--;
							}
							break;
						case SDL_SCANCODE_RIGHT:
							if (pointer != 2) {
								xArrow += 125;
								pointer++;
							}
							break;
						case SDL_SCANCODE_D:
							if (pointer != 2) {
								xArrow += 125;
								pointer++;
							}
							break;
						}

					}

				}

				if (pointer == 1 and arrowState[SDL_SCANCODE_RETURN]) hitEnemy = 1;
				if (pointer == 2 and arrowState[SDL_SCANCODE_RETURN]) hitEnemy = 2;

			}
			if (hitEnemy == 1 and enemy1.health > 0) {
				SDL_Delay(200);
				enemy1.health = enemy1.health - hero.Attack;
				if (enemy1.health <= 0) {
					enemy1.atk = 0;
					livedEnemies -= 1;
					hero.Gold += enemy1.gold;
					hero.experience += enemy1.level;
				}
			}
			if (hitEnemy == 2 and enemy2.health > 0) {
				SDL_Delay(200);
				enemy2.health = enemy2.health - hero.Attack;
				if (enemy2.health <= 0) {
					enemy2.atk = 0;
					livedEnemies -= 1;
					hero.Gold += enemy2.gold;
					hero.experience += enemy2.level;
				}
			}
			hero.Health = hero.Health - enemy1.atk;
			if (hero.Health <= 0) de_init(1);
			hero.Health = hero.Health - enemy2.atk;
			if (hero.Health <= 0) de_init(1);
		}
	if (amountEnemy == 3 and livedEnemies >= 1 and hero.Health > 0) {
			int hitEnemy = 0;
			while (hitEnemy == 0) {
				dstrectArrow = { xArrow, yArrow, 75, 75 };
				dstrectBat = { xEnemy1, yEnemy1, 75, 75 };
				dstrectBat2 = { xEnemy2, yEnemy2, 75, 75 };
				dstrectBat3 = { xEnemy3, yEnemy3, 75, 75 };
				SDL_SetRenderDrawColor(ren, 200, 200, 200, 0);
				SDL_RenderClear(ren);
				SDL_RenderCopy(ren, textBattle, NULL, NULL);
				SDL_RenderCopy(ren, textBat, &srcrectBat, &dstrectBat);
				SDL_RenderCopy(ren, textBat, &srcrectBat, &dstrectBat2);
				SDL_RenderCopy(ren, textBat, &srcrectBat, &dstrectBat3);
				SDL_RenderCopy(ren, textArrow, &srcrectArrow, &dstrectArrow);
				if (enemy1.health <= 0) {
					dstrectDeadEnemy1 = { xDeadEnemy1, yDeadEnemy1, 75, 75 };
					SDL_RenderCopy(ren, textdeadEenemy, &srcrectDeadEnemy, &dstrectDeadEnemy1);
					
				}
				else if (enemy2.health <= 0) {
					dstrectDeadEnemy2 = { xDeadEnemy2, yDeadEnemy2, 75, 75 };
					SDL_RenderCopy(ren, textdeadEenemy, &srcrectDeadEnemy, &dstrectDeadEnemy2);
					
				}
				else if (enemy3.health <= 0) {
					dstrectDeadEnemy3 = { xDeadEnemy3, yDeadEnemy3, 75, 75 };
					SDL_RenderCopy(ren, textdeadEenemy, &srcrectDeadEnemy, &dstrectDeadEnemy3);
					
				}
				SDL_RenderPresent(ren);


				while (SDL_PollEvent(&ev) != NULL) {
					switch (ev.type) {
					case SDL_KEYDOWN:
						switch (ev.key.keysym.scancode) {
						case SDL_SCANCODE_LEFT:
							if (pointer != 1) {
								xArrow -= 125;
								pointer--;
							}
							break;
						case SDL_SCANCODE_A:
							if (pointer != 1) {
								xArrow -= 125;
								pointer--;
							}
							break;
						case SDL_SCANCODE_RIGHT:
							if (pointer != 3) {
								xArrow += 125;
								pointer++;
							}
							break;
						case SDL_SCANCODE_D:
							if (pointer != 3) {
								xArrow += 125;
								pointer++;
							}
							break;
						}

					}
				}

				if (pointer == 1 and arrowState[SDL_SCANCODE_RETURN]) hitEnemy = 1;
				if (pointer == 2 and arrowState[SDL_SCANCODE_RETURN]) hitEnemy = 2;
				if (pointer == 3 and arrowState[SDL_SCANCODE_RETURN]) hitEnemy = 3;

			}
			if (hitEnemy == 1 and enemy1.health > 0) {
				SDL_Delay(200);
				enemy1.health = enemy1.health - hero.Attack;
				if (enemy1.health <= 0) {
					enemy1.atk = 0;
					livedEnemies -= 1;
					hero.Gold += enemy1.gold;
					hero.experience += enemy1.level;
				}
			}
			if (hitEnemy == 2 and enemy2.health > 0) {
				SDL_Delay(200);
				enemy2.health = enemy2.health - hero.Attack;
				if (enemy2.health <= 0) {
					enemy2.atk = 0;
					livedEnemies -= 1;
					hero.Gold += enemy2.gold;
					hero.experience += enemy2.level;
				}
			}
			if (hitEnemy == 3 and enemy3.health > 0) {
				SDL_Delay(200);
				enemy3.health = enemy3.health - hero.Attack;
				if (enemy3.health <= 0) {
					enemy3.atk = 0;
					livedEnemies -= 1;
					hero.Gold += enemy3.gold;
					hero.experience += enemy3.level;
				}
			}
			hero.Health = hero.Health - enemy1.atk;
			if (hero.Health <= 0) de_init(1);
			hero.Health = hero.Health - enemy2.atk;
			if (hero.Health <= 0) de_init(1);
			hero.Health = hero.Health - enemy3.atk;
			if (hero.Health <= 0) de_init(1);
		}
	SDL_DestroyTexture(textBat);
	SDL_DestroyTexture(textArrow);
	SDL_DestroyTexture(textBattle);
	SDL_DestroyTexture(textdeadEenemy);
	flag = 1;
}

void Fireball() {
	abilityDamageFireball;
	if (hero.Mana >= 15) {
		hero.Mana -= 15;
		if (choiceEnemy == 1)
			enemy1.health -= abilityDamageFireball;
		else if (choiceEnemy == 2)
			enemy2.health -= abilityDamageFireball;
		else if (choiceEnemy == 3)
			enemy3.health -= abilityDamageFireball;
	}
	else printf("not enough mana\n");
}

void Lightning() {
	abilityDamageLighting;
	if (hero.Mana >= 25 and lightingEffect == false) {
		hero.Mana -= 25;
		if (choiceEnemy == 1)
			enemy1.health -= abilityDamageLighting;
		else if (choiceEnemy == 2)
			enemy2.health -= abilityDamageLighting;
		else if (choiceEnemy == 3)
			enemy3.health -= abilityDamageLighting;
	}
}

void Poison() {
	abilityDamagePosion;
	if (hero.Mana >= 18 and posionEffect == false) {
		hero.Mana -= 18;
		if (choiceEnemy == 1)
			enemy1.isPoison = true;
		else if (choiceEnemy == 2)
			enemy2.isPoison = true;
		else if (choiceEnemy == 3)
			enemy3.isPoison = true;
	}
	else if (hero.Mana < 18) printf("not enough mana\n");

	if (enemy1.isPoison == true and enemy1.health <= 0)
		enemy1.isPoison = false;
	else if (enemy2.isPoison == true and enemy2.health <= 0)
		enemy2.isPoison = false;
	else if (enemy3.isPoison == true and enemy3.health <= 0)
		enemy3.isPoison = false;

	if (enemy1.isPoison == true) {
		enemy1.health -= abilityDamagePosion;
		abilityDamagePosion--;
	}
	else if (enemy2.isPoison == true) {
		enemy2.health -= abilityDamagePosion;
		abilityDamagePosion--;
	}
	else if (enemy3.isPoison == true) {
		enemy3.health -= abilityDamagePosion;
		abilityDamagePosion--;
	}

	if (abilityDamagePosion == 0)
		enemy1.isPoison, enemy2.isPoison, enemy3.isPoison = false;
}