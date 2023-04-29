#define ATTACK 1
#define HEALTH 2
#define PROTECTION 3
#define ABILITYATTACK 4
#define EXIT 5
#include "Models.h"
#include "Ability.h"
#include <stdio.h>
#include <stdlib.h>
#include <SDL.h>
#include <SDL_image.h>


void level_up() {

	if ((hero.experience >= hero.levelUp) and (hero.level <= hero.maxLevel)) {
		hero.level += 1;
		hero.pointsLevel += 4;
		hero.experience = 0;
		hero.levelUp = hero.levelUp * 1.5;
		system("cls");
		printf("Level up\n");
	}
	if (hero.level % 3 == 0) {
		hero.pointsTree += 1;
		printf("pointsTree %d\n", hero.pointsTree);
	}
	if (hero.level % 10 == 0) {
		hero.pointsTree += 2;
		printf("pointsTree %d\n", hero.pointsTree);
	}
}

void character_leveling(SDL_Renderer* ren) {
	#pragma region Texture
	//Level up
	SDL_Surface* surfLevelUp = IMG_Load("sprites\\menu\\levelup.png");
	if (surfLevelUp == NULL) {
		printf("couldn't load level up\n");
	}
	else printf("level up load\n");
	SDL_Texture* textLevelUp = SDL_CreateTextureFromSurface(ren, surfLevelUp);
	SDL_FreeSurface(surfLevelUp);
	//Arrow
	SDL_Surface* surfArrow = IMG_Load("sprites\\menu\\arrow.png");
	if (surfArrow == NULL) {
		printf("couldn't load arrow\n");
	}
	else printf("arrow load\n");
	SDL_Texture* textArrow = SDL_CreateTextureFromSurface(ren, surfArrow);
	SDL_FreeSurface(surfArrow);
#pragma endregion
	int xArrow = 280, yArrow = 142;
	int pointer = 1;
	const Uint8* arrowState = SDL_GetKeyboardState(NULL);
	SDL_Rect srcrectArrow = { 0, 0, 100, 140 };
	SDL_Rect dstrectArrow;
	int choicheParameter = 0;
	SDL_Event ev;
	SDL_PollEvent(&ev);
	printf("Select devepmoment option\n");
	printf("Points %d\n", hero.pointsLevel);
	printf("1 - Attack\n2 - Health\n3 - Protection\n4 - AbilityAtack\nESC - EXIT\n");
	while (choicheParameter == 0) {
		dstrectArrow = { xArrow, yArrow, 75, 75 };
		while (SDL_PollEvent(&ev) != NULL) {
			switch (ev.type) {
			case SDL_KEYDOWN:
				switch (ev.key.keysym.scancode) {
				case SDL_SCANCODE_ESCAPE:
					choicheParameter = EXIT;
					break;
				case SDL_SCANCODE_UP:
					if (pointer != 1) {
						yArrow -= 95;
						pointer--;
					}
					break;
				case SDL_SCANCODE_W:
					if (pointer != 1) {
						yArrow -= 95;
						pointer--;
					}
					break;
				case SDL_SCANCODE_DOWN:
					if (pointer != 5) {
						yArrow += 95;
						pointer++;
					}
					break;
				case SDL_SCANCODE_S:
					if (pointer != 5) {
						yArrow += 95;
						pointer++;
					}
					break;
				}
			}

			SDL_SetRenderDrawColor(ren, 200, 200, 200, 0);
			SDL_RenderClear(ren);
			SDL_RenderCopy(ren, textLevelUp, NULL, NULL);
			SDL_RenderCopy(ren, textArrow, &srcrectArrow, &dstrectArrow);
			SDL_RenderPresent(ren);
			SDL_Delay(3);

		}

		if (pointer == 1 and arrowState[SDL_SCANCODE_RETURN]) choicheParameter = ATTACK;
		if (pointer == 2 and arrowState[SDL_SCANCODE_RETURN]) choicheParameter = HEALTH;
		if (pointer == 3 and arrowState[SDL_SCANCODE_RETURN]) choicheParameter = PROTECTION;
		if (pointer == 4 and arrowState[SDL_SCANCODE_RETURN]) choicheParameter = ABILITYATTACK;
		if (pointer == 5 and arrowState[SDL_SCANCODE_RETURN]) choicheParameter = EXIT;

	}

	SDL_DestroyTexture(textLevelUp);
	SDL_DestroyTexture(textArrow);

	if (choicheParameter == EXIT) {
		system("cls");
		return;
	}
	if (hero.pointsLevel == 0) {
		system("cls");
		printf("You don't have points\n");
	}
	if (choicheParameter == ATTACK and hero.pointsLevel != 0) {
		hero.Attack = hero.Attack * 1.4;
		hero.maxAttack = hero.Attack * 1.4;
		system("cls");
		printf("Attack %d\n", hero.Attack);
		hero.pointsLevel--;
	}
	if (choicheParameter == HEALTH and hero.pointsLevel != 0) {
		hero.Health = hero.Health * 1.15;
		hero.maxHealth = hero.Health * 1.15;
		system("cls");
		printf("Health %d\n", hero.Health);
		hero.pointsLevel--;
	}
	if (choicheParameter == PROTECTION and hero.pointsLevel != 0) {
		hero.Defense = hero.Defense * 2;
		system("cls");
		printf("Defense %d\n", hero.Defense);
		hero.pointsLevel--;
	}
	if (choicheParameter == ABILITYATTACK and hero.pointsLevel != 0) {
		hero.Mana = hero.Mana * 1.3;
		hero.maxMana = hero.Mana * 1.3;
		abilityDamageFireball *= 1.3;
		abilityDamageLighting *= 1.2;
		abilityDamagePosion *= 1.2;
		system("cls");
		printf("Mana %d\n", hero.Mana);
		printf("abilityDamageFireball %d\n", abilityDamageFireball);
		printf("abilityDamageLighting %d\n", abilityDamageLighting);
		printf("abilityDamagePosion %d\n", abilityDamagePosion);
		hero.pointsLevel--;
	}
}

void skill_tree() {
	if (hero.pointsTree > 0) {
		hero.pointsTree--;
	}
	else printf("you don't have skill tree points\n");
}
