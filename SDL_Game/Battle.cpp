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
#define AttackEnemy 1
#define ShieldEnemy 2
#define HealEnemy 3
#define VampirismEnemy 4
#define CritEnemy 5
#define Win 0
#define Lose 1

int stepFight = 1;
extern int abilityDamageLightning = 48, abilityDamageFireball = 30, abilityDamagePoison = 6;
extern bool posionEffect = false;
extern bool lightingEffect = false;
extern int choiceEnemy = 0;
extern int poisonDamage = abilityDamagePoison;
int amountEnemy;
int livedEnemies = 1;
int curAction, nextAction, action = 1, flagPattern = 0;
int ratio;
bool isEnterPressed = 0, wasEnterPressed = 0, isPressed = 0;
bool isEscapePressed = 0, wasEscapePressed = 0, isPressedEscape = 0;
Character hero;
EnemyCharacteristics batCharacteristics, goblinCharacteristics, slimeCharacteristics, werewolfCharacteristics, ratCharacteristics;
ClassMage mage;
ClassWarrior warrior;
genEnemy enemy1, enemy2, enemy3, enemy4;
SDL_Rect srcrectDeadEnemy = { 0, 0, 100, 140 };
SDL_Rect srcrectBat = { 0, 0, 100, 140 };
SDL_Rect srcrectGoblin = { 71, 25, 141, 127 };
SDL_Rect srcrectWerewolf = { 106, 89, 162, 155 };
SDL_Rect srcRat = { 52, 34, 114, 88 };
SDL_Rect dstrectDeadEnemy1; SDL_Rect dstrectDeadEnemy2; SDL_Rect dstrectDeadEnemy3; SDL_Rect dstrectDeadEnemy4;
SDL_Rect dstrect; SDL_Rect dstrect2; SDL_Rect dstrect3;
//Icons
SDL_Rect AtkIcon = { 655, 285, 49, 49 };
SDL_Rect HealIcon = { 522, 231, 49, 49 };
SDL_Rect ShieldIcon = { 415, 285, 49, 49 };
SDL_Rect VampirismIcon = { 337,66,49,49 };
SDL_Rect CritIcon = { 654,66,49,49 };
SDL_Rect positionIcon = { 0,0, 45, 45 };
//
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
	const Uint8* escapeState = SDL_GetKeyboardState(NULL);
	wasEscapePressed = 0;
	if (!escapeState[SDL_SCANCODE_ESCAPE]) isEscapePressed = 0;

	if (escapeState[SDL_SCANCODE_ESCAPE] and wasEscapePressed == 0 and isEscapePressed == 0) {
		isEscapePressed = 1;
		return 1;
	}
	else return 0;
}

void MenuBattle(SDL_Renderer* ren, int enemy); void StartBattle(); void Battle(); int escape();

