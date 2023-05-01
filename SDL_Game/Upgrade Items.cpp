#include "Models.h"
#include <iostream>
#include <SDL.h>
#include <SDL_image.h>

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
	int xArrow = 40, yArrow = 245;
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
		SDL_Delay(7);

		while (SDL_PollEvent(&ev) != NULL) {
			switch (ev.type) {
			case SDL_KEYDOWN:
				switch (ev.key.keysym.scancode) {
				case SDL_SCANCODE_LEFT:
					if (pointer != 1) {
						xArrow -= 300;
						pointer--;
					}
					break;
				case SDL_SCANCODE_A:
					if (pointer != 1) {
						xArrow -= 300;
						pointer--;
					}
					break;
				case SDL_SCANCODE_RIGHT:
					if (pointer != 3) {
						xArrow += 300;
						pointer++;
					}
					break;
				case SDL_SCANCODE_D:
					if (pointer != 3) {
						xArrow += 300;
						pointer++;
					}
					break;
				case SDL_SCANCODE_ESCAPE:
					return;
					break;
				}

			}

		}

		if (pointer == 1 and arrowState[SDL_SCANCODE_RETURN]) choiche = 1;
		if (pointer == 2 and arrowState[SDL_SCANCODE_RETURN]) choiche = 2;
		if (pointer == 3 and arrowState[SDL_SCANCODE_RETURN]) choiche = 3;

	}

	SDL_DestroyTexture(textchoiceItem);
	SDL_DestroyTexture(textArrow);

	if (choiche == 1) upgradeWeapon(ren);
	if (choiche == 2) upgradeArmor(ren);
	if (choiche == 3) upgradeNecklace(ren);
}

void upgradeWeapon(SDL_Renderer* ren) {
	system("chcp 1251");
	SDL_Delay(300);
#pragma region Texture
	//Level up
	SDL_Surface* surfupgradeWeapon = IMG_Load("sprites\\menu\\upgradeWeapon.png");
	SDL_Texture* textupgradeWeapon = SDL_CreateTextureFromSurface(ren, surfupgradeWeapon);
	SDL_FreeSurface(surfupgradeWeapon);
	//Arrow
	SDL_Surface* surfArrow = IMG_Load("sprites\\menu\\arrow.png");
	SDL_Texture* textArrow = SDL_CreateTextureFromSurface(ren, surfArrow);
	SDL_FreeSurface(surfArrow);
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
		if (levelWeapon == 0) {
			xArrow = 10, yArrow = 200;
			dstrectArrow = { xArrow, yArrow, 75, 75 };
		}
		if (levelWeapon == 1) {
			xArrow = 230, yArrow = 200;
			dstrectArrow = { xArrow, yArrow, 75, 75 };
		}
		if (levelWeapon == 2) {
			xArrow = 450, yArrow = 200;
			dstrectArrow = { xArrow, yArrow, 75, 75 };
		}
		if (levelWeapon == 3) {
			xArrow = 670, yArrow = 200;
			dstrectArrow = { xArrow, yArrow, 75, 75 };
		}
		if (levelWeapon == 4) {
			xArrow = 320, yArrow = 340;
			dstrectArrow = { xArrow, yArrow, 75, 75 };
		}
		if (levelWeapon == 5) {
			xArrow = 320, yArrow = 340;
			dstrectArrow = { xArrow, yArrow, 75, 75 };
		}
#pragma endregion
		SDL_SetRenderDrawColor(ren, 200, 200, 200, 0);
		SDL_RenderClear(ren);
		SDL_RenderCopy(ren, textupgradeWeapon, NULL, NULL);
		SDL_RenderCopy(ren, textArrow, &srcrectArrow, &dstrectArrow);
		SDL_RenderPresent(ren);
		SDL_Delay(7);
		while (upgrade == 1) {
			while (SDL_PollEvent(&ev) != NULL) {
				if (arrowState[SDL_SCANCODE_ESCAPE]) return;
				if (levelWeapon == 0 and upgrade == 1 and arrowState[SDL_SCANCODE_RETURN]) {
					if (upgrade == 1 and hero.Gold >= itemUpgrade.LVL1) {
						hero.weapon += 10;
						upgrade = 0;
						levelWeapon = 1;
						printf("Ты прокачался 1\n");
					}
					if (upgrade == 1 and hero.Gold < itemUpgrade.LVL1) {
						printf("У вас не достаточно денег\n");
						upgrade = 0;
					}
					if (upgrade == 0) return;
				}
				if (levelWeapon == 1 and upgrade == 1 and arrowState[SDL_SCANCODE_RETURN]) {
					if (upgrade == 1 and hero.Gold >= itemUpgrade.LVL2) {
						hero.weapon += 10;
						upgrade = 0;
						levelWeapon = 2;
						printf("Ты прокачался 2\n");
					}
					if (upgrade == 1 and hero.Gold < itemUpgrade.LVL2) {
						printf("У вас не достаточно денег\n");
						upgrade = 0;
					}
					if (upgrade == 0) return;
				}
				if (levelWeapon == 2 and upgrade == 1 and arrowState[SDL_SCANCODE_RETURN]) {
					if (upgrade == 1 and hero.Gold >= itemUpgrade.LVL3) {
						hero.weapon += 10;
						upgrade = 0;
						levelWeapon = 3;
					}
					if (upgrade == 1 and hero.Gold < itemUpgrade.LVL3) {
						printf("У вас не достаточно денег\n");
						upgrade = 0;
					}
					if (upgrade == 0) return;
				}
				if (levelWeapon == 3 and upgrade == 1 and arrowState[SDL_SCANCODE_RETURN]) {
					if (upgrade == 1 and hero.Gold >= itemUpgrade.LVL4) {
						hero.weapon += 10;
						upgrade = 0;
						levelWeapon = 4;
					}
					if (upgrade == 1 and hero.Gold < itemUpgrade.LVL4) {
						printf("У вас не достаточно денег\n");
						upgrade = 0;
					}
					if (upgrade == 0) return;
				}
				if (levelWeapon == 4 and upgrade == 1 and arrowState[SDL_SCANCODE_RETURN]) {
					if (upgrade == 1 and hero.Gold >= itemUpgrade.LVL5) {
						hero.weapon += 10;
						upgrade = 0;
						levelWeapon = 5;
					}
					if (upgrade == 1 and hero.Gold < itemUpgrade.LVL5) {
						printf("У вас не достаточно денег\n");
						upgrade = 0;
					}
					if (upgrade == 0) return;
				}
				if (levelWeapon == 5 and upgrade == 1 and arrowState[SDL_SCANCODE_RETURN]) {
					printf("У вас максимальный уровень оружия\nВам больше нечего прокачивать\n");
					upgrade = 0;
				}
			}
		}
		if (upgrade == 0) {
			SDL_DestroyTexture(textupgradeWeapon);
			SDL_DestroyTexture(textArrow);
			return;
		}
}

