#include "Models.h"
#include "Battle.h"
#include "Upgrade Items.h"
#include <iostream>
#include <SDL.h>
#include <SDL_image.h>
#include <SDL_ttf.h>

int levelWeapon = 0; int levelArmor = 0; int levelNecklace = 0;

void upgradeWeapon(SDL_Renderer* ren); void upgradeArmor(SDL_Renderer* ren); void upgradeNecklace(SDL_Renderer* ren);
upgradeLVL itemUpgrade;

void upgradeItems(SDL_Renderer* ren) {
#pragma region Texture
	//Level up
	SDL_Surface* surfChoiceItem = IMG_Load("sprites\\menu\\choiceItem.png");
	SDL_Texture* textchoiceItem = SDL_CreateTextureFromSurface(ren, surfChoiceItem);
	SDL_FreeSurface(surfChoiceItem);
	//Arrow
	SDL_Surface* surfArrow = IMG_Load("sprites\\menu\\arrow.png");
	SDL_Texture* textArrow = SDL_CreateTextureFromSurface(ren, surfArrow);
	SDL_FreeSurface(surfArrow);
#pragma endregion
	int choiche = 0;
	int xArrow = 50, yArrow = 290;
	int pointer = 1;
	const Uint8* arrowState = SDL_GetKeyboardState(NULL);
	SDL_Rect srcrectArrow = { 0, 0, 100, 140 };
	SDL_Rect dstrectArrow;
	SDL_Event ev;
	while (choiche == 0) {
		SDL_PollEvent(&ev);
		dstrectArrow = { xArrow, yArrow, 75, 75 };

		SDL_SetRenderDrawColor(ren, 200, 200, 200, 0);
		SDL_RenderClear(ren);
		SDL_RenderCopy(ren, textchoiceItem, NULL, NULL);
		SDL_RenderCopy(ren, textArrow, &srcrectArrow, &dstrectArrow);
		SDL_RenderPresent(ren);
		

		while (SDL_PollEvent(&ev) != NULL) {
			switch (ev.type) {
			case SDL_KEYDOWN:
				switch (ev.key.keysym.scancode) {
				case SDL_SCANCODE_LEFT:
					if (pointer != 1) {
						xArrow -= 380;
						pointer--;
					}
					break;
				case SDL_SCANCODE_A:
					if (pointer != 1) {
						xArrow -= 380;
						pointer--;
					}
					break;
				case SDL_SCANCODE_RIGHT:
					if (pointer != 3) {
						xArrow += 380;
						pointer++;
					}
					break;
				case SDL_SCANCODE_D:
					if (pointer != 3) {
						xArrow += 380;
						pointer++;
					}
					break;
				case SDL_SCANCODE_ESCAPE:
					SDL_DestroyTexture(textchoiceItem);
					SDL_DestroyTexture(textArrow);
					return;
					break;
				}

			}
			isPressed = pressedEnter();
		}

		if (pointer == 1 and arrowState[SDL_SCANCODE_RETURN] and isPressed) choiche = 1;
		if (pointer == 2 and arrowState[SDL_SCANCODE_RETURN] and isPressed) choiche = 2;
		if (pointer == 3 and arrowState[SDL_SCANCODE_RETURN] and isPressed) choiche = 3;

		isPressed = 0;
	}

	SDL_DestroyTexture(textchoiceItem);
	SDL_DestroyTexture(textArrow);

	if (choiche == 1) upgradeWeapon(ren);
	if (choiche == 2) upgradeArmor(ren);
	if (choiche == 3) upgradeNecklace(ren);
}