void MenuBattle(SDL_Renderer* ren, int enemy) {
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
		SDL_Texture* textdeadEnemy = SDL_CreateTextureFromSurface(ren, surfdeadEnemy);
		SDL_FreeSurface(surfdeadEnemy);
		//
		SDL_Surface* surfBat = IMG_Load("sprites\\enemy\\bat.png");
		SDL_Texture* textBat = SDL_CreateTextureFromSurface(ren, surfBat);
		SDL_FreeSurface(surfBat);
		//
		SDL_Surface* surfGoblin = IMG_Load("sprites\\enemy\\goblin.png");
		SDL_Texture* textGoblin = SDL_CreateTextureFromSurface(ren, surfGoblin);
		SDL_FreeSurface(surfGoblin);
		//
		SDL_Surface* surfSlime = IMG_Load("sprites\\enemy\\red_slime.png");
		SDL_Texture* textSlime = SDL_CreateTextureFromSurface(ren, surfSlime);
		SDL_FreeSurface(surfSlime);
		//
		SDL_Surface* surfWerewolf = IMG_Load("sprites\\enemy\\werewolf.png");
		SDL_Texture* textWerewolf = SDL_CreateTextureFromSurface(ren, surfWerewolf);
		SDL_FreeSurface(surfWerewolf);
		//Rat
		SDL_Surface* surfRat = IMG_Load("sprites\\enemy\\rat.png");
		SDL_Texture* textRat = SDL_CreateTextureFromSurface(ren, surfRat);
		SDL_FreeSurface(surfRat);
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
		//Icons
		SDL_Surface* surfIcons = IMG_Load("sprites\\enemy\\icons.jpg");
		SDL_Texture* textIcons = SDL_CreateTextureFromSurface(ren, surfIcons);
		SDL_FreeSurface(surfIcons);
		#pragma endregion

	SDL_Event ev;
	SDL_PollEvent(&ev);
	StartBattle();
	
	stepFight = 1;
	action = 1;

	if (enemy == Bat)
		generateEnemy(Bat);
	if (enemy == Goblin)
		generateEnemy(Goblin);
	if (enemy == Slime)
		generateEnemy(Slime);
	if (enemy == Werewolf)
		generateEnemy(Werewolf);
	if (enemy == Rat)
		generateEnemy(Rat);
	amountEnemy = randomAmountEnemy();
	livedEnemies = amountEnemy;

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
			if (enemy == Bat) {
				render_enemy(Bat, ren, textBat, textGoblin, textSlime, textWerewolf, textRat);
			}
			if (enemy == Goblin) {
				render_enemy(Goblin, ren, textBat, textGoblin, textSlime, textWerewolf, textRat);
			}
			if (enemy == Slime) {
				render_enemy(Slime, ren, textBat, textGoblin, textSlime, textWerewolf, textRat);
			}
			if (enemy == Werewolf) {
				render_enemy(Werewolf, ren, textBat, textGoblin, textSlime, textWerewolf, textRat);
			}
			if (enemy == Rat) {
				render_enemy(Rat, ren, textBat, textGoblin, textSlime, textWerewolf, textRat);
			}
			render_dead_enemy(ren, textdeadEnemy);
			flagPattern = 0;
			if (enemy == Bat)
				enemy_patterns(Bat);
			if (enemy == Goblin)
				enemy_patterns(Goblin);
			if (enemy == Slime)
				enemy_patterns(Slime);
			if (enemy == Werewolf)
				enemy_patterns(Werewolf);
			if (enemy == Rat)
				enemy_patterns(Rat);
			check_pattern(ren, textIcons);

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
				if (enemy == Bat)
					Battler(ren, Bat);
				if (enemy == Goblin)
					Battler(ren, Goblin);
				if (enemy == Slime) {
					Battler(ren, Slime);
				}
				if (enemy == Werewolf)
					Battler(ren, Werewolf);
				if (enemy == Rat)
					Battler(ren, Rat);
				if (hero.Health <= 0) {
					SDL_DestroyTexture(textdeadEnemy);
					SDL_DestroyTexture(textArrow);
					SDL_DestroyTexture(textBattle);
					SDL_DestroyTexture(textBat);
					SDL_DestroyTexture(textEnemyHealthTTF);
					SDL_DestroyTexture(textCharacter);
					SDL_DestroyTexture(textGoblin);
					SDL_DestroyTexture(textSlime);
					SDL_DestroyTexture(textWerewolf);
					SDL_DestroyTexture(textRat);
					TTF_CloseFont(enemyTTF);
					SDL_DestroyTexture(textIcons);
					livedEnemies = 0;
					reward(ren, Lose);
					return;
				}
				if (enemy1.isPoison == true or enemy2.isPoison == true or enemy3.isPoison == true) Poison();
				printf("%d\n", batCharacteristics.Health);
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
					if (enemy == Bat) {
						render_enemy(Bat, ren, textBat, textGoblin, textSlime, textWerewolf, textRat);
					}
					if (enemy == Goblin) {
						render_enemy(Goblin, ren, textBat, textGoblin, textSlime, textWerewolf, textRat);
					}
					if (enemy == Slime) {
						render_enemy(Slime, ren, textBat, textGoblin, textSlime, textWerewolf, textRat);
					}
					if (enemy == Werewolf) {
						render_enemy(Werewolf, ren, textBat, textGoblin, textSlime, textWerewolf, textRat);
					}
					if (enemy == Rat) {
						render_enemy(Rat, ren, textBat, textGoblin, textSlime, textWerewolf, textRat);
					}
					render_dead_enemy(ren, textdeadEnemy);

					flagPattern = 0;
					if (enemy == Bat)
						enemy_patterns(Bat);
					if (enemy == Goblin)
						enemy_patterns(Goblin);
					if (enemy == Slime)
						enemy_patterns(Slime);
					if (enemy == Werewolf)
						enemy_patterns(Werewolf);
					if (enemy == Rat)
						enemy_patterns(Rat);
					check_pattern(ren, textIcons);

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
						if (enemy == Bat) {
							render_enemy(Bat, ren, textBat, textGoblin, textSlime, textWerewolf, textRat);
						}
						if (enemy == Goblin) {
							render_enemy(Goblin, ren, textBat, textGoblin, textSlime, textWerewolf, textRat);
						}
						if (enemy == Slime) {
							render_enemy(Slime, ren, textBat, textGoblin, textSlime, textWerewolf, textRat);
						}
						if (enemy == Werewolf) {
							render_enemy(Werewolf, ren, textBat, textGoblin, textSlime, textWerewolf, textRat);
						}
						if (enemy == Rat) {
							render_enemy(Rat, ren, textBat, textGoblin, textSlime, textWerewolf, textRat);
						}
						render_dead_enemy(ren, textdeadEnemy);

						flagPattern = 0;
						if (enemy == Bat)
							enemy_patterns(Bat);
						if (enemy == Goblin)
							enemy_patterns(Goblin);
						if (enemy == Slime)
							enemy_patterns(Slime);
						if (enemy == Werewolf)
							enemy_patterns(Werewolf);
						if (enemy == Rat)
							enemy_patterns(Rat);
						check_pattern(ren, textIcons);

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
						}
						else if (choiceSpell == LIGHTING) {
							Lightning();
						}
						else if (choiceSpell == POISON) {
							Poison();
						}
						if (enemy1.health <= 0) {
							enemy1.atk = 0;
							livedEnemies -= 1;
							hero.Gold += enemy1.gold;
						}
					}
					else if (choiceEnemy == 2) {
						//SDL_Delay(150);
						if (choiceSpell == FIREBOLT) {
							Fireball();
						}
						if (choiceSpell == LIGHTING) {
							Lightning();
						}
						if (choiceSpell == POISON) {
							Poison();
						}
						if (enemy2.health <= 0) {
							enemy2.atk = 0;
							livedEnemies -= 1;
							hero.Gold += enemy2.gold;
						}
					}
					flagPattern = 1;
					if (enemy == Bat)
						enemy_patterns(Bat);
					if (enemy == Goblin)
						enemy_patterns(Goblin);
					if (enemy == Slime)
						enemy_patterns(Slime);
					if (enemy == Werewolf)
						enemy_patterns(Werewolf);
					if (enemy == Rat)
						enemy_patterns(Rat);
					if (hero.Health <= 0) {
						SDL_DestroyTexture(textdeadEnemy);
						SDL_DestroyTexture(textArrow);
						SDL_DestroyTexture(textBattle);
						SDL_DestroyTexture(textBat);
						SDL_DestroyTexture(textEnemyHealthTTF);
						SDL_DestroyTexture(textCharacter);
						SDL_DestroyTexture(textGoblin);
						SDL_DestroyTexture(textSlime);
						SDL_DestroyTexture(textWerewolf);
						SDL_DestroyTexture(textRat);
						TTF_CloseFont(enemyTTF);
						SDL_DestroyTexture(textIcons);
						livedEnemies = 0;
						reward(ren, Lose);
						return;
					}
					stepFight += 1;
					action += 1;
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

						if (enemy == Bat) {
							render_enemy(Bat, ren, textBat, textGoblin, textSlime, textWerewolf, textRat);
						}
						if (enemy == Goblin) {
							render_enemy(Goblin, ren, textBat, textGoblin, textSlime, textWerewolf, textRat);
						}
						if (enemy == Slime) {
							render_enemy(Slime, ren, textBat, textGoblin, textSlime, textWerewolf, textRat);
						}
						if (enemy == Werewolf) {
							render_enemy(Werewolf, ren, textBat, textGoblin, textSlime, textWerewolf, textRat);
						}
						if (enemy == Rat) {
							render_enemy(Rat, ren, textBat, textGoblin, textSlime, textWerewolf, textRat);
						}
						render_dead_enemy(ren, textdeadEnemy);

						flagPattern = 0;
						if (enemy == Bat)
							enemy_patterns(Bat);
						if (enemy == Goblin)
							enemy_patterns(Goblin);
						if (enemy == Slime)
							enemy_patterns(Slime);
						if (enemy == Werewolf)
							enemy_patterns(Werewolf);
						if (enemy == Rat)
							enemy_patterns(Rat);
						check_pattern(ren, textIcons);

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
							
						}
						if (choiceSpell == LIGHTING) {
							Lightning();
							
						}
						if (choiceSpell == POISON) {
							Poison();
							
						}
						if (enemy1.health <= 0) {
							enemy1.atk = 0;
							livedEnemies -= 1;
							hero.Gold += enemy1.gold;
						}
					}
					if (choiceEnemy == 2) {
						//SDL_Delay(150);
						if (choiceSpell == FIREBOLT) {
							Fireball();
							
						}
						if (choiceSpell == LIGHTING) {
							Lightning();
							
						}
						if (choiceSpell == POISON) {
							Poison();
							
						}
						if (enemy2.health <= 0) {
							enemy2.atk = 0;
							livedEnemies -= 1;
							hero.Gold += enemy2.gold;
						}
					}
					if (choiceEnemy == 3) {
						//SDL_Delay(150);
						if (choiceSpell == FIREBOLT) {
							Fireball();
						}
						if (choiceSpell == LIGHTING) {
							Lightning();
						
						}
						if (choiceSpell == POISON) {
							Poison();
							
						}
						if (enemy3.health <= 0) {
							enemy3.atk = 0;
							livedEnemies -= 1;
							hero.Gold += enemy3.gold;
						}
					}
					flagPattern = 1;
					if (enemy == Bat)
						enemy_patterns(Bat);
					if (enemy == Goblin)
						enemy_patterns(Goblin);
					if (enemy == Slime)
						enemy_patterns(Slime);
					if (enemy == Werewolf)
						enemy_patterns(Werewolf);
					if (enemy == Rat)
						enemy_patterns(Rat);
					if (hero.Health <= 0) {
						SDL_DestroyTexture(textdeadEnemy);
						SDL_DestroyTexture(textArrow);
						SDL_DestroyTexture(textBattle);
						SDL_DestroyTexture(textBat);
						SDL_DestroyTexture(textEnemyHealthTTF);
						SDL_DestroyTexture(textCharacter);
						SDL_DestroyTexture(textGoblin);
						SDL_DestroyTexture(textSlime);
						SDL_DestroyTexture(textWerewolf);
						SDL_DestroyTexture(textRat);
						TTF_CloseFont(enemyTTF);
						SDL_DestroyTexture(textIcons);
						livedEnemies = 0;
						reward(ren, Lose);
						return;
					}
					stepFight += 1;
					action += 1;
				}

				
			}
			else if (choiche == ESCAPE) {
				//SDL_Delay(250);
				int storageEscape = escape();
				if (ChanceEscape >= storageEscape) {
					printf("You managed to escape\n");
					livedEnemies = 0;
					SDL_DestroyTexture(textdeadEnemy);
					SDL_DestroyTexture(textArrow);
					SDL_DestroyTexture(textBattle);
					SDL_DestroyTexture(textBat);
					SDL_DestroyTexture(textCharacter);
					SDL_DestroyTexture(textGoblin);
					SDL_DestroyTexture(textSlime);
					SDL_DestroyTexture(textWerewolf);
					SDL_DestroyTexture(textRat);
					SDL_DestroyTexture(textEnemyHealthTTF);
					SDL_DestroyTexture(textIcons);

					reward(ren, Lose);
					return;
				}
				else {
					printf("You failed to escape\n");
					if (enemy == Bat) {
						enemy_patterns(Bat);
					}
					if (enemy == Goblin) {
						enemy_patterns(Goblin);
					}
					if (enemy == Slime) {
						enemy_patterns(Slime);
					}
					if (enemy == Werewolf)
						enemy_patterns(Werewolf);
					stepFight += 1;
					printf("the enemy has damaged you %d\n", batCharacteristics.Attack);
					if (hero.Health <= 0) {
						SDL_DestroyTexture(textdeadEnemy);
						SDL_DestroyTexture(textArrow);
						SDL_DestroyTexture(textBattle);
						SDL_DestroyTexture(textBat);
						SDL_DestroyTexture(textEnemyHealthTTF);
						SDL_DestroyTexture(textCharacter);
						SDL_DestroyTexture(textGoblin);
						SDL_DestroyTexture(textSlime);
						SDL_DestroyTexture(textWerewolf);
						SDL_DestroyTexture(textRat);
						TTF_CloseFont(enemyTTF);
						SDL_DestroyTexture(textIcons);
						livedEnemies = 0;
						reward(ren, Lose);
						return;
					}
						
				}
			}
	}
	SDL_DestroyTexture(textdeadEnemy);
	SDL_DestroyTexture(textArrow);
	SDL_DestroyTexture(textBattle);
	SDL_DestroyTexture(textBat);
	SDL_DestroyTexture(textEnemyHealthTTF);
	SDL_DestroyTexture(textCharacter);
	SDL_DestroyTexture(textGoblin);
	SDL_DestroyTexture(textSlime);
	SDL_DestroyTexture(textWerewolf);
	SDL_DestroyTexture(textRat);
	TTF_CloseFont(enemyTTF);
	SDL_DestroyTexture(textIcons);

	if (livedEnemies < 1) {
		abilityDamagePoison = poisonDamage;
		hero.experience += (enemy1.level * amountEnemy);
		recovery_character();
		if (hero.experience >= hero.levelUp)
			level_up();
		if (questFlag and (curQuest == 1 or curQuest == 2) and enemy == Bat)
			counterKilledEnemies += 1;
		if (questFlag and curQuest == 3 and enemy == Goblin)
			counterKilledEnemies += 1;
		reward(ren, Win);
	}
}