void upgradeArmor(SDL_Renderer* ren) {
	system("chcp 1251");
	SDL_Delay(300);
#pragma region Texture
	//Level up
	SDL_Surface* surfupgradeArmor = IMG_Load("sprites\\menu\\upgradeArmor.png");
	SDL_Texture* textupgradeArmor = SDL_CreateTextureFromSurface(ren, surfupgradeArmor);
	SDL_FreeSurface(surfupgradeArmor);
	//Arrow
	SDL_Surface* surfArrow = IMG_Load("sprites\\menu\\arrow.png");
	SDL_Texture* textArrow = SDL_CreateTextureFromSurface(ren, surfArrow);
	SDL_FreeSurface(surfArrow);
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
		xArrow = 10, yArrow = 200;
		dstrectArrow = { xArrow, yArrow, 75, 75 };
	}
	if (levelArmor == 1) {
		xArrow = 230, yArrow = 200;
		dstrectArrow = { xArrow, yArrow, 75, 75 };
	}
	if (levelArmor == 2) {
		xArrow = 450, yArrow = 200;
		dstrectArrow = { xArrow, yArrow, 75, 75 };
	}
	if (levelArmor == 3) {
		xArrow = 670, yArrow = 200;
		dstrectArrow = { xArrow, yArrow, 75, 75 };
	}
	if (levelArmor == 4) {
		xArrow = 320, yArrow = 340;
		dstrectArrow = { xArrow, yArrow, 75, 75 };
	}
	if (levelArmor == 5) {
		xArrow = 320, yArrow = 340;
		dstrectArrow = { xArrow, yArrow, 75, 75 };
	}
