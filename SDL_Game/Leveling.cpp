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
#include <SDL_ttf.h>


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
	SDL_Texture* textLevelUp = SDL_CreateTextureFromSurface(ren, surfLevelUp);
	SDL_FreeSurface(surfLevelUp);
	//Arrow
	SDL_Surface* surfArrow = IMG_Load("sprites\\menu\\arrow.png");
	SDL_Texture* textArrow = SDL_CreateTextureFromSurface(ren, surfArrow);
	SDL_FreeSurface(surfArrow);
	//
	TTF_Font* heroPointTTF = TTF_OpenFont("fonts\\BAUHS93.TTF", 75);
	char heroPoints[100] = "Points";
	SDL_Surface* surftHeroPointTTF = TTF_RenderText_Blended(heroPointTTF, heroPoints, {255, 255, 255, 255});
	SDL_Texture* textHeroPointTTF = SDL_CreateTextureFromSurface(ren, surftHeroPointTTF);
	SDL_Rect size = {0, 0, surftHeroPointTTF->w, surftHeroPointTTF->h};
#pragma endregion
	int xArrow = 370, yArrow = 175;
	int xPoint = 1100, yPoint = 20;
	SDL_Rect pointsTTF = { xPoint, yPoint, 55, 60 };
	int pointer = 1;
	const Uint8* arrowState = SDL_GetKeyboardState(NULL);
	SDL_Rect srcrectArrow = { 0, 0, 100, 140 };
	SDL_Rect dstrectArrow;
	int choicheParameter = 0;
	SDL_Event ev;
	printf("Points %d\n", hero.pointsLevel);
	while (choicheParameter == 0) {
		SDL_PollEvent(&ev);
		dstrectArrow = { xArrow, yArrow, 75, 75 };

		sprintf_s(heroPoints, "%d", hero.pointsLevel);
		surftHeroPointTTF = TTF_RenderText_Blended(heroPointTTF, heroPoints, { 255, 255, 255, 255 });
		size = { 0, 0, surftHeroPointTTF->w, surftHeroPointTTF->h };
		textHeroPointTTF = SDL_CreateTextureFromSurface(ren, surftHeroPointTTF);

		SDL_SetRenderDrawColor(ren, 200, 200, 200, 0);
		SDL_RenderClear(ren);
		SDL_RenderCopy(ren, textLevelUp, NULL, NULL);
		SDL_RenderCopy(ren, textHeroPointTTF, &size, &pointsTTF);
		SDL_RenderCopy(ren, textArrow, &srcrectArrow, &dstrectArrow);
		SDL_RenderPresent(ren);
		SDL_Delay(7);
		SDL_FreeSurface(surftHeroPointTTF);

		while (SDL_PollEvent(&ev) != NULL) {
			switch (ev.type) {
			case SDL_KEYDOWN:
				switch (ev.key.keysym.scancode) {
				case SDL_SCANCODE_ESCAPE:
					choicheParameter = EXIT;
					break;
				case SDL_SCANCODE_UP:
					if (pointer != 1) {
						yArrow -= 112;
						pointer--;
					}
					break;
				case SDL_SCANCODE_W:
					if (pointer != 1) {
						yArrow -= 112;
						pointer--;
					}
					break;
				case SDL_SCANCODE_DOWN:
					if (pointer != 5) {
						yArrow += 112;
						pointer++;
					}
					break;
				case SDL_SCANCODE_S:
					if (pointer != 5) {
						yArrow += 112;
						pointer++;
					}
					break;
				}
			}

		}

		if (pointer == 1 and arrowState[SDL_SCANCODE_RETURN]) choicheParameter = ATTACK;
		if (pointer == 2 and arrowState[SDL_SCANCODE_RETURN]) choicheParameter = HEALTH;
		if (pointer == 3 and arrowState[SDL_SCANCODE_RETURN]) choicheParameter = PROTECTION;
		if (pointer == 4 and arrowState[SDL_SCANCODE_RETURN]) choicheParameter = ABILITYATTACK;
		if (pointer == 5 and arrowState[SDL_SCANCODE_RETURN]) choicheParameter = EXIT;

		SDL_DestroyTexture(textHeroPointTTF);
	}

	SDL_DestroyTexture(textLevelUp);
	SDL_DestroyTexture(textArrow);
	TTF_CloseFont(heroPointTTF);
	SDL_DestroyTexture(textHeroPointTTF);

	if (choicheParameter == EXIT) {
		system("cls");
		return;
	}
	if (hero.pointsLevel == 0) {
		system("cls");
		printf("You don't have points\n");
	}


	int xStats = 700, yStats = 165;
	TTF_Font* heroAtk = TTF_OpenFont("fonts\\BAUHS93.TTF", 75);
	char strheroAtk[100] = "Atk";
	SDL_Surface* surftHeroAtk = TTF_RenderText_Blended(heroAtk, strheroAtk, { 255, 255, 255, 255 });
	SDL_Texture* textHeroAtk = SDL_CreateTextureFromSurface(ren, surftHeroAtk);
	SDL_Rect statsTTF = { xStats, yStats, 280, 105 };

	if (choicheParameter == ATTACK and hero.pointsLevel != 0) {
		hero.Attack = hero.Attack * 1.1;
		hero.maxAttack = hero.Attack * 1.1;
		system("cls");
		printf("Attack %d\n", hero.Attack);
		sprintf_s(strheroAtk, "Attack %d", hero.Attack);
		surftHeroAtk = TTF_RenderText_Blended(heroAtk, strheroAtk, { 255, 255, 255, 255 });
		size = { 0, 0, surftHeroAtk->w, surftHeroAtk->h };
		textHeroAtk = SDL_CreateTextureFromSurface(ren, surftHeroAtk);
		SDL_RenderCopy(ren, textHeroAtk, &size, &statsTTF);
		SDL_RenderPresent(ren);
		SDL_Delay(500);
		hero.pointsLevel--;
	}
	if (choicheParameter == HEALTH and hero.pointsLevel != 0) {
		hero.Health = hero.Health * 1.15;
		hero.maxHealth = hero.Health * 1.15;
		system("cls");
		printf("Health %d\n", hero.maxHealth);
		sprintf_s(strheroAtk, "Health %d", hero.maxHealth);
		xStats = 700, yStats = 275;
		statsTTF = { xStats, yStats, 280, 105 };
		surftHeroAtk = TTF_RenderText_Blended(heroAtk, strheroAtk, { 255, 255, 255, 255 });
		size = { 0, 0, surftHeroAtk->w, surftHeroAtk->h };
		textHeroAtk = SDL_CreateTextureFromSurface(ren, surftHeroAtk);
		SDL_RenderCopy(ren, textHeroAtk, &size, &statsTTF);
		SDL_RenderPresent(ren);
		SDL_Delay(500);
		hero.pointsLevel--;
	}
	if (choicheParameter == PROTECTION and hero.pointsLevel != 0) {
		if (hero.Defense >= 0.85) {
			printf("Defense max\n");
			return;
		}
		hero.Defense = hero.Defense + 0.05;
		system("cls");
		printf("Defense %.2f\n", hero.Defense);
		sprintf_s(strheroAtk, "Defense %.2f", hero.Defense);
		xStats = 700, yStats = 385;
		statsTTF = { xStats, yStats, 280, 105 };
		surftHeroAtk = TTF_RenderText_Blended(heroAtk, strheroAtk, { 255, 255, 255, 255 });
		size = { 0, 0, surftHeroAtk->w, surftHeroAtk->h };
		textHeroAtk = SDL_CreateTextureFromSurface(ren, surftHeroAtk);
		SDL_RenderCopy(ren, textHeroAtk, &size, &statsTTF);
		SDL_RenderPresent(ren);
		SDL_Delay(500);
		hero.pointsLevel--;
	}
	if (choicheParameter == ABILITYATTACK and hero.pointsLevel != 0) {
		hero.Mana = hero.Mana * 1.1;
		hero.maxMana = hero.Mana * 1.3;
		abilityDamageFireball *= 1.3;
		abilityDamageLighting *= 1.15;
		abilityDamagePoison *= 1.15;
		system("cls");
		printf("Mana %d\n", hero.maxMana);
		printf("abilityDamageFireball %d\n", abilityDamageFireball);
		printf("abilityDamageLighting %d\n", abilityDamageLighting);
		printf("abilityDamagePosion %d\n", abilityDamagePoison);
		sprintf_s(strheroAtk, "Mana %d", hero.maxMana);
		xStats = 700, yStats = 495;
		statsTTF = { xStats, yStats, 280, 105 };
		surftHeroAtk = TTF_RenderText_Blended(heroAtk, strheroAtk, { 255, 255, 255, 255 });
		size = { 0, 0, surftHeroAtk->w, surftHeroAtk->h };
		textHeroAtk = SDL_CreateTextureFromSurface(ren, surftHeroAtk);
		SDL_RenderCopy(ren, textHeroAtk, &size, &statsTTF);
		SDL_RenderPresent(ren);

		sprintf_s(strheroAtk, "Fireball damage %d", abilityDamageFireball);
		xStats = 25, yStats = 220;
		statsTTF = { xStats, yStats, 400, 105 };
		surftHeroAtk = TTF_RenderText_Blended(heroAtk, strheroAtk, { 255, 255, 255, 255 });
		size = { 0, 0, surftHeroAtk->w, surftHeroAtk->h };
		textHeroAtk = SDL_CreateTextureFromSurface(ren, surftHeroAtk);
		SDL_RenderCopy(ren, textHeroAtk, &size, &statsTTF);
		SDL_RenderPresent(ren);

		sprintf_s(strheroAtk, "Lightting damage %d", abilityDamageLighting);
		xStats = 25, yStats = 320;
		statsTTF = { xStats, yStats, 400, 105 };
		surftHeroAtk = TTF_RenderText_Blended(heroAtk, strheroAtk, { 255, 255, 255, 255 });
		size = { 0, 0, surftHeroAtk->w, surftHeroAtk->h };
		textHeroAtk = SDL_CreateTextureFromSurface(ren, surftHeroAtk);
		SDL_RenderCopy(ren, textHeroAtk, &size, &statsTTF);
		SDL_RenderPresent(ren);

		sprintf_s(strheroAtk, "Poison damage %d", abilityDamagePoison);
		xStats = 25, yStats = 420;
		statsTTF = { xStats, yStats, 400, 105 };
		surftHeroAtk = TTF_RenderText_Blended(heroAtk, strheroAtk, { 255, 255, 255, 255 });
		size = { 0, 0, surftHeroAtk->w, surftHeroAtk->h };
		textHeroAtk = SDL_CreateTextureFromSurface(ren, surftHeroAtk);
		SDL_RenderCopy(ren, textHeroAtk, &size, &statsTTF);
		SDL_RenderPresent(ren);
		SDL_Delay(1500);


		hero.pointsLevel--;
	}
	SDL_DestroyTexture(textHeroAtk);
	TTF_CloseFont(heroAtk);
	SDL_FreeSurface(surftHeroAtk);
}

void skill_tree() {
	if (hero.pointsTree > 0) {
		hero.pointsTree--;
	}
	else printf("you don't have skill tree points\n");
}