void Battler(SDL_Renderer* ren, int enemy) {
#pragma region Texture
	//Battle menu
	SDL_Surface* surfBattle = IMG_Load("sprites\\menu\\battle.png");
	SDL_Texture* textBattle = SDL_CreateTextureFromSurface(ren, surfBattle);
	SDL_FreeSurface(surfBattle);
	//
	SDL_Surface* surfBat = IMG_Load("sprites\\enemy\\bat.png");
	SDL_Texture* textBat = SDL_CreateTextureFromSurface(ren, surfBat);
	SDL_FreeSurface(surfBat);
	//
	SDL_Surface* surfGoblin = IMG_Load("sprites\\enemy\\goblin.png");
	SDL_Texture* textGoblin = SDL_CreateTextureFromSurface(ren, surfGoblin);
	SDL_FreeSurface(surfGoblin);
	//
	SDL_Surface* surfSlime = IMG_Load("sprites\\enemy\\red_slime.png");
	SDL_Texture* textSlime = SDL_CreateTextureFromSurface(ren, surfSlime);
	SDL_FreeSurface(surfSlime);
	//
	SDL_Surface* surfWerewolf = IMG_Load("sprites\\enemy\\werewolf.png");
	SDL_Texture* textWerewolf = SDL_CreateTextureFromSurface(ren, surfWerewolf);
	SDL_FreeSurface(surfWerewolf);
	//Rat
	SDL_Surface* surfRat = IMG_Load("sprites\\enemy\\rat.png");
	SDL_Texture* textRat = SDL_CreateTextureFromSurface(ren, surfRat);
	SDL_FreeSurface(surfRat);
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
	//Icons
	SDL_Surface* surfIcons = IMG_Load("sprites\\enemy\\icons.jpg");
	SDL_Texture* textIcons = SDL_CreateTextureFromSurface(ren, surfIcons);
	SDL_FreeSurface(surfIcons);
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

	/*if (livedEnemies < 1) {
		SDL_DestroyTexture(textBat);
		SDL_DestroyTexture(textArrow);
		SDL_DestroyTexture(textBattle);
		SDL_DestroyTexture(textdeadEenemy);
		SDL_DestroyTexture(textCharacter);
		SDL_DestroyTexture(textGoblin);
		SDL_DestroyTexture(textSlime);
		SDL_DestroyTexture(textWerewolf);
		SDL_DestroyTexture(textRat);
		SDL_DestroyTexture(textAtk);
		SDL_DestroyTexture(textEnemyHealthTTF);
		SDL_DestroyTexture(textIcons);

		hero.experience += enemy1.level * amountEnemy;
		if (hero.experience >= hero.levelUp)
			level_up();
		flag = 1;
		return;
	}*/

	if (amountEnemy == 2 and livedEnemies >= 1 and hero.Health > 0) {
			int hitEnemy = 0;
			while (hitEnemy == 0) {
				dstrectArrow = { xArrow, yArrow, 75, 75 };
				SDL_SetRenderDrawColor(ren, 200, 200, 200, 0);
				SDL_RenderClear(ren);
				SDL_RenderCopy(ren, textBattle, NULL, NULL);
				SDL_RenderCopy(ren, textCharacter, &srcrectCharacter, &dstrectCharacter);
				if (enemy == Bat) {
					render_enemy(Bat, ren, textBat, textGoblin, textSlime, textWerewolf, textRat);
				}
				if (enemy == Goblin) {
					render_enemy(Goblin, ren, textBat, textGoblin, textSlime, textWerewolf, textRat);
				}
				if (enemy == Slime) {
					render_enemy(Slime, ren, textBat, textGoblin, textSlime, textWerewolf, textRat);
				}
				if (enemy == Werewolf) {
					render_enemy(Werewolf, ren, textBat, textGoblin, textSlime, textWerewolf, textRat);
				}
				if (enemy == Rat) {
					render_enemy(Rat, ren, textBat, textGoblin, textSlime, textWerewolf, textRat);
				}
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
				flagPattern = 0;
				if (enemy == Bat)
					enemy_patterns(Bat);
				if (enemy == Goblin)
					enemy_patterns(Goblin);
				if (enemy == Slime)
					enemy_patterns(Slime);
				if (enemy == Werewolf)
					enemy_patterns(Werewolf);
				if (enemy == Rat)
					enemy_patterns(Rat);
				check_pattern(ren, textIcons);


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
				}
			}
			if (hitEnemy == 2 and enemy2.health > 0) {
				//SDL_Delay(200);
				enemy2.health = enemy2.health - hero.Attack;
				if (enemy2.health <= 0) {
					enemy2.atk = 0;
					livedEnemies -= 1;
					hero.Gold += enemy2.gold;
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
					if (enemy == Bat) {
						render_enemy(Bat, ren, textBat, textGoblin, textSlime, textWerewolf, textRat);
					}
					if (enemy == Goblin) {
						render_enemy(Goblin, ren, textBat, textGoblin, textSlime, textWerewolf, textRat);
					}
					if (enemy == Slime) {
						render_enemy(Slime, ren, textBat, textGoblin, textSlime, textWerewolf, textRat);
					}
					if (enemy == Werewolf) {
						render_enemy(Werewolf, ren, textBat, textGoblin, textSlime, textWerewolf, textRat);
					}
					if (enemy == Rat) {
						render_enemy(Rat, ren, textBat, textGoblin, textSlime, textWerewolf, textRat);
					}
					SDL_RenderCopy(ren, textAtk, &srcrectAtk, &dstrectAtk);
					SDL_RenderPresent(ren);
					SDL_Delay(70);
				}
				if (frameFlag == 4) {
					animation = 0;
					frameFlag = 0;
				}
			}
			flagPattern = 1;
			if (enemy == Bat)
				enemy_patterns(Bat);
			if (enemy == Goblin)
				enemy_patterns(Goblin);
			if (enemy == Slime)
				enemy_patterns(Slime);
			if (enemy == Werewolf)
				enemy_patterns(Werewolf);
			if (enemy == Rat)
				enemy_patterns(Rat);
			if (hero.Health <= 0) {
				SDL_DestroyTexture(textdeadEenemy);
				SDL_DestroyTexture(textArrow);
				SDL_DestroyTexture(textBattle);
				SDL_DestroyTexture(textBat);
				SDL_DestroyTexture(textEnemyHealthTTF);
				SDL_DestroyTexture(textCharacter);
				SDL_DestroyTexture(textGoblin);
				SDL_DestroyTexture(textSlime);
				SDL_DestroyTexture(textWerewolf);
				SDL_DestroyTexture(textRat);
				TTF_CloseFont(enemyTTF);
				SDL_DestroyTexture(textIcons);
				livedEnemies = 0;
				reward(ren, Lose);
				return;
			}
			stepFight += 1;
			action += 1;

			SDL_DestroyTexture(textBat);
			SDL_DestroyTexture(textArrow);
			SDL_DestroyTexture(textBattle);
			SDL_DestroyTexture(textdeadEenemy);
			SDL_DestroyTexture(textEnemyHealthTTF);
			SDL_DestroyTexture(textAtk);
			SDL_DestroyTexture(textGoblin);
			SDL_DestroyTexture(textSlime);
			SDL_DestroyTexture(textWerewolf);
			SDL_DestroyTexture(textRat);
			SDL_DestroyTexture(textCharacter);
			SDL_DestroyTexture(textIcons);
			TTF_CloseFont(enemyTTF);
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
				SDL_SetRenderDrawColor(ren, 200, 200, 200, 0);
				SDL_RenderClear(ren);
				SDL_RenderCopy(ren, textBattle, NULL, NULL);
				SDL_RenderCopy(ren, textCharacter, &srcrectCharacter, &dstrectCharacter);
				if (enemy == Bat) {
					render_enemy(Bat, ren, textBat, textGoblin, textSlime, textWerewolf, textRat);
				}
				if (enemy == Goblin) {
					render_enemy(Goblin, ren, textBat, textGoblin, textSlime, textWerewolf, textRat);
				}
				if (enemy == Slime) {
					render_enemy(Slime, ren, textBat, textGoblin, textSlime, textWerewolf, textRat);
				}
				if (enemy == Werewolf) {
					render_enemy(Werewolf, ren, textBat, textGoblin, textSlime, textWerewolf, textRat);
				}
				if (enemy == Rat) {
					render_enemy(Rat, ren, textBat, textGoblin, textSlime, textWerewolf, textRat);
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
				flagPattern = 0;
				if (enemy == Bat)
					enemy_patterns(Bat);
				if (enemy == Goblin)
					enemy_patterns(Goblin);
				if (enemy == Slime)
					enemy_patterns(Slime);
				if (enemy == Werewolf)
					enemy_patterns(Werewolf);
				if (enemy == Rat)
					enemy_patterns(Rat);
				check_pattern(ren, textIcons);


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
				}
			}
			if (hitEnemy == 2 and enemy2.health > 0) {
				//SDL_Delay(200);
				enemy2.health = enemy2.health - hero.Attack;
				if (enemy2.health <= 0) {
					enemy2.atk = 0;
					livedEnemies -= 1;
					hero.Gold += enemy2.gold;
				}
			}
			if (hitEnemy == 3 and enemy3.health > 0) {
				//SDL_Delay(200);
				enemy3.health = enemy3.health - hero.Attack;
				if (enemy3.health <= 0) {
					enemy3.atk = 0;
					livedEnemies -= 1;
					hero.Gold += enemy3.gold;
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
					if (enemy == Bat) {
						render_enemy(Bat, ren, textBat, textGoblin, textSlime, textWerewolf, textRat);
					}
					if (enemy == Goblin) {
						render_enemy(Goblin, ren, textBat, textGoblin, textSlime, textWerewolf, textRat);
					}
					if (enemy == Slime) {
						render_enemy(Slime, ren, textBat, textGoblin, textSlime, textWerewolf, textRat);
					}
					if (enemy == Werewolf) {
						render_enemy(Werewolf, ren, textBat, textGoblin, textSlime, textWerewolf, textRat);
					}
					if (enemy == Rat) {
						render_enemy(Rat, ren, textBat, textGoblin, textSlime, textWerewolf, textRat);
					}
					SDL_RenderCopy(ren, textAtk, &srcrectAtk, &dstrectAtk);
					SDL_RenderPresent(ren);
					SDL_Delay(70);
				}
				if (frameFlag == 4) {
					animation = 0;
					frameFlag = 0;
				}
			}

			flagPattern = 1;
			if (enemy == Bat)
				enemy_patterns(Bat);
			if (enemy == Goblin)
				enemy_patterns(Goblin);
			if (enemy == Slime)
				enemy_patterns(Slime);
			if (enemy == Werewolf)
				enemy_patterns(Werewolf);
			if (enemy == Rat)
				enemy_patterns(Rat);
			if (hero.Health <= 0) {
				SDL_DestroyTexture(textdeadEenemy);
				SDL_DestroyTexture(textArrow);
				SDL_DestroyTexture(textBattle);
				SDL_DestroyTexture(textBat);
				SDL_DestroyTexture(textEnemyHealthTTF);
				SDL_DestroyTexture(textCharacter);
				SDL_DestroyTexture(textGoblin);
				SDL_DestroyTexture(textSlime);
				SDL_DestroyTexture(textWerewolf);
				SDL_DestroyTexture(textRat);
				TTF_CloseFont(enemyTTF);
				SDL_DestroyTexture(textIcons);
				livedEnemies = 0;
				reward(ren, Lose);
				return;
			}
			stepFight += 1;
			action += 1;

			SDL_DestroyTexture(textBat);
			SDL_DestroyTexture(textArrow);
			SDL_DestroyTexture(textBattle);
			SDL_DestroyTexture(textdeadEenemy);
			SDL_DestroyTexture(textEnemyHealthTTF);
			SDL_DestroyTexture(textAtk);
			SDL_DestroyTexture(textGoblin);
			SDL_DestroyTexture(textSlime);
			SDL_DestroyTexture(textWerewolf);
			SDL_DestroyTexture(textRat);
			SDL_DestroyTexture(textCharacter);
			SDL_DestroyTexture(textIcons);
			TTF_CloseFont(enemyTTF);
		}

	flag = 1;
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