void upgradeWeapon(SDL_Renderer* ren) {
	system("chcp 1251");
#pragma region Texture
	//Level up
	SDL_Surface* surfupgradeWeapon = IMG_Load("sprites\\menu\\upgradeWeapon.png");
	SDL_Texture* textupgradeWeapon = SDL_CreateTextureFromSurface(ren, surfupgradeWeapon);
	SDL_FreeSurface(surfupgradeWeapon);
	//Arrow
	SDL_Surface* surfArrow = IMG_Load("sprites\\menu\\arrow.png");
	SDL_Texture* textArrow = SDL_CreateTextureFromSurface(ren, surfArrow);
	SDL_FreeSurface(surfArrow);
	//
	TTF_Font* statItemsFont = TTF_OpenFont("fonts\\BAUHS93.TTF", 75);
	char stats[100] = "stats";
	SDL_Surface* surfStatItems = TTF_RenderText_Blended(statItemsFont, stats, { 255, 255, 255, 255 });
	SDL_Texture* textStatItemsText = SDL_CreateTextureFromSurface(ren, surfStatItems);
	SDL_Rect size = { 0, 0, surfStatItems->w, surfStatItems->h };
	int xPoint = 100, yPoint = 50;
	SDL_Rect statsRect = { xPoint, yPoint, 55, 60 };
	SDL_FreeSurface(surfStatItems);
#pragma endregion
	int upgrade = 1;
	int xArrow = 40, yArrow = 350;
	int pointer = 1;
	const Uint8* arrowState = SDL_GetKeyboardState(NULL);
	SDL_Rect srcrectArrow = { 0, 0, 100, 140 };
	SDL_Rect dstrectArrow;
	SDL_Event ev;
	SDL_PollEvent(&ev);
	dstrectArrow = { xArrow, yArrow, 75, 75 };
#pragma region Arrow
		if (levelWeapon == 0) {
			xArrow = 10, yArrow = 240;
			dstrectArrow = { xArrow, yArrow, 75, 75 };
		}
		if (levelWeapon == 1) {
			xArrow = 290, yArrow = 240;
			dstrectArrow = { xArrow, yArrow, 75, 75 };
		}
		if (levelWeapon == 2) {
			xArrow = 570, yArrow = 240;
			dstrectArrow = { xArrow, yArrow, 75, 75 };
		}
		if (levelWeapon == 3) {
			xArrow = 850, yArrow = 240;
			dstrectArrow = { xArrow, yArrow, 75, 75 };
		}
		if (levelWeapon == 4) {
			xArrow = 440, yArrow = 405;
			dstrectArrow = { xArrow, yArrow, 75, 75 };
		}
		if (levelWeapon == 5) {
			xArrow = 440, yArrow = 405;
			dstrectArrow = { xArrow, yArrow, 75, 75 };
		}
#pragma endregion
		while (upgrade == 1) {
			while (SDL_PollEvent(&ev) != NULL) {
				isPressed = pressedEnter();

				if (arrowState[SDL_SCANCODE_ESCAPE]) {
					SDL_DestroyTexture(textupgradeWeapon);
					SDL_DestroyTexture(textArrow);
					return;
				}
				if (levelWeapon == 0 and upgrade == 1 and arrowState[SDL_SCANCODE_RETURN] and isPressed) {
					if (upgrade == 1 and hero.Gold >= itemUpgrade.LVL1) {
						hero.Attack -= 10;
						hero.weapon += 10;
						hero.Attack += hero.weapon;
						upgrade = 0;
						levelWeapon = 1;
						hero.Gold -= itemUpgrade.LVL1;
					}
					if (upgrade == 1 and hero.Gold < itemUpgrade.LVL1) {
						printf("У вас не достаточно денег\n");
						upgrade = 0;
					}
				}
				if (levelWeapon == 1 and upgrade == 1 and arrowState[SDL_SCANCODE_RETURN] and isPressed) {
					if (upgrade == 1 and hero.Gold >= itemUpgrade.LVL2) {
						hero.Attack -= 10;
						hero.weapon += 10;
						hero.Attack += hero.weapon;
						upgrade = 0;
						levelWeapon = 2;
						hero.Gold -= itemUpgrade.LVL2;
					}
					if (upgrade == 1 and hero.Gold < itemUpgrade.LVL2) {
						printf("У вас не достаточно денег\n");
						upgrade = 0;
					}
				}
				if (levelWeapon == 2 and upgrade == 1 and arrowState[SDL_SCANCODE_RETURN] and isPressed) {
					if (upgrade == 1 and hero.Gold >= itemUpgrade.LVL3) {
						hero.Attack -= 10;
						hero.weapon += 10;
						hero.Attack += hero.weapon;
						upgrade = 0;
						levelWeapon = 3;
						hero.Gold -= itemUpgrade.LVL3;
					}
					if (upgrade == 1 and hero.Gold < itemUpgrade.LVL3) {
						printf("У вас не достаточно денег\n");
						upgrade = 0;
					}
				}
				if (levelWeapon == 3 and upgrade == 1 and arrowState[SDL_SCANCODE_RETURN] and isPressed) {
					if (upgrade == 1 and hero.Gold >= itemUpgrade.LVL4) {
						hero.Attack -= 10;
						hero.weapon += 10;
						hero.Attack += hero.weapon;
						upgrade = 0;
						levelWeapon = 4;
						hero.Gold -= itemUpgrade.LVL4;
					}
					if (upgrade == 1 and hero.Gold < itemUpgrade.LVL4) {
						printf("У вас не достаточно денег\n");
						upgrade = 0;
					}
				}
				if (levelWeapon == 4 and upgrade == 1 and arrowState[SDL_SCANCODE_RETURN] and isPressed) {
					if (upgrade == 1 and hero.Gold >= itemUpgrade.LVL5) {
						hero.Attack -= 10;
						hero.weapon += 10;
						hero.Attack += hero.weapon;
						upgrade = 0;
						levelWeapon = 5;
						hero.Gold -= itemUpgrade.LVL5;
					}
					if (upgrade == 1 and hero.Gold < itemUpgrade.LVL5) {
						printf("У вас не достаточно денег\n");
						upgrade = 0;
					}
				}
				if (levelWeapon == 5 and upgrade == 1 and arrowState[SDL_SCANCODE_RETURN] and isPressed) {
					printf("У вас максимальный уровень оружия\nВам больше нечего прокачивать\n");
					upgrade = 0;
				}
			}

			SDL_SetRenderDrawColor(ren, 200, 200, 200, 0);
			SDL_RenderClear(ren);
			SDL_RenderCopy(ren, textupgradeWeapon, NULL, NULL);
			SDL_RenderCopy(ren, textArrow, &srcrectArrow, &dstrectArrow);

			xPoint = 100, yPoint = 50;
			statsRect = { xPoint, yPoint, 55, 60 };
			sprintf_s(stats, "%d", hero.weapon);
			surfStatItems = TTF_RenderText_Blended(statItemsFont, stats, { 255, 255, 255, 255 });
			size = { 0, 0, surfStatItems->w, surfStatItems->h };
			textStatItemsText = SDL_CreateTextureFromSurface(ren, surfStatItems);
			SDL_RenderCopy(ren, textStatItemsText, &size, &statsRect);
			SDL_FreeSurface(surfStatItems);
			SDL_DestroyTexture(textStatItemsText);

			SDL_RenderPresent(ren);
		}
		isPressed = 0;
		
		SDL_DestroyTexture(textArrow);
		SDL_DestroyTexture(textStatItemsText);
		SDL_DestroyTexture(textupgradeWeapon);

		TTF_CloseFont(statItemsFont);
}