#pragma endregion
	SDL_SetRenderDrawColor(ren, 200, 200, 200, 0);
	SDL_RenderClear(ren);
	SDL_RenderCopy(ren, textupgradeArmor, NULL, NULL);
	SDL_RenderCopy(ren, textArrow, &srcrectArrow, &dstrectArrow);
	SDL_RenderPresent(ren);
	SDL_Delay(7);
	while (upgrade == 1) {
		while (SDL_PollEvent(&ev) != NULL) {
			if (arrowState[SDL_SCANCODE_ESCAPE]) return;
			if (levelArmor == 0 and upgrade == 1 and arrowState[SDL_SCANCODE_RETURN]) {
				if (upgrade == 1 and hero.Gold >= itemUpgrade.LVL1) {
					hero.armorHealth += 30;
					hero.armorDefense += 5;
					upgrade = 0;
					levelArmor = 1;
				}
				if (upgrade == 1 and hero.Gold < itemUpgrade.LVL1) {
					printf("У вас не достаточно денег\n");
					upgrade = 0;
				}
				if (upgrade == 0) return;
			}
			if (levelArmor == 1 and upgrade == 1 and arrowState[SDL_SCANCODE_RETURN]) {
				if (upgrade == 1 and hero.Gold >= itemUpgrade.LVL2) {
					hero.armorHealth += 30;
					hero.armorDefense += 5;
					upgrade = 0;
					levelArmor = 2;
				}
				if (upgrade == 1 and hero.Gold < itemUpgrade.LVL2) {
					printf("У вас не достаточно денег\n");
					upgrade = 0;
				}
				if (upgrade == 0) return;
			}
			if (levelArmor == 2 and upgrade == 1 and arrowState[SDL_SCANCODE_RETURN]) {
				if (upgrade == 1 and hero.Gold >= itemUpgrade.LVL3) {
					hero.armorHealth += 30;
					hero.armorDefense += 5;
					upgrade = 0;
					levelArmor = 3;
				}
				if (upgrade == 1 and hero.Gold < itemUpgrade.LVL3) {
					printf("У вас не достаточно денег\n");
					upgrade = 0;
				}
				if (upgrade == 0) return;
			}
			if (levelArmor == 3 and upgrade == 1 and arrowState[SDL_SCANCODE_RETURN]) {
				if (upgrade == 1 and hero.Gold >= itemUpgrade.LVL4) {
					hero.armorHealth += 30;
					hero.armorDefense += 5;
					upgrade = 0;
					levelArmor = 4;
				}
				if (upgrade == 1 and hero.Gold < itemUpgrade.LVL4) {
					printf("У вас не достаточно денег\n");
					upgrade = 0;
				}
				if (upgrade == 0) return;
			}
			if (levelArmor == 4 and upgrade == 1 and arrowState[SDL_SCANCODE_RETURN]) {
				if (upgrade == 1 and hero.Gold >= itemUpgrade.LVL5) {
					hero.armorHealth += 30;
					hero.armorDefense += 5;
					upgrade = 0;
					levelArmor = 5;
				}
				if (upgrade == 1 and hero.Gold < itemUpgrade.LVL5) {
					printf("У вас не достаточно денег\n");
					upgrade = 0;
				}
				if (upgrade == 0) return;
			}
			if (levelArmor == 5 and upgrade == 1 and arrowState[SDL_SCANCODE_RETURN]) {
				printf("У вас максимальный уровень брони\nВам больше нечего прокачивать\n");
				upgrade = 0;
			}
		}
	}
	if (upgrade == 0) {
		SDL_DestroyTexture(textupgradeArmor);
		SDL_DestroyTexture(textArrow);
		return;
	}
}

void upgradeNecklace(SDL_Renderer* ren) {
	system("chcp 1251");
	SDL_Delay(300);
#pragma region Texture
	//Level up
	SDL_Surface* surfupgradeNecklace = IMG_Load("sprites\\menu\\upgradeNecklace.png");
	SDL_Texture* textupgradeNecklace = SDL_CreateTextureFromSurface(ren, surfupgradeNecklace);
	SDL_FreeSurface(surfupgradeNecklace);
	//Arrow
	SDL_Surface* surfArrow = IMG_Load("sprites\\menu\\arrow.png");
	SDL_Texture* textArrow = SDL_CreateTextureFromSurface(ren, surfArrow);
	SDL_FreeSurface(surfArrow);
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
		xArrow = 10, yArrow = 200;
		dstrectArrow = { xArrow, yArrow, 75, 75 };
	}
	if (levelNecklace == 1) {
		xArrow = 230, yArrow = 200;
		dstrectArrow = { xArrow, yArrow, 75, 75 };
	}
	if (levelNecklace == 2) {
		xArrow = 450, yArrow = 200;
		dstrectArrow = { xArrow, yArrow, 75, 75 };
	}
	if (levelNecklace == 3) {
		xArrow = 670, yArrow = 200;
		dstrectArrow = { xArrow, yArrow, 75, 75 };
	}
	if (levelNecklace == 4) {
		xArrow = 320, yArrow = 340;
		dstrectArrow = { xArrow, yArrow, 75, 75 };
	}
	if (levelNecklace == 5) {
		xArrow = 320, yArrow = 340;
		dstrectArrow = { xArrow, yArrow, 75, 75 };
	}