void generateEnemy(int enemy) {
	if (enemy == Bat) {
		batCharacteristics.Health = 130; batCharacteristics.Attack = 35; batCharacteristics.Gold = 90; batCharacteristics.experienceEnemy = 130;
		if (curQuest == 1) {
			batCharacteristics.Health = 100; batCharacteristics.Attack = 20; batCharacteristics.Gold = 50; batCharacteristics.experienceEnemy = 100;
		}
		batCharacteristics.maxHealth = batCharacteristics.Health;
		enemy1.atk = batCharacteristics.Attack; enemy1.health = batCharacteristics.Health; enemy1.gold = batCharacteristics.Gold,
			enemy1.level = batCharacteristics.experienceEnemy, enemy1.isPoison = 0, enemy1.maxHealth = batCharacteristics.Health;
		enemy2.atk = batCharacteristics.Attack; enemy2.health = batCharacteristics.Health; enemy2.gold = batCharacteristics.Gold,
			enemy2.level = batCharacteristics.experienceEnemy, enemy2.isPoison = 0, enemy2.maxHealth = batCharacteristics.Health;
		enemy3.atk = batCharacteristics.Attack; enemy3.health = batCharacteristics.Health; enemy3.gold = batCharacteristics.Gold,
			enemy3.level = batCharacteristics.experienceEnemy, enemy3.isPoison = 0, enemy3.maxHealth = batCharacteristics.Health;
	}
	if (enemy == Goblin) {
		goblinCharacteristics.Health = 175; goblinCharacteristics.Attack = 50; goblinCharacteristics.Gold = 75; goblinCharacteristics.experienceEnemy = 175;
		goblinCharacteristics.maxHealth = goblinCharacteristics.Health;
		enemy1.atk = goblinCharacteristics.Attack; enemy1.health = goblinCharacteristics.Health; enemy1.gold = goblinCharacteristics.Gold,
			enemy1.level = goblinCharacteristics.experienceEnemy, enemy1.isPoison = 0, enemy1.maxHealth = goblinCharacteristics.Health;
		enemy2.atk = goblinCharacteristics.Attack; enemy2.health = goblinCharacteristics.Health; enemy2.gold = goblinCharacteristics.Gold,
			enemy2.level = goblinCharacteristics.experienceEnemy, enemy2.isPoison = 0, enemy2.maxHealth = goblinCharacteristics.Health;
		enemy3.atk = goblinCharacteristics.Attack; enemy3.health = goblinCharacteristics.Health; enemy3.gold = goblinCharacteristics.Gold,
			enemy3.level = goblinCharacteristics.experienceEnemy, enemy3.isPoison = 0, enemy3.maxHealth = goblinCharacteristics.Health;
	}
	if (enemy == Slime) {
		slimeCharacteristics.Health = 60; slimeCharacteristics.Attack = 0; slimeCharacteristics.Gold = 10; slimeCharacteristics.experienceEnemy = 20;
		slimeCharacteristics.maxHealth = slimeCharacteristics.Health;
		enemy1.atk = slimeCharacteristics.Attack; enemy1.health = slimeCharacteristics.Health; enemy1.gold = slimeCharacteristics.Gold,
			enemy1.level = slimeCharacteristics.experienceEnemy, enemy1.isPoison = 0, enemy1.maxHealth = slimeCharacteristics.Health;
		enemy2.atk = slimeCharacteristics.Attack; enemy2.health = slimeCharacteristics.Health; enemy2.gold = slimeCharacteristics.Gold,
			enemy2.level = slimeCharacteristics.experienceEnemy, enemy2.isPoison = 0, enemy2.maxHealth = slimeCharacteristics.Health;
		enemy3.atk = slimeCharacteristics.Attack; enemy3.health = slimeCharacteristics.Health; enemy3.gold = slimeCharacteristics.Gold,
			enemy3.level = slimeCharacteristics.experienceEnemy, enemy3.isPoison = 0, enemy3.maxHealth = slimeCharacteristics.Health;
	}
	if (enemy == Werewolf) {
		werewolfCharacteristics.Health = 150; werewolfCharacteristics.Attack = 40; werewolfCharacteristics.Gold = 80; werewolfCharacteristics.experienceEnemy = 150;
		werewolfCharacteristics.maxHealth = werewolfCharacteristics.Health;
		enemy1.atk = werewolfCharacteristics.Attack; enemy1.health = werewolfCharacteristics.Health; enemy1.gold = werewolfCharacteristics.Gold,
			enemy1.level = werewolfCharacteristics.experienceEnemy, enemy1.isPoison = 0, enemy1.maxHealth = werewolfCharacteristics.Health;
		enemy2.atk = werewolfCharacteristics.Attack; enemy2.health = werewolfCharacteristics.Health; enemy2.gold = werewolfCharacteristics.Gold,
			enemy2.level = werewolfCharacteristics.experienceEnemy, enemy2.isPoison = 0, enemy2.maxHealth = werewolfCharacteristics.Health;
		enemy3.atk = werewolfCharacteristics.Attack; enemy3.health = werewolfCharacteristics.Health; enemy3.gold = werewolfCharacteristics.Gold,
			enemy3.level = werewolfCharacteristics.experienceEnemy, enemy3.isPoison = 0, enemy3.maxHealth = werewolfCharacteristics.Health;
	}
	if (enemy == Rat) {
		ratCharacteristics.Health = 65; ratCharacteristics.Attack = 15; ratCharacteristics.Gold = 25; ratCharacteristics.experienceEnemy = 40;
		ratCharacteristics.maxHealth = ratCharacteristics.Health;
		enemy1.atk = ratCharacteristics.Attack; enemy1.health = ratCharacteristics.Health; enemy1.gold = ratCharacteristics.Gold,
			enemy1.level = ratCharacteristics.experienceEnemy, enemy1.isPoison = 0, enemy1.maxHealth = ratCharacteristics.Health;
		enemy2.atk = ratCharacteristics.Attack; enemy2.health = ratCharacteristics.Health; enemy2.gold = ratCharacteristics.Gold,
			enemy2.level = ratCharacteristics.experienceEnemy, enemy2.isPoison = 0, enemy2.maxHealth = ratCharacteristics.Health;
		enemy3.atk = ratCharacteristics.Attack; enemy3.health = ratCharacteristics.Health; enemy3.gold = ratCharacteristics.Gold,
			enemy3.level = ratCharacteristics.experienceEnemy, enemy3.isPoison = 0, enemy3.maxHealth = ratCharacteristics.Health;
	}
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

	if (abilityDamagePoison == 0) {
		enemy1.isPoison, enemy2.isPoison, enemy3.isPoison = false;
		abilityDamagePoison = poisonDamage;
	}
}

