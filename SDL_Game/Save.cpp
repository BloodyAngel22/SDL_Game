#define _CRT_SECURE_NO_WARNINGS
#include "Save.h"
#include "Models.h"
#include "Battle.h"
#include "Quest.h"
#include "Puzzle.h"
#include "Minigames.h"
#include "Upgrade Items.h"
#include <SDL.h>
#include <SDL_image.h>

FILE* saves;
char save1[100] = "save1.txt"; char save2[100] = "save2.txt"; char save3[100] = "save3.txt";

void save_in_file(SDL_Renderer* ren) {//���������� � ����
#pragma region Texture
	//Level up
	SDL_Surface* surfSave = IMG_Load("sprites\\menu\\save.png");
	SDL_Texture* textSave = SDL_CreateTextureFromSurface(ren, surfSave);
	SDL_FreeSurface(surfSave);
	//Arrow
	SDL_Surface* surfArrow = IMG_Load("sprites\\menu\\arrow.png");
	SDL_Texture* textArrow = SDL_CreateTextureFromSurface(ren, surfArrow);
	SDL_FreeSurface(surfArrow);
#pragma endregion
	int xArrow = 430, yArrow = 125;
	int pointer = 1;
	const Uint8* arrowState = SDL_GetKeyboardState(NULL);
	SDL_Rect srcrectArrow = { 0, 0, 100, 140 };
	SDL_Rect dstrectArrow;
	
	SDL_Event ev;
	int choiceSaveFile = 0;
	int isPressed = 0;
	while (choiceSaveFile == 0) {
		SDL_PollEvent(&ev);
		dstrectArrow = { xArrow, yArrow, 75, 75 };

		SDL_SetRenderDrawColor(ren, 200, 200, 200, 0);
		SDL_RenderClear(ren);
		SDL_RenderCopy(ren, textSave, NULL, NULL);

		SDL_RenderCopy(ren, textArrow, &srcrectArrow, &dstrectArrow);
		SDL_RenderPresent(ren);

		while (SDL_PollEvent(&ev) != NULL) {
			switch (ev.type) {
			case SDL_KEYDOWN:
				switch (ev.key.keysym.scancode) {
				case SDL_SCANCODE_ESCAPE:
					return;
					break;
				case SDL_SCANCODE_UP:
					if (pointer != 1) {
						yArrow -= 190;
						pointer--;
					}
					break;
				case SDL_SCANCODE_W:
					if (pointer != 1) {
						yArrow -= 190;
						pointer--;
					}
					break;
				case SDL_SCANCODE_DOWN:
					if (pointer != 3) {
						yArrow += 190;
						pointer++;
					}
					break;
				case SDL_SCANCODE_S:
					if (pointer != 3) {
						yArrow += 190;
						pointer++;
					}
					break;
				}
			}
			isPressed = pressedEnter();
		}

		if (pointer == 1 and arrowState[SDL_SCANCODE_RETURN] and isPressed) choiceSaveFile = 1;
		if (pointer == 2 and arrowState[SDL_SCANCODE_RETURN] and isPressed) choiceSaveFile = 2;
		if (pointer == 3 and arrowState[SDL_SCANCODE_RETURN] and isPressed) choiceSaveFile = 3;
		
		isPressed = 0;
	}
	
	if (choiceSaveFile == 1) {
		fopen_s(&saves, save1, "w");
	}
	if (choiceSaveFile == 2) {
		fopen_s(&saves, save2, "w");
	}
	if (choiceSaveFile == 3) {
		fopen_s(&saves, save3, "w");
	}

	fprintf(saves, "%d %d %d %.3f %d %d %d %d %d %d %d %d\n", hero.Health, hero.Attack, hero.Mana, hero.Defense, hero.Gold, hero.experience, 
		hero.level, hero.levelUp, abilityDamageFireball, abilityDamageLightning, abilityDamagePoison, hero.pointsLevel);
	fprintf(saves, "%d %d %.3f %d\n", hero.weapon, hero.armorHealth, hero.armorDefense, hero.necklace);
	fprintf(saves, "%d %d\n", Xcoordinate, Ycoordinate);
	fprintf(saves, "%d %d %d %d %d\n", counterKilledEnemies, curQuest, questFlag, keyCheckBat, keyCheckGoblin);
	fprintf(saves, "%d %d %d %d %d %d %d %d\n", flagCode, checkChest, checkChest2, questFlag, keyCheckBat, keyCheckGoblin, flagLamps, flagRunes);
	fprintf(saves, "%d %d\n", row, col);
	fprintf(saves, "%d\n", winningStreak);
	fprintf(saves, "%d %d %d\n", levelWeapon, levelArmor, levelNecklace);


	fclose(saves);
	SDL_DestroyTexture(textSave);
	SDL_DestroyTexture(textArrow);
}