#pragma endregion
	SDL_SetRenderDrawColor(ren, 200, 200, 200, 0);
	SDL_RenderClear(ren);
	SDL_RenderCopy(ren, textupgradeNecklace, NULL, NULL);
	SDL_RenderCopy(ren, textArrow, &srcrectArrow, &dstrectArrow);
	SDL_RenderPresent(ren);
	SDL_Delay(7);
	while (upgrade == 1) {
		while (SDL_PollEvent(&ev) != NULL) {
			if (arrowState[SDL_SCANCODE_ESCAPE]) return;
			if (levelNecklace == 0 and upgrade == 1 and arrowState[SDL_SCANCODE_RETURN]) {
				if (upgrade == 1 and hero.Gold >= itemUpgrade.LVL1) {
					hero.necklace += 10;
					upgrade = 0;
					levelNecklace = 1;
				}
				if (upgrade == 1 and hero.Gold < itemUpgrade.LVL1) {
					printf("У вас не достаточно денег\n");
					upgrade = 0;
				}
				if (upgrade == 0) return;
			}
			if (levelNecklace == 1 and upgrade == 1 and arrowState[SDL_SCANCODE_RETURN]) {
				if (upgrade == 1 and hero.Gold >= itemUpgrade.LVL2) {
					hero.necklace += 10;
					upgrade = 0;
					levelNecklace = 2;
				}
				if (upgrade == 1 and hero.Gold < itemUpgrade.LVL2) {
					printf("У вас не достаточно денег\n");
					upgrade = 0;
				}
				if (upgrade == 0) return;
			}
			if (levelNecklace == 2 and upgrade == 1 and arrowState[SDL_SCANCODE_RETURN]) {
				if (upgrade == 1 and hero.Gold >= itemUpgrade.LVL3) {
					hero.necklace += 10;
					upgrade = 0;
					levelNecklace = 3;
				}
				if (upgrade == 1 and hero.Gold < itemUpgrade.LVL3) {
					printf("У вас не достаточно денег\n");
					upgrade = 0;
				}
				if (upgrade == 0) return;
			}
			if (levelNecklace == 3 and upgrade == 1 and arrowState[SDL_SCANCODE_RETURN]) {
				if (upgrade == 1 and hero.Gold >= itemUpgrade.LVL4) {
					hero.necklace += 10;
					upgrade = 0;
					levelNecklace = 4;
				}
				if (upgrade == 1 and hero.Gold < itemUpgrade.LVL4) {
					printf("У вас не достаточно денег\n");
					upgrade = 0;
				}
				if (upgrade == 0) return;
			}
			if (levelNecklace == 4 and upgrade == 1 and arrowState[SDL_SCANCODE_RETURN]) {
				if (upgrade == 1 and hero.Gold >= itemUpgrade.LVL5) {
					hero.necklace += 10;
					upgrade = 0;
					levelNecklace = 5;
				}
				if (upgrade == 1 and hero.Gold < itemUpgrade.LVL5) {
					printf("У вас не достаточно денег\n");
					upgrade = 0;
				}
				if (upgrade == 0) return;
			}
			if (levelNecklace == 5 and upgrade == 1 and arrowState[SDL_SCANCODE_RETURN]) {
				printf("У вас максимальный уровень ожерелья\nВам больше нечего прокачивать\n");
				upgrade = 0;
			}
		}
	}
	if (upgrade == 0) {
		SDL_DestroyTexture(textupgradeNecklace);
		SDL_DestroyTexture(textArrow);
		return;
	}
}

//int main() {
//	system("chcp 1251");
//	upgradeItems();
//}