void enemy_patterns(int enemy) {
	if (enemy == Bat) {
		if (action == 3)
			action = 1;
		if (stepFight == 1 and action == 1) {
			curAction = AttackEnemy;
			nextAction = ShieldEnemy;
		}
		if (stepFight == 2 and action == 2) {
			curAction = ShieldEnemy;
			nextAction = AttackEnemy;
		}
		if (stepFight == 3)
			stepFight = 1;
		if (stepFight == 1 and flagPattern == 1) {//Attack
			if (amountEnemy == 2) {
				if (enemy1.health > 0)
					hero.Health -= (enemy1.atk - (enemy1.atk * hero.Defense));
				if (enemy2.health > 0)
					hero.Health -= (enemy2.atk - (enemy2.atk * hero.Defense));
			}
			if (amountEnemy == 3) {
				if (enemy1.health > 0)
					hero.Health -= (enemy1.atk - (enemy1.atk * hero.Defense));
				if (enemy2.health > 0)
					hero.Health -= (enemy2.atk - (enemy2.atk * hero.Defense));
				if (enemy3.health > 0)
					hero.Health -= (enemy3.atk - (enemy3.atk * hero.Defense));
			}
		}
		if (stepFight == 2 and flagPattern == 1) {//Shield
			if (amountEnemy == 2) {
				if (enemy1.health > 0)
					enemy1.health += 15;
				if (enemy2.health > 0)
					enemy2.health += 15;
			}
			if (amountEnemy == 3) {
				if (enemy1.health > 0)
					enemy1.health += 15;
				if (enemy2.health > 0)
					enemy2.health += 15;
				if (enemy3.health > 0)
					enemy3.health += 15;
			}
		}
	}
	if (enemy == Goblin) {
		if (stepFight == 4)
			stepFight = 1;
		if (action == 4)
			action = 1;
		if (stepFight == 1 and action == 1) {
			curAction = AttackEnemy;
			nextAction = AttackEnemy;
		}
		if (stepFight == 2 and action == 2) {
			curAction = AttackEnemy;
			nextAction = HealEnemy;
		}
		if (stepFight == 3 and action == 3) {
			curAction = HealEnemy;
			nextAction = AttackEnemy;
		}
		if (stepFight == 1 and flagPattern == 1) {//Attack
			
			if (amountEnemy == 2) {
				if (enemy1.health > 0)
					hero.Health -= (enemy1.atk - (enemy1.atk * hero.Defense));
				if (enemy2.health > 0)
					hero.Health -= (enemy2.atk - (enemy2.atk * hero.Defense));
			}
			if (amountEnemy == 3) {
				if (enemy1.health > 0)
					hero.Health -= (enemy1.atk - (enemy1.atk * hero.Defense));
				if (enemy2.health > 0)
					hero.Health -= (enemy2.atk - (enemy2.atk * hero.Defense));
				if (enemy3.health > 0)
					hero.Health -= (enemy3.atk - (enemy3.atk * hero.Defense));
			}
		}
		if (stepFight == 2 and flagPattern == 1) {//Attack
			
			if (amountEnemy == 2) {
				if (enemy1.health > 0)
					hero.Health -= (enemy1.atk - (enemy1.atk * hero.Defense));
				if (enemy2.health > 0)
					hero.Health -= (enemy2.atk - (enemy2.atk * hero.Defense));
			}
			if (amountEnemy == 3) {
				if (enemy1.health > 0)
					hero.Health -= (enemy1.atk - (enemy1.atk * hero.Defense));
				if (enemy2.health > 0)
					hero.Health -= (enemy2.atk - (enemy2.atk * hero.Defense));
				if (enemy3.health > 0)
					hero.Health -= (enemy3.atk - (enemy3.atk * hero.Defense));
			}
		}
		if (stepFight == 3 and flagPattern == 1) {//Heal
			
			if (amountEnemy == 2) {
				if (enemy1.health < enemy1.maxHealth and enemy1.health > 0)
					enemy1.health += 20;
				if (enemy2.health < enemy2.maxHealth and enemy2.health > 0)
					enemy2.health += 20;
			}
			if (amountEnemy == 3) {
				if (enemy1.health < enemy1.maxHealth and enemy1.health > 0)
					enemy1.health += 20;
				if (enemy2.health < enemy2.maxHealth and enemy2.health > 0)
					enemy2.health += 20;
				if (enemy3.health < enemy3.maxHealth and enemy3.health > 0)
					enemy3.health += 20;
			}
		}
	}
	if (enemy == Slime) {
		if (stepFight == 4)
			stepFight = 1;
		if (action == 4)
			action = 1;
		if (stepFight == 1 and action == 1) {
			curAction = ShieldEnemy;
			nextAction = ShieldEnemy;
		}
		if (stepFight == 2 and action == 2) {
			curAction = ShieldEnemy;
			nextAction = HealEnemy;
		}
		if (stepFight == 3 and action == 3) {
			curAction = HealEnemy;
			nextAction = ShieldEnemy;
		}
		if (stepFight == 1 and flagPattern == 1) {//Shield
			
			if (amountEnemy == 2) {
				if (enemy1.health > 0)
					enemy1.health += 20;
				if (enemy2.health > 0)
					enemy2.health += 20;
			}
			if (amountEnemy == 3) {
				if (enemy1.health > 0)
					enemy1.health += 20;
				if (enemy2.health > 0)
					enemy2.health += 20;
				if (enemy3.health > 0)
					enemy3.health += 20;
			}
		}
		if (stepFight == 2 and flagPattern == 1) {//Shield
			
			if (amountEnemy == 2) {
				if (enemy1.health > 0)
					enemy1.health += 40;
				if (enemy2.health > 0)
					enemy2.health += 40;
			}
			if (amountEnemy == 3) {
				if (enemy1.health > 0)
					enemy1.health += 40;
				if (enemy2.health > 0)
					enemy2.health += 40;
				if (enemy3.health > 0)
					enemy3.health += 40;
			}
		}
		if (stepFight == 3 and flagPattern == 1) {//Heal
			
			if (amountEnemy == 2) {
				if (enemy1.health > 0 and enemy1.health < enemy1.maxHealth)
					enemy1.health = enemy1.maxHealth;
				if (enemy2.health > 0 and enemy2.health < enemy2.maxHealth)
					enemy2.health = enemy2.maxHealth;
			}
			if (amountEnemy == 3) {
				if (enemy1.health > 0 and enemy1.health < enemy1.maxHealth)
					enemy1.health = enemy1.maxHealth;
				if (enemy2.health > 0 and enemy2.health < enemy2.maxHealth)
					enemy2.health = enemy2.maxHealth;
				if (enemy3.health > 0 and enemy3.health < enemy3.maxHealth)
					enemy3.health = enemy3.maxHealth;
			}
		}
	}
	if (enemy == Werewolf) {
		if (stepFight == 4)
			stepFight = 1;
		if (action == 4)
			action = 1;
		if (stepFight == 1 and action == 1) {
			curAction = AttackEnemy;
			nextAction = VampirismEnemy;
		}
		if (stepFight == 2 and action == 2) {
			curAction = VampirismEnemy;
			nextAction = ShieldEnemy;
		}
		if (stepFight == 3 and action == 3) {
			curAction = ShieldEnemy;
			nextAction = AttackEnemy;
		}
		if (stepFight == 1 and flagPattern == 1) {//Attack
			if (amountEnemy == 2) {
				if (enemy1.health > 0)
					hero.Health -= (enemy1.atk - (enemy1.atk * hero.Defense));
				if (enemy2.health > 0)
					hero.Health -= (enemy2.atk - (enemy2.atk * hero.Defense));
			}
			if (amountEnemy == 3) {
				if (enemy1.health > 0)
					hero.Health -= (enemy1.atk - (enemy1.atk * hero.Defense));
				if (enemy2.health > 0)
					hero.Health -= (enemy2.atk - (enemy2.atk * hero.Defense));
				if (enemy3.health > 0)
					hero.Health -= (enemy3.atk - (enemy3.atk * hero.Defense));
			}
		}
		if (stepFight == 2 and flagPattern == 1) {//Vampirism
			if (amountEnemy == 2) {
				if (enemy1.health > 0) {
					hero.Health -= (enemy1.atk - (enemy1.atk * hero.Defense));
					enemy1.health += (enemy1.atk - (enemy1.atk * hero.Defense));
				}
				if (enemy2.health > 0) {
					hero.Health -= (enemy2.atk - (enemy2.atk * hero.Defense));
					enemy2.health += (enemy2.atk - (enemy2.atk * hero.Defense));
				}
			}
			if (amountEnemy == 3) {
				if (enemy1.health > 0) {
					hero.Health -= (enemy1.atk - (enemy1.atk * hero.Defense));
					enemy1.health += (enemy1.atk - (enemy1.atk * hero.Defense));
				}
				if (enemy2.health > 0) {
					hero.Health -= (enemy2.atk - (enemy2.atk * hero.Defense));
					enemy2.health += (enemy2.atk - (enemy2.atk * hero.Defense));
				}
				if (enemy3.health > 0) {
					hero.Health -= (enemy3.atk - (enemy3.atk * hero.Defense));
					enemy3.health += (enemy3.atk - (enemy3.atk * hero.Defense));
				}
			}
		}
		if (stepFight == 3 and flagPattern == 1) {//Shield
			if (amountEnemy == 2) {
				if (enemy1.health > 0)
					enemy1.health += 25;
				if (enemy2.health > 0)
					enemy2.health += 25;
			}
			if (amountEnemy == 3) {
				if (enemy1.health > 0)
					enemy1.health += 25;
				if (enemy2.health > 0)
					enemy2.health += 25;
				if (enemy3.health > 0)
					enemy3.health += 25;
			}
		}
	}
	if (enemy == Rat) {
		if (stepFight == 4)
			stepFight = 1;
		if (action == 4)
			action = 1;
		if (stepFight == 1 and action == 1) {
			curAction = AttackEnemy;
			nextAction = AttackEnemy;
		}
		if (stepFight == 2 and action == 2) {
			curAction = AttackEnemy;
			nextAction = CritEnemy;
		}
		if (stepFight == 3 and action == 3) {
			curAction = CritEnemy;
			nextAction = AttackEnemy;
		}
		if (stepFight == 1 and flagPattern == 1) {//Attack
			if (amountEnemy == 2) {
				if (enemy1.health > 0)
					hero.Health -= (enemy1.atk - (enemy1.atk * hero.Defense));
				if (enemy2.health > 0)
					hero.Health -= (enemy2.atk - (enemy2.atk * hero.Defense));
			}
			if (amountEnemy == 3) {
				if (enemy1.health > 0)
					hero.Health -= (enemy1.atk - (enemy1.atk * hero.Defense));
				if (enemy2.health > 0)
					hero.Health -= (enemy2.atk - (enemy2.atk * hero.Defense));
				if (enemy3.health > 0)
					hero.Health -= (enemy3.atk - (enemy3.atk * hero.Defense));
			}
		}
		if (stepFight == 2 and flagPattern == 1) {//Attack
			if (amountEnemy == 2) {
				if (enemy1.health > 0)
					hero.Health -= (enemy1.atk - (enemy1.atk * hero.Defense));
				if (enemy2.health > 0)
					hero.Health -= (enemy2.atk - (enemy2.atk * hero.Defense));
			}
			if (amountEnemy == 3) {
				if (enemy1.health > 0)
					hero.Health -= (enemy1.atk - (enemy1.atk * hero.Defense));
				if (enemy2.health > 0)
					hero.Health -= (enemy2.atk - (enemy2.atk * hero.Defense));
				if (enemy3.health > 0)
					hero.Health -= (enemy3.atk - (enemy3.atk * hero.Defense));
			}
		}
		if (stepFight == 3 and flagPattern == 1) {//Crit (Double Damage)
			if (amountEnemy == 2) {
				if (enemy1.health > 0)
					hero.Health -= ((enemy1.atk - (enemy1.atk * hero.Defense)) * 2);
				if (enemy2.health > 0)
					hero.Health -= ((enemy2.atk - (enemy2.atk * hero.Defense)) * 2);
			}
			if (amountEnemy == 3) {
				if (enemy1.health > 0)
					hero.Health -= ((enemy1.atk - (enemy1.atk * hero.Defense)) * 2);
				if (enemy2.health > 0)
					hero.Health -= ((enemy2.atk - (enemy2.atk * hero.Defense)) * 2);
				if (enemy3.health > 0)
					hero.Health -= ((enemy3.atk - (enemy3.atk * hero.Defense)) * 2);
			}
		}
	}
}