void upgradeArmor(SDL_Renderer* ren) {
	system("chcp 1251");
#pragma region Texture
	//Level up
	SDL_Surface* surfupgradeArmor = IMG_Load("sprites\\menu\\upgradeArmor.png");
	SDL_Texture* textupgradeArmor = SDL_CreateTextureFromSurface(ren, surfupgradeArmor);
	SDL_FreeSurface(surfupgradeArmor);
	//Arrow
	SDL_Surface* surfArrow = IMG_Load("sprites\\menu\\arrow.png");
	SDL_Texture* textArrow = SDL_CreateTextureFromSurface(ren, surfArrow);
	SDL_FreeSurface(surfArrow);
	//
	TTF_Font* statItemsFont = TTF_OpenFont("fonts\\BAUHS93.TTF", 75);
	char stats[100] = "stats";
	SDL_Surface* surfStatItems = TTF_RenderText_Blended(statItemsFont, stats, { 255, 255, 255, 255 });
	SDL_Texture* textStatItemsText = SDL_CreateTextureFromSurface(ren, surfStatItems);
	SDL_Rect size = { 0, 0, surfStatItems->w, surfStatItems->h };
	int xPoint = 100, yPoint = 50;
	SDL_Rect statsRect = { xPoint, yPoint, 55, 60 };
	SDL_FreeSurface(surfStatItems);
#pragma endregion
	int upgrade = 1;
	int xArrow = 40, yArrow = 245;
	int pointer = 1;
	const Uint8* arrowState = SDL_GetKeyboardState(NULL);
	SDL_Rect srcrectArrow = { 0, 0, 100, 140 };
	SDL_Rect dstrectArrow;
	SDL_Event ev;
	SDL_PollEvent(&ev);
	dstrectArrow = { xArrow, yArrow, 75, 75 };
#pragma region Arrow
	if (levelArmor == 0) {
		xArrow = 10, yArrow = 240;
		dstrectArrow = { xArrow, yArrow, 75, 75 };
	}
	if (levelArmor == 1) {
		xArrow = 290, yArrow = 240;
		dstrectArrow = { xArrow, yArrow, 75, 75 };
	}
	if (levelArmor == 2) {
		xArrow = 570, yArrow = 240;
		dstrectArrow = { xArrow, yArrow, 75, 75 };
	}
	if (levelArmor == 3) {
		xArrow = 850, yArrow = 240;
		dstrectArrow = { xArrow, yArrow, 75, 75 };
	}
	if (levelArmor == 4) {
		xArrow = 440, yArrow = 405;
		dstrectArrow = { xArrow, yArrow, 75, 75 };
	}
	if (levelArmor == 5) {
		xArrow = 440, yArrow = 405;
		dstrectArrow = { xArrow, yArrow, 75, 75 };
	}
#pragma endregion
	
	while (upgrade == 1) {
		while (SDL_PollEvent(&ev) != NULL) {
			isPressed = pressedEnter();
			if (arrowState[SDL_SCANCODE_ESCAPE]) { 
				SDL_DestroyTexture(textupgradeArmor);
				SDL_DestroyTexture(textArrow);
				return; 
			}
			if (levelArmor == 0 and upgrade == 1 and arrowState[SDL_SCANCODE_RETURN] and isPressed) {
				if (upgrade == 1 and hero.Gold >= itemUpgrade.LVL1) {
					hero.maxHealth += 30;
					hero.Defense -= 0.025;
					hero.armorHealth += 30;
					hero.armorDefense += 0.010;
					hero.Health = hero.maxHealth;
					hero.Defense += hero.armorDefense;
					upgrade = 0;
					levelArmor = 1;
					hero.Gold -= itemUpgrade.LVL1;
				}
				if (upgrade == 1 and hero.Gold < itemUpgrade.LVL1) {
					printf("У вас не достаточно денег\n");
					upgrade = 0;
				}
			}
			if (levelArmor == 1 and upgrade == 1 and arrowState[SDL_SCANCODE_RETURN] and isPressed) {
				if (upgrade == 1 and hero.Gold >= itemUpgrade.LVL2) {
					hero.maxHealth += 30;
					hero.Defense -= 0.025;
					hero.armorHealth += 30;
					hero.armorDefense += 0.010;
					hero.Health = hero.maxHealth;
					hero.Defense += hero.armorDefense;
					upgrade = 0;
					levelArmor = 2;
					hero.Gold -= itemUpgrade.LVL2;
				}
				if (upgrade == 1 and hero.Gold < itemUpgrade.LVL2) {
					printf("У вас не достаточно денег\n");
					upgrade = 0;
				}
				
			}
			if (levelArmor == 2 and upgrade == 1 and arrowState[SDL_SCANCODE_RETURN] and isPressed) {
				if (upgrade == 1 and hero.Gold >= itemUpgrade.LVL3) {
					hero.maxHealth += 30;
					hero.Defense -= 0.025;
					hero.armorHealth += 30;
					hero.armorDefense += 0.010;
					hero.Health = hero.maxHealth;
					hero.Defense += hero.armorDefense;
					upgrade = 0;
					levelArmor = 3;
					hero.Gold -= itemUpgrade.LVL3;
				}
				if (upgrade == 1 and hero.Gold < itemUpgrade.LVL3) {
					printf("У вас не достаточно денег\n");
					upgrade = 0;
				}
				
			}
			if (levelArmor == 3 and upgrade == 1 and arrowState[SDL_SCANCODE_RETURN] and isPressed) {
				if (upgrade == 1 and hero.Gold >= itemUpgrade.LVL4) {
					hero.maxHealth += 30;
					hero.Defense -= 0.025;
					hero.armorHealth += 30;
					hero.armorDefense += 0.010;
					hero.Health = hero.maxHealth;
					hero.Defense += hero.armorDefense;
					upgrade = 0;
					levelArmor = 4;
					hero.Gold -= itemUpgrade.LVL4;
				}
				if (upgrade == 1 and hero.Gold < itemUpgrade.LVL4) {
					printf("У вас не достаточно денег\n");
					upgrade = 0;
				}
				
			}
			if (levelArmor == 4 and upgrade == 1 and arrowState[SDL_SCANCODE_RETURN] and isPressed) {
				if (upgrade == 1 and hero.Gold >= itemUpgrade.LVL5) {
					hero.maxHealth += 30;
					hero.Defense -= 0.025;
					hero.armorHealth += 30;
					hero.armorDefense += 0.010;
					hero.Health = hero.maxHealth;
					hero.Defense += hero.armorDefense;
					upgrade = 0;
					levelArmor = 5;
					hero.Gold -= itemUpgrade.LVL5;
				}
				if (upgrade == 1 and hero.Gold < itemUpgrade.LVL5) {
					printf("У вас не достаточно денег\n");
					upgrade = 0;
				}
				
			}
			if (levelArmor == 5 and upgrade == 1 and arrowState[SDL_SCANCODE_RETURN] and isPressed) {
				printf("У вас максимальный уровень брони\nВам больше нечего прокачивать\n");
				upgrade = 0;
			}
		}
		SDL_SetRenderDrawColor(ren, 200, 200, 200, 0);
		SDL_RenderClear(ren);
		SDL_RenderCopy(ren, textupgradeArmor, NULL, NULL);

		xPoint = 100, yPoint = 50;
		statsRect = { xPoint, yPoint, 55, 60 };
		sprintf_s(stats, "%d", hero.armorHealth);
		surfStatItems = TTF_RenderText_Blended(statItemsFont, stats, { 255, 255, 255, 255 });
		size = { 0, 0, surfStatItems->w, surfStatItems->h };
		textStatItemsText = SDL_CreateTextureFromSurface(ren, surfStatItems);
		SDL_RenderCopy(ren, textStatItemsText, &size, &statsRect);
		SDL_FreeSurface(surfStatItems);
		SDL_DestroyTexture(textStatItemsText);

		xPoint = 100, yPoint = 100;
		statsRect = { xPoint, yPoint, 55, 60 };
		sprintf_s(stats, "%.2f", hero.armorDefense);
		surfStatItems = TTF_RenderText_Blended(statItemsFont, stats, { 255, 255, 255, 255 });
		size = { 0, 0, surfStatItems->w, surfStatItems->h };
		textStatItemsText = SDL_CreateTextureFromSurface(ren, surfStatItems);
		SDL_RenderCopy(ren, textStatItemsText, &size, &statsRect);
		SDL_FreeSurface(surfStatItems);
		SDL_DestroyTexture(textStatItemsText);

		SDL_RenderCopy(ren, textArrow, &srcrectArrow, &dstrectArrow);
		SDL_RenderPresent(ren);
	}
	
	SDL_DestroyTexture(textArrow);
	SDL_DestroyTexture(textStatItemsText);
	SDL_DestroyTexture(textupgradeArmor);

	TTF_CloseFont(statItemsFont);
	isPressed = 0;
}

