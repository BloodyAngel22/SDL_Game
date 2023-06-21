#define ATTACK 1
#define HEALTH 2
#define PROTECTION 3
#define ABILITYATTACK 4
#define EXIT 5
#include "Models.h"
#include "Ability.h"
#include "Battle.h"
#include "Runes.h"
#include <stdio.h>
#include <stdlib.h>
#include <SDL.h>
#include <SDL_image.h>
#include <SDL_ttf.h>


void level_up() {
	if ((hero.experience >= hero.levelUp) and (hero.level <= hero.maxLevel)) {
		int tmpExperience = hero.experience;
		while (tmpExperience >= hero.levelUp and hero.level <= hero.maxLevel) {
			hero.level += 1;
			hero.pointsLevel += 4;
			tmpExperience -= hero.levelUp;
			hero.levelUp = hero.levelUp * 1.5;
			system("cls");
			printf("Level up\n");
			if (tmpExperience < hero.levelUp)
				hero.experience = tmpExperience;

		}
	}
	//if (hero.level % 3 == 0) {
	//	hero.pointsTree += 1;
	//	printf("pointsTree %d\n", hero.pointsTree);
	//}
	//if (hero.level % 10 == 0) {
	//	hero.pointsTree += 2;
	//	printf("pointsTree %d\n", hero.pointsTree);
	//}
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
	int xPoint = 1100, yPoint = 20;
	SDL_Rect pointsTTF = { xPoint, yPoint, 55, 60 };
	int xStats = 700, yStats = 165;
#pragma endregion
	int xArrow = 370, yArrow = 175;
	int pointer = 1;
	const Uint8* arrowState = SDL_GetKeyboardState(NULL);
	SDL_Rect srcrectArrow = { 0, 0, 100, 140 };
	SDL_Rect dstrectArrow;
	int choicheParameter = 0;
	SDL_Event ev;
	while (choicheParameter == 0) {
		SDL_PollEvent(&ev);
		dstrectArrow = { xArrow, yArrow, 75, 75 };

		xPoint = 1100, yPoint = 20;
		pointsTTF = { xPoint, yPoint, 55, 60 };
		sprintf_s(heroPoints, "%d", hero.pointsLevel);
		surftHeroPointTTF = TTF_RenderText_Blended(heroPointTTF, heroPoints, { 255, 255, 255, 255 });
		size = { 0, 0, surftHeroPointTTF->w, surftHeroPointTTF->h };
		textHeroPointTTF = SDL_CreateTextureFromSurface(ren, surftHeroPointTTF);

		SDL_SetRenderDrawColor(ren, 200, 200, 200, 0);
		SDL_RenderClear(ren);
		SDL_RenderCopy(ren, textLevelUp, NULL, NULL);
		SDL_RenderCopy(ren, textHeroPointTTF, &size, &pointsTTF);
		SDL_FreeSurface(surftHeroPointTTF);
		SDL_DestroyTexture(textHeroPointTTF);
		#pragma region TTF
		xPoint = 700, yPoint = 180;
		sprintf_s(heroPoints, "-> %d", hero.Attack);
		surftHeroPointTTF = TTF_RenderText_Blended(heroPointTTF, heroPoints, { 255, 255, 255, 255 });
		pointsTTF = { xPoint, yPoint, 200, 80 };
		size = { 0, 0, surftHeroPointTTF->w, surftHeroPointTTF->h };
		textHeroPointTTF = SDL_CreateTextureFromSurface(ren, surftHeroPointTTF);
		SDL_RenderCopy(ren, textHeroPointTTF, &size, &pointsTTF);
		SDL_FreeSurface(surftHeroPointTTF);
		SDL_DestroyTexture(textHeroPointTTF);

		xPoint = 700, yPoint = 290;
		sprintf_s(heroPoints, "-> %d", hero.maxHealth);
		surftHeroPointTTF = TTF_RenderText_Blended(heroPointTTF, heroPoints, { 255, 255, 255, 255 });
		pointsTTF = { xPoint, yPoint, 200, 80 };
		size = { 0, 0, surftHeroPointTTF->w, surftHeroPointTTF->h };
		textHeroPointTTF = SDL_CreateTextureFromSurface(ren, surftHeroPointTTF);
		SDL_RenderCopy(ren, textHeroPointTTF, &size, &pointsTTF);
		SDL_FreeSurface(surftHeroPointTTF);
		SDL_DestroyTexture(textHeroPointTTF);

		xPoint = 700, yPoint = 400;
		sprintf_s(heroPoints, "-> %.2f", hero.Defense);
		surftHeroPointTTF = TTF_RenderText_Blended(heroPointTTF, heroPoints, { 255, 255, 255, 255 });
		pointsTTF = { xPoint, yPoint, 200, 80 };
		size = { 0, 0, surftHeroPointTTF->w, surftHeroPointTTF->h };
		textHeroPointTTF = SDL_CreateTextureFromSurface(ren, surftHeroPointTTF);
		SDL_RenderCopy(ren, textHeroPointTTF, &size, &pointsTTF);
		SDL_FreeSurface(surftHeroPointTTF);
		SDL_DestroyTexture(textHeroPointTTF);

		xPoint = 700, yPoint = 510;
		sprintf_s(heroPoints, "-> mana %d", hero.maxMana);
		surftHeroPointTTF = TTF_RenderText_Blended(heroPointTTF, heroPoints, { 255, 255, 255, 255 });
		pointsTTF = { xPoint, yPoint, 400, 80 };
		size = { 0, 0, surftHeroPointTTF->w, surftHeroPointTTF->h };
		textHeroPointTTF = SDL_CreateTextureFromSurface(ren, surftHeroPointTTF);
		SDL_RenderCopy(ren, textHeroPointTTF, &size, &pointsTTF);
		SDL_FreeSurface(surftHeroPointTTF);
		SDL_DestroyTexture(textHeroPointTTF);

		xPoint = 10, yPoint = 510;
		sprintf_s(heroPoints, "fireball %d <-", abilityDamageFireball);
		surftHeroPointTTF = TTF_RenderText_Blended(heroPointTTF, heroPoints, { 255, 255, 255, 255 });
		pointsTTF = { xPoint, yPoint, 440, 80 };
		size = { 0, 0, surftHeroPointTTF->w, surftHeroPointTTF->h };
		textHeroPointTTF = SDL_CreateTextureFromSurface(ren, surftHeroPointTTF);
		SDL_RenderCopy(ren, textHeroPointTTF, &size, &pointsTTF);
		SDL_FreeSurface(surftHeroPointTTF);
		SDL_DestroyTexture(textHeroPointTTF);

		xPoint = 10, yPoint = 400;
		sprintf_s(heroPoints, "lightning %d", abilityDamageLightning);
		surftHeroPointTTF = TTF_RenderText_Blended(heroPointTTF, heroPoints, { 255, 255, 255, 255 });
		pointsTTF = { xPoint, yPoint, 400, 80 };
		size = { 0, 0, surftHeroPointTTF->w, surftHeroPointTTF->h };
		textHeroPointTTF = SDL_CreateTextureFromSurface(ren, surftHeroPointTTF);
		SDL_RenderCopy(ren, textHeroPointTTF, &size, &pointsTTF);
		SDL_FreeSurface(surftHeroPointTTF);
		SDL_DestroyTexture(textHeroPointTTF);

		xPoint = 10, yPoint = 290;
		sprintf_s(heroPoints, "poison %d", abilityDamagePoison);
		surftHeroPointTTF = TTF_RenderText_Blended(heroPointTTF, heroPoints, { 255, 255, 255, 255 });
		pointsTTF = { xPoint, yPoint, 320, 80 };
		size = { 0, 0, surftHeroPointTTF->w, surftHeroPointTTF->h };
		textHeroPointTTF = SDL_CreateTextureFromSurface(ren, surftHeroPointTTF);
		SDL_RenderCopy(ren, textHeroPointTTF, &size, &pointsTTF);
		SDL_FreeSurface(surftHeroPointTTF);
		SDL_DestroyTexture(textHeroPointTTF);
#pragma endregion
		SDL_RenderCopy(ren, textArrow, &srcrectArrow, &dstrectArrow);
		SDL_RenderPresent(ren);
	
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

	if (choicheParameter == ATTACK and hero.pointsLevel != 0) {
		hero.Attack += 5;
		hero.maxAttack = hero.Attack;
		system("cls");
		hero.pointsLevel--;
	}
	if (choicheParameter == HEALTH and hero.pointsLevel != 0) {
		hero.Health += 20;
		hero.maxHealth = hero.Health;
		system("cls");
		hero.pointsLevel--;
	}
	if (choicheParameter == PROTECTION and hero.pointsLevel != 0) {
		if (hero.Defense >= 0.55) {
			printf("Defense max\n");
			return;
		}
		hero.Defense = hero.Defense + 0.025;
		system("cls");
		hero.pointsLevel--;
	}
	if (choicheParameter == ABILITYATTACK and hero.pointsLevel != 0) {
		hero.Mana += 20;
		hero.maxMana = hero.Mana;
		abilityDamageFireball += 10;
		abilityDamageLightning += 7;
		abilityDamagePoison += 1;
		poisonDamage = abilityDamagePoison;
		system("cls");
		hero.pointsLevel--;
	}
}

void skill_tree() {
	if (hero.pointsTree > 0) {
		hero.pointsTree--;
	}
	else printf("you don't have skill tree points\n");
}

void set_runes(bool& runeWater, bool& runeFire, bool& runeEarth) {
	Rune water;
	water.attack = 1;
	water.damageAbility = 1.2;
	water.defense = 1;
	water.health = 1.3;

	Rune fire;
	fire.attack = 1.3;
	fire.damageAbility = 1;
	fire.defense = 1;
	fire.health = 1.1;

	Rune earth;
	earth.attack = 1;
	earth.damageAbility = 1.2;
	earth.defense = 1.2;
	earth.health = 1.2;

	if (runeWater == 1) {
		hero.Attack *= water.attack;
		abilityDamageFireball *= water.damageAbility;
		abilityDamageLightning *= water.damageAbility;
		abilityDamagePoison *= water.damageAbility;
		hero.Defense *= water.defense;
		hero.Health *= water.health;
		hero.maxHealth = hero.Health;
	}
	if (runeFire == 1) {
		hero.Attack *= fire.attack;
		abilityDamageFireball *= fire.damageAbility;
		abilityDamageLightning *= fire.damageAbility;
		abilityDamagePoison *= fire.damageAbility;
		hero.Defense *= fire.defense;
		hero.Health *= fire.health;
		hero.maxHealth = hero.Health;
	}
	if (runeEarth == 1) {
		hero.Attack *= earth.attack;
		abilityDamageFireball *= earth.damageAbility;
		abilityDamageLightning *= earth.damageAbility;
		abilityDamagePoison *= earth.damageAbility;
		hero.Defense *= earth.defense;
		hero.Health *= earth.health;
		hero.maxHealth = hero.Health;
	}
}

void remove_the_rune(bool& runeWater, bool& runeFire, bool& runeEarth) {
	Rune water;
	water.attack = 1;
	water.damageAbility = 1.2;
	water.defense = 1;
	water.health = 1.3;

	Rune fire;
	fire.attack = 1.3;
	fire.damageAbility = 1;
	fire.defense = 1;
	fire.health = 1.1;

	Rune earth;
	earth.attack = 1;
	earth.damageAbility = 1.2;
	earth.defense = 1.2;
	earth.health = 1.2;

	if (runeWater == 1) {
		hero.Attack /= water.attack;
		abilityDamageFireball /= water.damageAbility;
		abilityDamageLightning /= water.damageAbility;
		abilityDamagePoison /= water.damageAbility;
		hero.Defense /= water.defense;
		hero.Health /= water.health;
		hero.maxHealth = hero.Health;
		runeWater = 0;
	}
	if (runeFire == 1) {
		hero.Attack /= fire.attack;
		abilityDamageFireball /= fire.damageAbility;
		abilityDamageLightning /= fire.damageAbility;
		abilityDamagePoison /= fire.damageAbility;
		hero.Defense /= fire.defense;
		hero.Health /= fire.health;
		hero.maxHealth = hero.Health;
		runeFire = 0;
	}
	if (runeEarth == 1) {
		hero.Attack /= earth.attack;
		abilityDamageFireball /= earth.damageAbility;
		abilityDamageLightning /= earth.damageAbility;
		abilityDamagePoison /= earth.damageAbility;
		hero.Defense /= earth.defense;
		hero.Health /= earth.health;
		hero.maxHealth = hero.Health;
		runeEarth = 0;
	}
}