void render_enemy(int enemy, SDL_Renderer* ren, SDL_Texture* textBat, SDL_Texture* textGoblin, SDL_Texture* textSlime, SDL_Texture* textWerewolf, SDL_Texture* textRat){
	if (amountEnemy == 2) {
		dstrect = { xEnemy1, yEnemy1, 75, 75 };
		dstrect2 = { xEnemy2, yEnemy2, 75, 75 };
		if (enemy == Bat) {
			SDL_RenderCopy(ren, textBat, &srcrectBat, &dstrect);
			SDL_RenderCopy(ren, textBat, &srcrectBat, &dstrect2);
		}
		if (enemy == Goblin) {
			SDL_RenderCopy(ren, textGoblin, &srcrectGoblin, &dstrect);
			SDL_RenderCopy(ren, textGoblin, &srcrectGoblin, &dstrect2);
		}
		if (enemy == Slime) {
			SDL_RenderCopy(ren, textSlime, NULL, &dstrect);
			SDL_RenderCopy(ren, textSlime, NULL, &dstrect2);
		}
		if (enemy == Werewolf) {
			SDL_RenderCopy(ren, textWerewolf, &srcrectWerewolf, &dstrect);
			SDL_RenderCopy(ren, textWerewolf, &srcrectWerewolf, &dstrect2);
		}
		if (enemy == Rat) {
			SDL_RenderCopy(ren, textRat, &srcRat, &dstrect);
			SDL_RenderCopy(ren, textRat, &srcRat, &dstrect2);
		}
	}
	if (amountEnemy == 3) {
		dstrect = { xEnemy1, yEnemy1, 75, 75 };
		dstrect2 = { xEnemy2, yEnemy2, 75, 75 };
		dstrect3 = { xEnemy3, yEnemy3, 75, 75 };
		if (enemy == Bat) {
			SDL_RenderCopy(ren, textBat, &srcrectBat, &dstrect);
			SDL_RenderCopy(ren, textBat, &srcrectBat, &dstrect2);
			SDL_RenderCopy(ren, textBat, &srcrectBat, &dstrect3);
		}
		if (enemy == Goblin) {
			SDL_RenderCopy(ren, textGoblin, &srcrectGoblin, &dstrect);
			SDL_RenderCopy(ren, textGoblin, &srcrectGoblin, &dstrect2);
			SDL_RenderCopy(ren, textGoblin, &srcrectGoblin, &dstrect3);
		}
		if (enemy == Slime) {
			SDL_RenderCopy(ren, textSlime, NULL, &dstrect);
			SDL_RenderCopy(ren, textSlime, NULL, &dstrect2);
			SDL_RenderCopy(ren, textSlime, NULL, &dstrect3);
		}
		if (enemy == Werewolf) {
			SDL_RenderCopy(ren, textWerewolf, &srcrectWerewolf, &dstrect);
			SDL_RenderCopy(ren, textWerewolf, &srcrectWerewolf, &dstrect2);
			SDL_RenderCopy(ren, textWerewolf, &srcrectWerewolf, &dstrect3);
		}
		if (enemy == Rat) {
			SDL_RenderCopy(ren, textRat, &srcRat, &dstrect);
			SDL_RenderCopy(ren, textRat, &srcRat, &dstrect2);
			SDL_RenderCopy(ren, textRat, &srcRat, &dstrect3);
		}
	}
}