void upgradeNecklace(SDL_Renderer* ren) {
	system("chcp 1251");
#pragma region Texture
	//Level up
	SDL_Surface* surfupgradeNecklace = IMG_Load("sprites\\menu\\upgradeNecklace.png");
	SDL_Texture* textupgradeNecklace = SDL_CreateTextureFromSurface(ren, surfupgradeNecklace);
	SDL_FreeSurface(surfupgradeNecklace);
	//Arrow
	SDL_Surface* surfArrow = IMG_Load("sprites\\menu\\arrow.png");
	SDL_Texture* textArrow = SDL_CreateTextureFromSurface(ren, surfArrow);
	SDL_FreeSurface(surfArrow);
	//
	TTF_Font* statItemsFont = TTF_OpenFont("fonts\\BAUHS93.TTF", 75);
	char stats[100] = "stats";
	SDL_Surface* surfStatItems = TTF_RenderText_Blended(statItemsFont, stats, { 255, 255, 255, 255 });
	SDL_Texture* textStatItemsText = SDL_CreateTextureFromSurface(ren, surfStatItems);
	SDL_Rect size = { 0, 0, surfStatItems->w, surfStatItems->h };
	int xPoint = 100, yPoint = 50;
	SDL_Rect statsRect = { xPoint, yPoint, 55, 60 };
	SDL_FreeSurface(surfStatItems);
#pragma endregion
	int upgrade = 1;
	int xArrow = 40, yArrow = 245;
	int pointer = 1;
	const Uint8* arrowState = SDL_GetKeyboardState(NULL);
	SDL_Rect srcrectArrow = { 0, 0, 100, 140 };
	SDL_Rect dstrectArrow;
	SDL_Event ev;
	SDL_PollEvent(&ev);
	dstrectArrow = { xArrow, yArrow, 75, 75 };
#pragma region Arrow
	if (levelNecklace == 0) {
		xArrow = 10, yArrow = 240;
		dstrectArrow = { xArrow, yArrow, 75, 75 };
	}
	if (levelNecklace == 1) {
		xArrow = 290, yArrow = 240;
		dstrectArrow = { xArrow, yArrow, 75, 75 };
	}
	if (levelNecklace == 2) {
		xArrow = 570, yArrow = 240;
		dstrectArrow = { xArrow, yArrow, 75, 75 };
	}
	if (levelNecklace == 3) {
		xArrow = 850, yArrow = 240;
		dstrectArrow = { xArrow, yArrow, 75, 75 };
	}
	if (levelNecklace == 4) {
		xArrow = 440, yArrow = 405;
		dstrectArrow = { xArrow, yArrow, 75, 75 };
	}
	if (levelNecklace == 5) {
		xArrow = 440, yArrow = 405;
		dstrectArrow = { xArrow, yArrow, 75, 75 };
	}
#pragma endregion
	
	while (upgrade == 1) {
		while (SDL_PollEvent(&ev) != NULL) {
			isPressed = pressedEnter();
			if (arrowState[SDL_SCANCODE_ESCAPE]) {
				SDL_DestroyTexture(textupgradeNecklace);
				SDL_DestroyTexture(textArrow);
				return;
			}
			if (levelNecklace == 0 and upgrade == 1 and arrowState[SDL_SCANCODE_RETURN] and isPressed) {
				if (upgrade == 1 and hero.Gold >= itemUpgrade.LVL1) {
					hero.maxMana -= 10;
					hero.necklace += 10;
					hero.maxMana += hero.necklace;
					hero.Mana = hero.maxMana;
					upgrade = 0;
					levelNecklace = 1;
					hero.Gold -= itemUpgrade.LVL1;
				}
				if (upgrade == 1 and hero.Gold < itemUpgrade.LVL1) {
					printf("У вас не достаточно денег\n");
					upgrade = 0;
				}
				
			}
			if (levelNecklace == 1 and upgrade == 1 and arrowState[SDL_SCANCODE_RETURN] and isPressed) {
				if (upgrade == 1 and hero.Gold >= itemUpgrade.LVL2) {
					hero.maxMana -= 10;
					hero.necklace += 10;
					hero.maxMana += hero.necklace;
					hero.Mana = hero.maxMana; 
					upgrade = 0;
					levelNecklace = 2;
					hero.Gold -= itemUpgrade.LVL2;
				}
				if (upgrade == 1 and hero.Gold < itemUpgrade.LVL2) {
					printf("У вас не достаточно денег\n");
					upgrade = 0;
				}
				
			}
			if (levelNecklace == 2 and upgrade == 1 and arrowState[SDL_SCANCODE_RETURN] and isPressed) {
				if (upgrade == 1 and hero.Gold >= itemUpgrade.LVL3) {
					hero.maxMana -= 10;
					hero.necklace += 10;
					hero.maxMana += hero.necklace;
					hero.Mana = hero.maxMana; 
					upgrade = 0;
					levelNecklace = 3;
					hero.Gold -= itemUpgrade.LVL3;
				}
				if (upgrade == 1 and hero.Gold < itemUpgrade.LVL3) {
					printf("У вас не достаточно денег\n");
					upgrade = 0;
				}
				
			}
			if (levelNecklace == 3 and upgrade == 1 and arrowState[SDL_SCANCODE_RETURN] and isPressed) {
				if (upgrade == 1 and hero.Gold >= itemUpgrade.LVL4) {
					hero.maxMana -= 10;
					hero.necklace += 10;
					hero.maxMana += hero.necklace;
					hero.Mana = hero.maxMana; 
					upgrade = 0;
					levelNecklace = 4;
					hero.Gold -= itemUpgrade.LVL4;
				}
				if (upgrade == 1 and hero.Gold < itemUpgrade.LVL4) {
					printf("У вас не достаточно денег\n");
					upgrade = 0;
				}
				
			}
			if (levelNecklace == 4 and upgrade == 1 and arrowState[SDL_SCANCODE_RETURN] and isPressed) {
				if (upgrade == 1 and hero.Gold >= itemUpgrade.LVL5) {
					hero.maxMana -= 10;
					hero.necklace += 10;
					hero.maxMana += hero.necklace;
					hero.Mana = hero.maxMana; 
					upgrade = 0;
					levelNecklace = 5;
					hero.Gold -= itemUpgrade.LVL5;
				}
				if (upgrade == 1 and hero.Gold < itemUpgrade.LVL5) {
					printf("У вас не достаточно денег\n");
					upgrade = 0;
				}
				
			}
			if (levelNecklace == 5 and upgrade == 1 and arrowState[SDL_SCANCODE_RETURN] and isPressed) {
				printf("У вас максимальный уровень ожерелья\nВам больше нечего прокачивать\n");
				upgrade = 0;
			}
		}
		SDL_SetRenderDrawColor(ren, 200, 200, 200, 0);
		SDL_RenderClear(ren);
		SDL_RenderCopy(ren, textupgradeNecklace, NULL, NULL);

		xPoint = 100, yPoint = 50;
		statsRect = { xPoint, yPoint, 55, 60 };
		sprintf_s(stats, "%d", hero.necklace);
		surfStatItems = TTF_RenderText_Blended(statItemsFont, stats, { 255, 255, 255, 255 });
		size = { 0, 0, surfStatItems->w, surfStatItems->h };
		textStatItemsText = SDL_CreateTextureFromSurface(ren, surfStatItems);
		SDL_RenderCopy(ren, textStatItemsText, &size, &statsRect);
		SDL_FreeSurface(surfStatItems);
		SDL_DestroyTexture(textStatItemsText);

		SDL_RenderCopy(ren, textArrow, &srcrectArrow, &dstrectArrow);
		SDL_RenderPresent(ren);
	}
	
	SDL_DestroyTexture(textArrow);
	SDL_DestroyTexture(textStatItemsText);
	SDL_DestroyTexture(textupgradeNecklace);

	TTF_CloseFont(statItemsFont);

	isPressed = 0;
}

//int main() {
//	system("chcp 1251");
//	upgradeItems();
//}