void print_in_file(SDL_Renderer* ren) {//�������� ����������
#pragma region Texture
	//Level up
	SDL_Surface* surfSave = IMG_Load("sprites\\menu\\save.png");
	SDL_Texture* textSave = SDL_CreateTextureFromSurface(ren, surfSave);
	SDL_FreeSurface(surfSave);
	//Arrow
	SDL_Surface* surfArrow = IMG_Load("sprites\\menu\\arrow.png");
	SDL_Texture* textArrow = SDL_CreateTextureFromSurface(ren, surfArrow);
	SDL_FreeSurface(surfArrow);
#pragma endregion
	int xArrow = 430, yArrow = 125;
	int pointer = 1;
	const Uint8* arrowState = SDL_GetKeyboardState(NULL);
	SDL_Rect srcrectArrow = { 0, 0, 100, 140 };
	SDL_Rect dstrectArrow;

	SDL_Event ev;
	int isPressed = 0;
	int choicePrintFile = 0;
	while (choicePrintFile == 0) {
		SDL_PollEvent(&ev);
		dstrectArrow = { xArrow, yArrow, 75, 75 };

		SDL_SetRenderDrawColor(ren, 200, 200, 200, 0);
		SDL_RenderClear(ren);
		SDL_RenderCopy(ren, textSave, NULL, NULL);

		SDL_RenderCopy(ren, textArrow, &srcrectArrow, &dstrectArrow);
		SDL_RenderPresent(ren);

		while (SDL_PollEvent(&ev) != NULL) {
			switch (ev.type) {
			case SDL_KEYDOWN:
				switch (ev.key.keysym.scancode) {
				case SDL_SCANCODE_ESCAPE:
					return;
					break;
				case SDL_SCANCODE_UP:
					if (pointer != 1) {
						yArrow -= 190;
						pointer--;
					}
					break;
				case SDL_SCANCODE_W:
					if (pointer != 1) {
						yArrow -= 190;
						pointer--;
					}
					break;
				case SDL_SCANCODE_DOWN:
					if (pointer != 3) {
						yArrow += 190;
						pointer++;
					}
					break;
				case SDL_SCANCODE_S:
					if (pointer != 3) {
						yArrow += 190;
						pointer++;
					}
					break;
				}
			}
			isPressed = pressedEnter();
		}

		if (pointer == 1 and arrowState[SDL_SCANCODE_RETURN] and isPressed) choicePrintFile = 1;
		if (pointer == 2 and arrowState[SDL_SCANCODE_RETURN] and isPressed) choicePrintFile = 2;
		if (pointer == 3 and arrowState[SDL_SCANCODE_RETURN] and isPressed) choicePrintFile = 3;

		isPressed = 0;
	}

	if (choicePrintFile == 1) {
		fopen_s(&saves, save1, "rt");
		fscanf(saves, "%d %d %d %f %d %d %d %d %d %d %d %d\n", &hero.Health, &hero.Attack, &hero.Mana, &hero.Defense, &hero.Gold, &hero.experience,
			&hero.level, &hero.levelUp, &abilityDamageFireball, &abilityDamageLightning, &abilityDamagePoison, &hero.pointsLevel);
		hero.maxHealth = hero.Health; hero.maxMana = hero.Mana;
		fscanf(saves, "%d %d %f %d\n", &hero.weapon, &hero.armorHealth, &hero.armorDefense, &hero.necklace);
		fscanf(saves, "%d %d\n", &Xcoordinate, &Ycoordinate);
		fscanf(saves, "%d %d %d %d %d\n", &counterKilledEnemies ,&curQuest, &questFlag, &keyCheckBat, &keyCheckGoblin);
		fscanf(saves, "%d %d %d %d %d %d %d %d\n", &flagCode, &checkChest, &checkChest2, &questFlag, &keyCheckBat, &keyCheckGoblin, &flagLamps, &flagRunes);
		fscanf(saves, "%d %d\n", &row, &col);
		fscanf(saves, "%d\n", &winningStreak);
		fscanf(saves, "%d %d %d\n", &levelWeapon, &levelArmor, &levelNecklace);
	}
	if (choicePrintFile == 2) {
		fopen_s(&saves, save2, "rt");
		fscanf(saves, "%d %d %d %f %d %d %d %d %d %d %d %d\n", &hero.Health, &hero.Attack, &hero.Mana, &hero.Defense, &hero.Gold, &hero.experience,
			&hero.level, &hero.levelUp, &abilityDamageFireball, &abilityDamageLightning, &abilityDamagePoison, &hero.pointsLevel);
		hero.maxHealth = hero.Health; hero.maxMana = hero.Mana;
		fscanf(saves, "%d %d %f %d\n", &hero.weapon, &hero.armorHealth, &hero.armorDefense, &hero.necklace);
		fscanf(saves, "%d %d\n", &Xcoordinate, &Ycoordinate);
		fscanf(saves, "%d %d %d %d %d\n", &counterKilledEnemies, &curQuest, &questFlag, &keyCheckBat, &keyCheckGoblin);
		fscanf(saves, "%d %d %d %d %d %d %d %d\n", &flagCode, &checkChest, &checkChest2, &questFlag, &keyCheckBat, &keyCheckGoblin, &flagLamps, &flagRunes);
		fscanf(saves, "%d %d\n", &row, &col);
		fscanf(saves, "%d\n", &winningStreak);
		fscanf(saves, "%d %d %d\n", &levelWeapon, &levelArmor, &levelNecklace);

	}
	if (choicePrintFile == 3) {
		fopen_s(&saves, save3, "rt");
		fscanf(saves, "%d %d %d %f %d %d %d %d %d %d %d %d\n", &hero.Health, &hero.Attack, &hero.Mana, &hero.Defense, &hero.Gold, &hero.experience,
			&hero.level, &hero.levelUp, &abilityDamageFireball, &abilityDamageLightning, &abilityDamagePoison, &hero.pointsLevel);
		hero.maxHealth = hero.Health; hero.maxMana = hero.Mana;
		fscanf(saves, "%d %d %f %d\n", &hero.weapon, &hero.armorHealth, &hero.armorDefense, &hero.necklace);
		fscanf(saves, "%d %d\n", &Xcoordinate, &Ycoordinate);
		fscanf(saves, "%d %d %d %d %d\n", &counterKilledEnemies, &curQuest, &questFlag, &keyCheckBat, &keyCheckGoblin);
		fscanf(saves, "%d %d %d %d %d %d %d %d\n", &flagCode, &checkChest, &checkChest2, &questFlag, &keyCheckBat, &keyCheckGoblin, &flagLamps, &flagRunes);
		fscanf(saves, "%d %d\n", &row, &col);
		fscanf(saves, "%d\n", &winningStreak);
		fscanf(saves, "%d %d %d\n", &levelWeapon, &levelArmor, &levelNecklace);

	}


	fclose(saves);
}