void check_pattern(SDL_Renderer* ren, SDL_Texture* textIcons) {
	if (enemy1.health > 0) {
		positionIcon.x = 500, positionIcon.y = 175;
		if (curAction == AttackEnemy)
			SDL_RenderCopy(ren, textIcons, &AtkIcon, &positionIcon);
		if (curAction == HealEnemy)
			SDL_RenderCopy(ren, textIcons, &HealIcon, &positionIcon);
		if (curAction == ShieldEnemy)
			SDL_RenderCopy(ren, textIcons, &ShieldIcon, &positionIcon);
		if (curAction == VampirismEnemy)
			SDL_RenderCopy(ren, textIcons, &VampirismIcon, &positionIcon);
		if (curAction == CritEnemy)
			SDL_RenderCopy(ren, textIcons, &CritIcon, &positionIcon);

		positionIcon.x = 580;
		if (nextAction == AttackEnemy)
			SDL_RenderCopy(ren, textIcons, &AtkIcon, &positionIcon);
		if (nextAction == HealEnemy)
			SDL_RenderCopy(ren, textIcons, &HealIcon, &positionIcon);
		if (nextAction == ShieldEnemy)
			SDL_RenderCopy(ren, textIcons, &ShieldIcon, &positionIcon);
		if (nextAction == VampirismEnemy)
			SDL_RenderCopy(ren, textIcons, &VampirismIcon, &positionIcon);
		if (nextAction == CritEnemy)
			SDL_RenderCopy(ren, textIcons, &CritIcon, &positionIcon);
	}
	if (enemy2.health > 0) {
		positionIcon.x = 700, positionIcon.y = 175;
		if (curAction == AttackEnemy)
			SDL_RenderCopy(ren, textIcons, &AtkIcon, &positionIcon);
		if (curAction == HealEnemy)
			SDL_RenderCopy(ren, textIcons, &HealIcon, &positionIcon);
		if (curAction == ShieldEnemy)
			SDL_RenderCopy(ren, textIcons, &ShieldIcon, &positionIcon);
		if (curAction == VampirismEnemy)
			SDL_RenderCopy(ren, textIcons, &VampirismIcon, &positionIcon);
		if (curAction == CritEnemy)
			SDL_RenderCopy(ren, textIcons, &CritIcon, &positionIcon);

		positionIcon.x = 780;
		if (nextAction == AttackEnemy)
			SDL_RenderCopy(ren, textIcons, &AtkIcon, &positionIcon);
		if (nextAction == HealEnemy)
			SDL_RenderCopy(ren, textIcons, &HealIcon, &positionIcon);
		if (nextAction == ShieldEnemy)
			SDL_RenderCopy(ren, textIcons, &ShieldIcon, &positionIcon);
		if (nextAction == VampirismEnemy)
			SDL_RenderCopy(ren, textIcons, &VampirismIcon, &positionIcon);
		if (nextAction == CritEnemy)
			SDL_RenderCopy(ren, textIcons, &CritIcon, &positionIcon);
	}
	if (amountEnemy == 3) {
		if (enemy3.health > 0) {
			positionIcon.x = 900, positionIcon.y = 175;
			if (curAction == AttackEnemy)
				SDL_RenderCopy(ren, textIcons, &AtkIcon, &positionIcon);
			if (curAction == HealEnemy)
				SDL_RenderCopy(ren, textIcons, &HealIcon, &positionIcon);
			if (curAction == ShieldEnemy)
				SDL_RenderCopy(ren, textIcons, &ShieldIcon, &positionIcon);
			if (curAction == VampirismEnemy)
				SDL_RenderCopy(ren, textIcons, &VampirismIcon, &positionIcon);
			if (curAction == CritEnemy)
				SDL_RenderCopy(ren, textIcons, &CritIcon, &positionIcon);

			positionIcon.x = 980;
			if (nextAction == AttackEnemy)
				SDL_RenderCopy(ren, textIcons, &AtkIcon, &positionIcon);
			if (nextAction == HealEnemy)
				SDL_RenderCopy(ren, textIcons, &HealIcon, &positionIcon);
			if (nextAction == ShieldEnemy)
				SDL_RenderCopy(ren, textIcons, &ShieldIcon, &positionIcon);
			if (nextAction == VampirismEnemy)
				SDL_RenderCopy(ren, textIcons, &VampirismIcon, &positionIcon);
			if (nextAction == CritEnemy)
				SDL_RenderCopy(ren, textIcons, &CritIcon, &positionIcon);
		}
	}
}

