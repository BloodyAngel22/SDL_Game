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

int amountEnemy;
int ratio;
warrior hero;
Enemy opponent;

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
	#pragma endregion
	SDL_Event ev;
	SDL_PollEvent(&ev);
	StartBattle();
	while ((hero.Health > 0) and (opponent.Health > 0)) {
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

			SDL_SetRenderDrawColor(ren, 200, 200, 200, 0);
			SDL_RenderClear(ren);
			SDL_RenderCopy(ren, textBattle, NULL, NULL);
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


			if (pointer == 1 and arrowState[SDL_SCANCODE_RETURN]) choiche = BATTLE;
			if (pointer == 2 and arrowState[SDL_SCANCODE_RETURN]) choiche = ABILITY;
			if (pointer == 3 and arrowState[SDL_SCANCODE_RETURN]) choiche = ESCAPE;

		}
			if (choiche == BATTLE) {
				SDL_Delay(250);
				system("cls");
				Battle();
				if (posionEffect == true) Poison();
				printf("%d\n", opponent.Health);
			}
			if (choiche == ABILITY) {
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
				if (choiceSpell == FIREBOLT) {
					Fireball();
					SDL_Delay(165);
					printf("%d\n", opponent.Health);
					hero.Health -= opponent.Attack;
					if (hero.Health <= 0)
						exit(1);
				}
				else if (choiceSpell == LIGHTING) {
					Lightning();
					SDL_Delay(165);
					printf("%d\n", opponent.Health);
					hero.Health -= opponent.Attack;
					if (hero.Health <= 0)
						exit(1);
				}
				else if (choiceSpell == POISON) {
					Poison();
					SDL_Delay(165);
					printf("%d\n", opponent.Health);
					hero.Health -= opponent.Attack;
					if (hero.Health <= 0)
						exit(1);
				}
				if (opponent.Health <= 0) {
					printf("%d\n", opponent.Health);
					hero.experience += opponent.experienceEnemy;
					if (hero.experience >= hero.levelUp)
						level_up();
				}
			}
			if (choiche == ESCAPE) {
				SDL_Delay(250);
				int storageEscape = escape();
				if (ChanceEscape >= storageEscape) {
					printf("You managed to escape\n");
					opponent.Health = 0;
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

void recovery_enemy() {
	opponent.Health = opponent.maxHealth;
}

int escape() {
	return rand() % 100;
}

int randomAmountEnemy() {
	return rand() % (4 - 2) + 2;
}

void generateEnemy() {
	enemy1.atk = opponent.Attack; enemy1.health = opponent.Health; enemy1.gold = opponent.Gold, enemy1.level = opponent.level;
	enemy2.atk = opponent.Attack; enemy2.health = opponent.Health; enemy2.gold = opponent.Gold, enemy2.level = opponent.level;
	enemy3.atk = opponent.Attack; enemy3.health = opponent.Health; enemy3.gold = opponent.Gold, enemy3.level = opponent.level;
	enemy4.atk = opponent.Attack; enemy4.health = opponent.Health; enemy4.gold = opponent.Gold, enemy4.level = opponent.level;

}

void Battler() {
	generateEnemy();
	amountEnemy = randomAmountEnemy();
	int livedEnemies = amountEnemy;
	if (amountEnemy == 2 and livedEnemies >= 1 and hero.Health > 0) {
		int hitEnemy = 0;
		if (hitEnemy == 1) {
			enemy1.health = enemy1.health - hero.Attack;
			if (enemy1.health <= 0) {
				livedEnemies -= 1;
				hero.Gold += enemy1.gold;
				hero.level += enemy1.level;
			}
		}
		if (hitEnemy == 2) {
			enemy2.health = enemy2.health - hero.Attack;
			if (enemy2.health <= 0) {
				livedEnemies -= 1;
				hero.Gold += enemy2.gold;
				hero.level += enemy2.level;
			}
		}
		hero.Health = hero.Health - enemy1.atk;
		if (hero.Health <= 0) de_init(1);
		hero.Health = hero.Health - enemy2.atk;
		if (hero.Health <= 0) de_init(1);
	}
	if (amountEnemy == 3 and livedEnemies >= 1 and hero.Health > 0) {
		int hitEnemy = 0;
		if (hitEnemy == 1) {
			enemy1.health = enemy1.health - hero.Attack;
			if (enemy1.health <= 0) {
				livedEnemies -= 1;
				hero.Gold += enemy1.gold;
				hero.level += enemy1.level;
			}
		}
		if (hitEnemy == 2) {
			enemy2.health = enemy2.health - hero.Attack;
			if (enemy2.health <= 0) {
				livedEnemies -= 1;
				hero.Gold += enemy2.gold;
				hero.level += enemy2.level;
			}
		}
		if (hitEnemy == 3) {
			enemy3.health = enemy3.health - hero.Attack;
			if (enemy3.health <= 0) {
				livedEnemies -= 1;
				hero.Gold += enemy3.gold;
				hero.level += enemy3.level;
			}
		}
		hero.Health = hero.Health - enemy1.atk;
		if (hero.Health <= 0) de_init(1);
		hero.Health = hero.Health - enemy2.atk;
		if (hero.Health <= 0) de_init(1);
		hero.Health = hero.Health - enemy3.atk;
		if (hero.Health <= 0) de_init(1);
	}
	if (amountEnemy == 4 and livedEnemies >= 1 and hero.Health > 0) {
		int hitEnemy = 0;
		if (hitEnemy == 1) {
			enemy1.health = enemy1.health - hero.Attack;
			if (enemy1.health <= 0) {
				livedEnemies -= 1;
				hero.Gold += enemy1.gold;
				hero.level += enemy1.level;
			}
		}
		if (hitEnemy == 2) {
			enemy2.health = enemy2.health - hero.Attack;
			if (enemy2.health <= 0) {
				livedEnemies -= 1;
				hero.Gold += enemy2.gold;
				hero.level += enemy2.level;
			}
		}
		if (hitEnemy == 3) {
			enemy3.health = enemy3.health - hero.Attack;
			if (enemy3.health <= 0) {
				livedEnemies -= 1;
				hero.Gold += enemy3.gold;
				hero.level += enemy3.level;
			}
		}
		if (hitEnemy == 4) {
			enemy4.health = enemy4.health - hero.Attack;
			if (enemy4.health <= 0) {
				livedEnemies -= 1;
				hero.Gold += enemy4.gold;
				hero.level += enemy4.level;
			}
		}
		hero.Health = hero.Health - enemy1.atk;
		if (hero.Health <= 0) de_init(1);
		hero.Health = hero.Health - enemy2.atk;
		if (hero.Health <= 0) de_init(1);
		hero.Health = hero.Health - enemy3.atk;
		if (hero.Health <= 0) de_init(1);
		hero.Health = hero.Health - enemy4.atk;
		if (hero.Health <= 0) de_init(1);
	}
}