void render_dead_enemy(SDL_Renderer* ren, SDL_Texture* textdeadEenemy) {
	if (enemy1.health <= 0) {
		dstrectDeadEnemy1 = { xDeadEnemy1, yDeadEnemy1, 75, 75 };
		SDL_RenderCopy(ren, textdeadEenemy, &srcrectDeadEnemy, &dstrectDeadEnemy1);
	}
	if (enemy2.health <= 0) {
		dstrectDeadEnemy2 = { xDeadEnemy2, yDeadEnemy2, 75, 75 };
		SDL_RenderCopy(ren, textdeadEenemy, &srcrectDeadEnemy, &dstrectDeadEnemy2);
	}
	if (amountEnemy == 3) {
		if (enemy3.health <= 0) {
			dstrectDeadEnemy3 = { xDeadEnemy3, yDeadEnemy3, 75, 75 };
			SDL_RenderCopy(ren, textdeadEenemy, &srcrectDeadEnemy, &dstrectDeadEnemy3);
		}
	}
}

void reward(SDL_Renderer* ren, int Reward) {
	//Texture
	SDL_Surface* surfReward = IMG_Load("sprites\\menu\\reward.png");
	SDL_Texture* textReward = SDL_CreateTextureFromSurface(ren, surfReward);
	SDL_FreeSurface(surfReward);

	TTF_Font* rewardFont = TTF_OpenFont("fonts\\Ubuntu-Regular.ttf", 75);
	char rewardStr[100] = "parameters";
	SDL_Surface* surfRewardTTF = TTF_RenderText_Blended(rewardFont, rewardStr, { 255, 255, 255, 255 });
	SDL_Texture* textRewardTTF = SDL_CreateTextureFromSurface(ren, surfRewardTTF);
	SDL_Rect size = { 0, 0, surfRewardTTF->w, surfRewardTTF->h };
	int xPoint = 100, yPoint = 50;
	SDL_Rect statsRect = { xPoint, yPoint, 55, 60 };
	SDL_FreeSurface(surfRewardTTF);

	SDL_Event ev;
	SDL_PollEvent(&ev);
	const Uint8* state = SDL_GetKeyboardState(NULL);

	while (true) {

		SDL_SetRenderDrawColor(ren, 200, 200, 200, 0);
		SDL_RenderClear(ren);
		SDL_RenderCopy(ren, textReward, NULL, NULL);

		if (Reward == 1) {
			xPoint = 460, yPoint = 200;
			statsRect = { xPoint, yPoint, 320, 60 };
			sprintf_s(rewardStr, "Experience 0");
			surfRewardTTF = TTF_RenderText_Blended(rewardFont, rewardStr, { 255, 255, 255, 255 });
			size = { 0, 0, surfRewardTTF->w, surfRewardTTF->h };
			textRewardTTF = SDL_CreateTextureFromSurface(ren, surfRewardTTF);
			SDL_RenderCopy(ren, textRewardTTF, &size, &statsRect);
			SDL_FreeSurface(surfRewardTTF);
			SDL_DestroyTexture(textRewardTTF);

			xPoint = 460, yPoint = 280;
			statsRect = { xPoint, yPoint, 200, 60 };
			sprintf_s(rewardStr, "Gold 0");
			surfRewardTTF = TTF_RenderText_Blended(rewardFont, rewardStr, { 255, 255, 255, 255 });
			size = { 0, 0, surfRewardTTF->w, surfRewardTTF->h };
			textRewardTTF = SDL_CreateTextureFromSurface(ren, surfRewardTTF);
			SDL_RenderCopy(ren, textRewardTTF, &size, &statsRect);
			SDL_FreeSurface(surfRewardTTF);
			SDL_DestroyTexture(textRewardTTF);
		}
		if (amountEnemy == 2 and Reward == 0) {
			xPoint = 460, yPoint = 200;
			statsRect = { xPoint, yPoint, 320, 60 };
			sprintf_s(rewardStr, "Experience %d", enemy1.level + enemy2.level);
			surfRewardTTF = TTF_RenderText_Blended(rewardFont, rewardStr, { 255, 255, 255, 255 });
			size = { 0, 0, surfRewardTTF->w, surfRewardTTF->h };
			textRewardTTF = SDL_CreateTextureFromSurface(ren, surfRewardTTF);
			SDL_RenderCopy(ren, textRewardTTF, &size, &statsRect);
			SDL_FreeSurface(surfRewardTTF);
			SDL_DestroyTexture(textRewardTTF);

			xPoint = 460, yPoint = 280;
			statsRect = { xPoint, yPoint, 200, 60 };
			sprintf_s(rewardStr, "Gold %d", enemy1.gold + enemy2.gold);
			surfRewardTTF = TTF_RenderText_Blended(rewardFont, rewardStr, { 255, 255, 255, 255 });
			size = { 0, 0, surfRewardTTF->w, surfRewardTTF->h };
			textRewardTTF = SDL_CreateTextureFromSurface(ren, surfRewardTTF);
			SDL_RenderCopy(ren, textRewardTTF, &size, &statsRect);
			SDL_FreeSurface(surfRewardTTF);
			SDL_DestroyTexture(textRewardTTF);
		}
		if (amountEnemy == 3 and Reward == 0) {
			xPoint = 460, yPoint = 200;
			statsRect = { xPoint, yPoint, 320, 60 };
			sprintf_s(rewardStr, "Experience %d", enemy1.level + enemy2.level + enemy3.level);
			surfRewardTTF = TTF_RenderText_Blended(rewardFont, rewardStr, { 255, 255, 255, 255 });
			size = { 0, 0, surfRewardTTF->w, surfRewardTTF->h };
			textRewardTTF = SDL_CreateTextureFromSurface(ren, surfRewardTTF);
			SDL_RenderCopy(ren, textRewardTTF, &size, &statsRect);
			SDL_FreeSurface(surfRewardTTF);
			SDL_DestroyTexture(textRewardTTF);

			xPoint = 460, yPoint = 280;
			statsRect = { xPoint, yPoint, 200, 60 };
			sprintf_s(rewardStr, "Gold %d", enemy1.gold + enemy2.gold + enemy3.gold);
			surfRewardTTF = TTF_RenderText_Blended(rewardFont, rewardStr, { 255, 255, 255, 255 });
			size = { 0, 0, surfRewardTTF->w, surfRewardTTF->h };
			textRewardTTF = SDL_CreateTextureFromSurface(ren, surfRewardTTF);
			SDL_RenderCopy(ren, textRewardTTF, &size, &statsRect);
			SDL_FreeSurface(surfRewardTTF);
			SDL_DestroyTexture(textRewardTTF);
		}

		while (SDL_PollEvent(&ev) != NULL) {
			SDL_PollEvent(&ev);

			if (state[SDL_SCANCODE_RETURN]) {
				SDL_DestroyTexture(textReward);
				SDL_DestroyTexture(textRewardTTF);
				TTF_CloseFont(rewardFont);
				return;
			}
		}

		SDL_RenderPresent(ren);
		SDL_Delay(20);
	}
}