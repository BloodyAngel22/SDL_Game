#define _CRT_SECURE_NO_WARNINGS
#include <SDL.h>
#include <SDL_image.h>
#include <SDL_ttf.h>
#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include "Leveling.h"
#include "Battle.h"
#include "Models.h"
#include "SDL_general.h"
#include "Upgrade Items.h"
#include "Save.h"
#include "Quest.h"
#include "Puzzle.h"
#include "Minigames.h"
#define  EnemyUp 1
#define  EnemyRight 2
#define  EnemyDown 3
#define  EnemyLeft 4


void init(); void de_init(int error); void choiceClass();

int classHero = 0;
float win_width = 1280, win_height = 720;
SDL_Window* win = 0;
SDL_Renderer* ren = 0;
int Xcoordinate, Ycoordinate;
extern int checkChest = 0;
extern int checkChest2 = 0;

void init() {

	if (SDL_Init(SDL_INIT_VIDEO) != 0) {
		printf("Couldn't init sdl, Error %s", SDL_GetError());
		system("pause");
		de_init(1);
	}

	int res;
	if ((res = IMG_Init(IMG_INIT_PNG | IMG_INIT_JPG)) == 0) {
		printf("Couldn't init img");
		de_init(1);
	}
	if (res & IMG_INIT_PNG) printf("png init\n"); else printf("couldn't init png\n");
	if (res & IMG_INIT_JPG) printf("jpg init\n"); else printf("couldn't init jpg\n");

	if (TTF_Init()) {
		printf("Couldn't init img");
		de_init(1);
	}

	win = SDL_CreateWindow("Window", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED,
		win_width, win_height, SDL_WINDOW_SHOWN  /*SDL_WINDOW_FULLSCREEN*/);
	if (win == NULL) {
		printf("window couldn't init %s", SDL_GetError());
		system("pause");
		SDL_Quit();
		de_init(1);
	}
	ren = SDL_CreateRenderer(win, 0, SDL_RENDERER_ACCELERATED);
	if (ren == NULL) {
		printf("renderer couldn't init %s", SDL_GetError());
		system("pause");
		SDL_Quit();
		de_init(1);
	}
}

void de_init(int error) {
	if (ren != 0) SDL_DestroyRenderer(ren);
	if (win != 0) SDL_DestroyWindow(win);
	TTF_Quit();
	IMG_Quit();
	SDL_Quit();
	exit(error);
}

void streing(float& EnemyX, float& EnemyY, int& i, int& flag) {
	int limiter = 100;
	float speedEnemy = 0.7;
	if (i < limiter and flag == EnemyUp) {
		EnemyY -= speedEnemy;
		i++;
		if (i == limiter) {
			flag = EnemyRight;
			i = 0;
		}
	}
	if (i < limiter and flag == EnemyRight) {
		EnemyX += speedEnemy;
		i++;

		if (i == limiter) {
			flag = EnemyDown;
			i = 0;
		}
	}
	if (i < limiter and flag == EnemyDown) {
		EnemyY += speedEnemy;
		i++;

		if (i == limiter) {
			flag = EnemyLeft;
			i = 0;
		}
	}
	if (i < limiter and flag == EnemyLeft) {
		EnemyX -= speedEnemy;
		i++;

		if (i == limiter) {
			flag = EnemyUp;
			i = 0;
		}
	}
}

void battle(float& EnemyX, float& EnemyY, bool& switcher, int enemy) {
	switcher = true;
	while (switcher == true) {
		MenuBattle(ren, enemy);
		if (livedEnemies < 1 and switcher) {
			EnemyX = -300; EnemyY = -300;
			switcher = false;
		}
	}
}

bool checkCollision(SDL_Rect a, SDL_FRect b)
{
	int leftA, leftB;
	int rightA, rightB;
	int topA, topB;
	int bottomA, bottomB;

	leftA = a.x;
	rightA = a.x + a.w;
	topA = a.y;
	bottomA = a.y + a.h;

	leftB = b.x;
	rightB = b.x + b.w;
	topB = b.y;
	bottomB = b.y + b.h;

	if (bottomA <= topB) {
		return false;
	}
	if (topA >= bottomB) {
		return false;
	}
	if (rightA <= leftB) {
		return false;
	}
	if (leftA >= rightB) {
		return false;
	}

	return true;
}

void main_menu() {
	#pragma region Texture
	//Main menu
	SDL_Surface* surfMainMenu = IMG_Load("sprites\\menu\\mainMenu.png");
	SDL_Texture* textMainMenu = SDL_CreateTextureFromSurface(ren, surfMainMenu);
	SDL_FreeSurface(surfMainMenu);
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
	int mainMenu = 0;
	SDL_Event ev;
	SDL_PollEvent(&ev);

	int xArrow = 320, yArrow = 160;
	int pointer = 1;
	const Uint8* arrowState = SDL_GetKeyboardState(NULL);
	SDL_Rect srcrectArrow = { 0, 0, 100, 140 };
	SDL_Rect dstrectArrow;
	int flag = 0;
	while (mainMenu == 0) {
		SDL_SetRenderDrawColor(ren, 200, 200, 200, 0);
		SDL_RenderClear(ren);
		SDL_RenderCopy(ren, textMainMenu, NULL, NULL);
		dstrectArrow = { xArrow, yArrow, 75, 75 };
		while (SDL_PollEvent(&ev) != NULL) {
			switch (ev.type) {
			case SDL_KEYDOWN:
				switch (ev.key.keysym.scancode) {
				case SDL_SCANCODE_ESCAPE:
					de_init(1);
					break;
				case SDL_SCANCODE_UP:
					if (pointer != 1) {
						yArrow -= 110;
						pointer--;
					}
					break;
				case SDL_SCANCODE_W:
					if (pointer != 1) {
						yArrow -= 110;
						pointer--;
					}
					break;
				case SDL_SCANCODE_DOWN:
					if (pointer != 4) {
						yArrow += 110;
						pointer++;
					}
						break;
				case SDL_SCANCODE_S:
					if (pointer != 4) {
						yArrow += 110;
						pointer++;
						break;
					}
				}
			}
			isPressed = pressedEnter();
		}
		if (pointer == 1 and arrowState[SDL_SCANCODE_RETURN] and isPressed) {
			SDL_DestroyTexture(textMainMenu);
			SDL_DestroyTexture(textArrow);
			if (flag == 1) {
				SDL_FreeSurface(surfStatItems);
				SDL_DestroyTexture(textStatItemsText);
				TTF_CloseFont(statItemsFont);
			}
			isPressed = 0;
			choiceClass();
			return;
		}
		if (pointer == 2 and arrowState[SDL_SCANCODE_RETURN] and isPressed) {
			isPressed = 0;
			SDL_DestroyTexture(textMainMenu);
			SDL_DestroyTexture(textArrow);
			if (flag == 1) {
				SDL_FreeSurface(surfStatItems);
				SDL_DestroyTexture(textStatItemsText);
				TTF_CloseFont(statItemsFont);
			}
			print_in_file(ren);
			return;
		}
		if (pointer == 3 and arrowState[SDL_SCANCODE_RETURN] and isPressed) {
			if (flag == 0)
				flag = 1;
		}
		if (pointer == 4 and arrowState[SDL_SCANCODE_RETURN] and isPressed) {
			SDL_DestroyTexture(textMainMenu);
			SDL_DestroyTexture(textArrow);
			de_init(1);
		}
		isPressed = 0;
		if (flag == 1) {
			xPoint = 750, yPoint = 390;
			statsRect = { xPoint, yPoint, 200, 60 };
			sprintf_s(stats, "Zhigalkin Maxim");
			surfStatItems = TTF_RenderText_Blended(statItemsFont, stats, { 255, 255, 255, 255 });
			size = { 0, 0, surfStatItems->w, surfStatItems->h };
			textStatItemsText = SDL_CreateTextureFromSurface(ren, surfStatItems);
			SDL_RenderCopy(ren, textStatItemsText, &size, &statsRect);
			SDL_FreeSurface(surfStatItems);
			SDL_DestroyTexture(textStatItemsText);
		}
		SDL_RenderCopy(ren, textArrow, &srcrectArrow, &dstrectArrow);
		SDL_RenderPresent(ren);
	}


}

void menu() {
#pragma region Texture
	//Main menu
	SDL_Surface* surfMenu = IMG_Load("sprites\\menu\\menu.png");
	SDL_Texture* textMenu = SDL_CreateTextureFromSurface(ren, surfMenu);
	SDL_FreeSurface(surfMenu);
	//Arrow
	SDL_Surface* surfArrow = IMG_Load("sprites\\menu\\arrow.png");
	SDL_Texture* textArrow = SDL_CreateTextureFromSurface(ren, surfArrow);
	SDL_FreeSurface(surfArrow);
#pragma endregion
	int menu = 0;
	SDL_Event ev;
	SDL_PollEvent(&ev);
	int xArrow = 370, yArrow = 180;
	int pointer = 1;
	const Uint8* arrowState = SDL_GetKeyboardState(NULL);
	SDL_Rect srcrectArrow = { 0, 0, 100, 140 };
	SDL_Rect dstrectArrow;
	while (menu == 0) {
		dstrectArrow = { xArrow, yArrow, 75, 75 };
		SDL_SetRenderDrawColor(ren, 200, 200, 200, 0);
		SDL_RenderClear(ren);
		SDL_RenderCopy(ren, textMenu, NULL, NULL);
		SDL_RenderCopy(ren, textArrow, &srcrectArrow, &dstrectArrow);
		SDL_RenderPresent(ren);
		while (SDL_PollEvent(&ev) != NULL) {
			/*isPressedEscape = pressedEscape();
			if (isPressedEscape and arrowState[SDL_SCANCODE_ESCAPE]) {
				SDL_DestroyTexture(textMenu);
				SDL_DestroyTexture(textArrow);
				return;
			}*/
			switch (ev.type) {
			case SDL_KEYDOWN:
				switch (ev.key.keysym.scancode) {
				case SDL_SCANCODE_UP:
					if (pointer != 1) {
						yArrow -= 145;
						pointer--;
					}
					break;
				case SDL_SCANCODE_W:
					if (pointer != 1) {
						yArrow -= 145;
						pointer--;
					}
					break;
				case SDL_SCANCODE_DOWN:
					if (pointer != 3) {
						yArrow += 145;
						pointer++;
					}
					break;
				case SDL_SCANCODE_S:
					if (pointer != 3) {
						yArrow += 145;
						pointer++;
						break;
					}
				}
			}
			isPressed = pressedEnter();
		}

		if (pointer == 1 and arrowState[SDL_SCANCODE_RETURN] and isPressed) {
			SDL_DestroyTexture(textMenu);
			SDL_DestroyTexture(textArrow);
			return; //continue
		}
		if (pointer == 2 and arrowState[SDL_SCANCODE_RETURN] and isPressed) {
			SDL_DestroyTexture(textMenu);
			SDL_DestroyTexture(textArrow);
			save_in_file(ren);
			printf("You save a game\n");
			return; //save
		}
		if (pointer == 3 and arrowState[SDL_SCANCODE_RETURN] and isPressed) {
			SDL_DestroyTexture(textMenu);
			SDL_DestroyTexture(textArrow);
			de_init(1); //exit
		}

		isPressed = 0;
		isPressedEscape = 0;
	}
}

void choiceClass() {
#pragma region Texture
	//Main menu
	SDL_Surface* surfClass = IMG_Load("sprites\\menu\\class.png");
	SDL_Texture* textClass = SDL_CreateTextureFromSurface(ren, surfClass);
	SDL_FreeSurface(surfClass);
	//Arrow
	SDL_Surface* surfArrow = IMG_Load("sprites\\menu\\arrow.png");
	SDL_Texture* textArrow = SDL_CreateTextureFromSurface(ren, surfArrow);
	SDL_FreeSurface(surfArrow);
#pragma endregion
	int choice = 0;
	SDL_Event ev;
	SDL_PollEvent(&ev);
	int xArrow = 185, yArrow = 250;
	int pointer = 1;
	const Uint8* arrowState = SDL_GetKeyboardState(NULL);
	SDL_Rect srcrectArrow = { 0, 0, 100, 140 };
	SDL_Rect dstrectArrow;
	while (choice == 0) {
		dstrectArrow = { xArrow, yArrow, 75, 75 };
		SDL_SetRenderDrawColor(ren, 200, 200, 200, 0);
		SDL_RenderClear(ren);
		SDL_RenderCopy(ren, textClass, NULL, NULL);
		SDL_RenderCopy(ren, textArrow, &srcrectArrow, &dstrectArrow);
		SDL_RenderPresent(ren);
		while (SDL_PollEvent(&ev) != NULL) {
			switch (ev.type) {
			case SDL_KEYDOWN:
				switch (ev.key.keysym.scancode) {
				case SDL_SCANCODE_ESCAPE:
					de_init(1);
					break;
				case SDL_SCANCODE_LEFT:
					if (pointer != 1) {
						xArrow -= 500;
						pointer--;
					}
					break;
				case SDL_SCANCODE_A:
					if (pointer != 1) {
						xArrow -= 500;
						pointer--;
					}
					break;
				case SDL_SCANCODE_RIGHT:
					if (pointer != 2) {
						xArrow += 500;
						pointer++;
					}
					break;
				case SDL_SCANCODE_D:
					if (pointer != 2) {
						xArrow += 500;
						pointer++;
						break;
					}
				}
			}
			isPressed = pressedEnter();
		}
		if (pointer == 1 and arrowState[SDL_SCANCODE_RETURN] and isPressed) {
			hero.Attack = warrior.Attack, hero.Health = warrior.Health, hero.Defense = warrior.Defense, hero.Gold = warrior.Gold, hero.Mana = warrior.Mana;
			hero.maxAttack = warrior.maxAttack, hero.maxHealth = warrior.maxHealth, hero.maxMana = warrior.maxMana;
			SDL_DestroyTexture(textArrow);
			SDL_DestroyTexture(textClass);
			classHero = 1;
			return;
		}
		if (pointer == 2 and arrowState[SDL_SCANCODE_RETURN] and isPressed) {
			hero.Attack = mage.Attack, hero.Health = mage.Health, hero.Defense = mage.Defense, hero.Gold = mage.Gold, hero.Mana = mage.Mana;
			hero.maxAttack = mage.maxAttack, hero.maxHealth = mage.maxHealth, hero.maxMana = mage.maxMana;
			hero.pointsLevel = mage.pointsLevel;
			SDL_DestroyTexture(textArrow);
			SDL_DestroyTexture(textClass);
			classHero = 2;
			return;
		}
		isPressed = 0;
	}
}

void wall(SDL_Rect a) {
	int leftA;
	int rightA;
	int topA;
	int bottomA;

	leftA = a.x;
	rightA = a.x + a.w;
	topA = a.y;
	bottomA = a.y + a.h;

	if (rightA > win_width)
		Xcoordinate-=4;
	if (leftA < 0)
		Xcoordinate+=4;
	if (bottomA > win_height)
		Ycoordinate-=4;
	if (topA < 0)
		Ycoordinate+=4;
}

int main(int argc, char* argv[]) {
	init();
	srand(time(NULL));
	bool winnerBat = false;
	bool winnerGoblin = false;
	bool winnerSlime = false;
	bool winnerWerewolf = false;
	bool winnerRat = false;
	bool isRunning = true;
	bool switcherBat = true;
	bool switcherGoblin = true;
	bool switcherSlime = true;
	bool switcherWerewolf = true;
	bool switcherRat = true;
	int pause = 0;
	int i = 0; int i2 = 0; int i3 = 0; int i4 = 0; int i5 = 0;
	int EnemyCharacteristics = 0;
	int startRespawn = 0;
	int endRespawn = 0;
	int flagEnemy1 = EnemyUp;
	int flagEnemy2 = EnemyDown;
	int flagEnemy3 = EnemyRight;
	int flagEnemy4 = EnemyLeft;
	int flagEnemy5 = EnemyDown;
	int flagCollision = 0;
	int shiftX = win_width / 2, shiftY = win_height / 2, Xsize = 40, Ysize = 40;
	Xcoordinate = shiftX - Xsize / 2, Ycoordinate = shiftY - Ysize / 2;
	//Position Enemy and FRects
	float BatX = 850, BatY = 550, XsizeEnemy = 75, YsizeEnemy = 75;
	float GoblinX = 320, GoblinY = 450;
	float SlimeX = 950, SlimeY = 100;
	float WerewolfX = 950, WerewolfY = 100;
	float RatX = 200, RatY = 450;
	SDL_FRect bat = { BatX, BatY, XsizeEnemy, YsizeEnemy };
	SDL_FRect goblin = { GoblinX, GoblinY, XsizeEnemy, YsizeEnemy };
	SDL_FRect slime = { SlimeX, SlimeY, XsizeEnemy, YsizeEnemy };
	SDL_FRect werewolf = { WerewolfX, WerewolfY, XsizeEnemy, YsizeEnemy };
	SDL_FRect rat = { RatX, RatY, XsizeEnemy, YsizeEnemy };
	//
	SDL_Event ev;
	bool UP, DOWN, RIGHT, LEFT;
	const Uint8* state = SDL_GetKeyboardState(NULL);
	UP = DOWN = RIGHT = LEFT = 0;
	Xcoordinate = shiftX - Xsize / 2, Ycoordinate = shiftY - Ysize / 2;
	SDL_PollEvent(&ev);

	float RuneSize = 60;
	//Water
	bool runeWater = 0;
	SDL_Rect dstrune = { 100, 100, RuneSize, RuneSize };
	SDL_Rect srcrune = { 60, 60, 190, 190 };
	SDL_FRect rune = { dstrune.x, dstrune.y, RuneSize, RuneSize };
	//Fire
	bool runeFire = 0;
	SDL_Rect dstrune2 = { 200, 100, RuneSize, RuneSize };
	SDL_Rect srcrune2 = { 430, 70, 190, 190 };
	SDL_FRect rune2 = { dstrune2.x, dstrune2.y, RuneSize, RuneSize };
	//Earth
	bool runeEarth = 0;
	SDL_Rect dstrune3 = { 400, 100, RuneSize, RuneSize };
	SDL_Rect srcrune3 = { 240, 60, 190, 190 };
	SDL_FRect rune3 = { dstrune3.x, dstrune3.y, RuneSize, RuneSize };

	#pragma region Texture
	//room1
	SDL_Surface* surfRoom = IMG_Load("sprites\\background\\part1.png");
	SDL_Texture* textRoom1 = SDL_CreateTextureFromSurface(ren, surfRoom);
	SDL_FreeSurface(surfRoom);

	SDL_Surface* surfRoom1Collision = IMG_Load("sprites\\background\\part1Collision.png");
	SDL_Texture* textRoom1Collision = SDL_CreateTextureFromSurface(ren, surfRoom1Collision);
	SDL_FreeSurface(surfRoom1Collision);
	//room2
	SDL_Surface* surfRoom2 = IMG_Load("sprites\\background\\part2.png");
	SDL_Texture* textRoom2 = SDL_CreateTextureFromSurface(ren, surfRoom2);
	SDL_FreeSurface(surfRoom2);

	SDL_Surface* surfRoom2Collision = IMG_Load("sprites\\background\\part2collision.png");
	SDL_Texture* textRoom2Collision = SDL_CreateTextureFromSurface(ren, surfRoom2Collision);
	SDL_FreeSurface(surfRoom2Collision);
	//room3
	SDL_Surface* surfRoom3 = IMG_Load("sprites\\background\\part3.png");
	SDL_Texture* textRoom3 = SDL_CreateTextureFromSurface(ren, surfRoom3);
	SDL_FreeSurface(surfRoom3);

	SDL_Surface* surfRoom3Collision = IMG_Load("sprites\\background\\part3Collision.png");
	SDL_Texture* textRoom3Collision = SDL_CreateTextureFromSurface(ren, surfRoom3Collision);
	SDL_FreeSurface(surfRoom3Collision);
	//room4
	SDL_Surface* surfRoom4 = IMG_Load("sprites\\background\\part4.png");
	SDL_Texture* textRoom4 = SDL_CreateTextureFromSurface(ren, surfRoom4);
	SDL_FreeSurface(surfRoom4);
	int row = 1, col = 1;
	int room = 1;
	// character 
	SDL_Surface* surfCharacter = IMG_Load("sprites\\character\\character.png");
	SDL_Texture* textCharacter = SDL_CreateTextureFromSurface(ren, surfCharacter);
	SDL_Rect player = { Xcoordinate, Ycoordinate, Xsize, Ysize };
	SDL_Rect legs = { Xcoordinate, Ycoordinate + 30, Xsize, 10 };
	player.w = player.h;
	SDL_FreeSurface(surfCharacter);
	//Bat
	SDL_Surface* surfBat = IMG_Load("sprites\\enemy\\bat.png");
	SDL_Texture* textBat = SDL_CreateTextureFromSurface(ren, surfBat);
	SDL_FreeSurface(surfBat);
	//Goblin
	SDL_Surface* surfGoblin = IMG_Load("sprites\\enemy\\goblin.png");
	SDL_Texture* textGoblin = SDL_CreateTextureFromSurface(ren, surfGoblin);
	SDL_FreeSurface(surfGoblin);
	//Slime
	SDL_Surface* surfSlime = IMG_Load("sprites\\enemy\\red_slime.png");
	SDL_Texture* textSlime = SDL_CreateTextureFromSurface(ren, surfSlime);
	SDL_FreeSurface(surfSlime);
	//Werewolf
	SDL_Surface* surfWerewolf = IMG_Load("sprites\\enemy\\werewolf.png");
	SDL_Texture* textWerewolf = SDL_CreateTextureFromSurface(ren, surfWerewolf);
	SDL_FreeSurface(surfWerewolf);
	//Rat
	SDL_Surface* surfRat = IMG_Load("sprites\\enemy\\rat.png");
	SDL_Texture* textRat = SDL_CreateTextureFromSurface(ren, surfRat);
	SDL_FreeSurface(surfRat);
	//
	SDL_Surface* surfRune = IMG_Load("sprites\\runes\\runes.png");
	SDL_Texture* textRune = SDL_CreateTextureFromSurface(ren, surfRune);
	SDL_FreeSurface(surfRune);
	//Portal
	SDL_Surface* surfPortal = IMG_Load("sprites\\portal\\mainPortal.png");
	SDL_Texture* textPortal = SDL_CreateTextureFromSurface(ren, surfPortal);
	SDL_FreeSurface(surfPortal);
	int portalSize = 80;
	//Portal1
	SDL_Rect dstPortal1 = { 0, 300, portalSize , portalSize };
	SDL_FRect Portal1 = { dstPortal1.x, dstPortal1.y, portalSize , portalSize };
	SDL_Rect srcPortal = { 0, 0, 29, 32 };
	//Portal2
	SDL_Rect dstPortal2 = { 1200, 300, portalSize , portalSize };
	SDL_FRect Portal2 = { dstPortal2.x, dstPortal2.y, portalSize , portalSize };
	//Portal3
	SDL_Rect dstPortal3 = { 570, 5, portalSize , portalSize };
	SDL_FRect Portal3 = { dstPortal3.x, dstPortal3.y, portalSize , portalSize };
	//Portal4
	SDL_Rect dstPortal4 = { 570, 635, portalSize , portalSize };
	SDL_FRect Portal4 = { dstPortal4.x, dstPortal4.y, portalSize , portalSize };
	//NPC
	int sizeNPC = 80;
	SDL_Surface* surfNPC = IMG_Load("sprites\\npc\\npc.png");
	SDL_Texture* textNPC = SDL_CreateTextureFromSurface(ren, surfNPC);
	SDL_FreeSurface(surfNPC);
	SDL_Rect srcNPC = { 232, 40, 99, 118 };
	SDL_Rect dstNPC = { 200, 135, sizeNPC, sizeNPC };
	SDL_FRect NPC = { dstNPC.x, dstNPC.y, sizeNPC, sizeNPC };

	SDL_Rect srcNPC2 = { 459, 22, 69, 126 };
	SDL_Rect dstNPC2 = { 1000, 560, 60, 100 };
	SDL_FRect NPC2 = { dstNPC2.x, dstNPC2.y, dstNPC2.w, dstNPC2.h };
	//Locked Chest
	SDL_FRect chest = { 200, 82, 70, 70 };
	SDL_Surface* surfLockedChest = IMG_Load("sprites\\puzzles\\lockedChest.png");
	SDL_Texture* textLockedChest = SDL_CreateTextureFromSurface(ren, surfLockedChest);
	SDL_FreeSurface(surfLockedChest);
	SDL_Rect dstLockedChest = {chest.x, chest.y, chest.w, chest.h};
	//Open Chest
	SDL_Surface* surfOpenChest = IMG_Load("sprites\\puzzles\\openChest.png");
	SDL_Texture* textOpenChest = SDL_CreateTextureFromSurface(ren, surfOpenChest);
	SDL_FreeSurface(surfOpenChest);
	SDL_Rect dstOpenChest = { chest.x, chest.y, chest.w, chest.h };
	//Lamp off
	SDL_Rect dstLamp = { 180,465, 35, 35 };
	SDL_FRect dstFLamp = { 180,465, 35, 35 };
	SDL_Surface* surfLampOff = IMG_Load("sprites\\puzzles\\extinguished_lamp.png");
	SDL_Texture* textLampOff = SDL_CreateTextureFromSurface(ren, surfLampOff);
	SDL_FreeSurface(surfLampOff);
	//Lamp on
	SDL_Surface* surfLampOn = IMG_Load("sprites\\puzzles\\lit_lamp.png");
	SDL_Texture* textLampOn = SDL_CreateTextureFromSurface(ren, surfLampOn);
	SDL_FreeSurface(surfLampOn);
	//Runes Puzzle
	SDL_Surface* surfRunesPuzzle = IMG_Load("sprites\\puzzles\\puzzle3.png");
	SDL_Texture* textRunesPuzzle = SDL_CreateTextureFromSurface(ren, surfRunesPuzzle);
	SDL_FreeSurface(surfRunesPuzzle);
	SDL_FRect RunesRect = { 900, 500, 60, 60};
	SDL_Rect dstRunesRect = { RunesRect.x, RunesRect.y, RunesRect.w, RunesRect.h };
	SDL_Rect srcRunesRect = { 0 , 34, 182, 147};
#pragma endregion

	//Rect
	//Trees
	SDL_FRect rect1 = { 728, 195, 12, 37 };
	SDL_FRect rect2 = { 272, 99, 15, 47 };
	SDL_FRect rect3 = { 445, 586, 15, 42 };
	//Columns
	SDL_FRect rect4 = { 275, 45, 45, 48 };
	SDL_FRect rect5 = { 274, 144, 43, 45 };
	SDL_FRect rect6 = { 150, 145, 42, 42 };
	SDL_FRect rect7 = { 149, 145, 42, 44 };
	SDL_FRect rect8 = { 363, 259, 42, 46 };
	SDL_FRect rect9 = { 362, 368, 44, 45 };
	SDL_FRect rect10 = { 539, 196, 42, 44 };
	SDL_FRect rect11 = { 653, 196, 45, 46 };
	SDL_FRect rect12 = { 655, 410, 44, 50 };
	SDL_FRect rect13 = { 915, 511, 27, 60 };
	SDL_FRect rect14 = { 255, 600, 70, 62 };
	SDL_FRect rect16 = { 802, 137, 32, 43 };
	SDL_FRect rect17 = { 876, 126, 34, 55 };
	SDL_FRect rect18 = { 947, 126, 34, 55 };
	SDL_FRect rect19 = { 1015, 133, 33, 47 };

	int frame = 0, frame_count = 10, cur_frametime = 0, max_frametime = 1000/120;
	int lasttime = SDL_GetTicks(); int newtime = SDL_GetTicks();
	int	dt = 0;
	bool animation = false;

	int lastPosXbat = 0, lastPosYbat = 0;
	int lastPosXgoblin = 0, lastPosYgoblin = 0;
	int lastPosXSlime = 0, lastPosYSlime = 0;
	int lastPosXWerewolf = 0, lastPosYWerewolf = 0;
	int lastPosXRat = 0, lastPosYRat = 0;
	int lastPosXPlayer = 0, lastPosYPlayer = 0;
	main_menu();
	while (isRunning) {
		UP = DOWN = LEFT = RIGHT = 0;
		player = { Xcoordinate, Ycoordinate, Xsize, Ysize };
		legs = { Xcoordinate, Ycoordinate + 30, Xsize, 10 };
		bat = { BatX, BatY, XsizeEnemy, YsizeEnemy };
		goblin = { GoblinX, GoblinY, XsizeEnemy, YsizeEnemy };
		slime = { SlimeX, SlimeY, XsizeEnemy, YsizeEnemy };
		werewolf = { WerewolfX, WerewolfY, XsizeEnemy, YsizeEnemy };
		rat = { RatX, RatY, XsizeEnemy, YsizeEnemy };
		while (SDL_PollEvent(&ev) != NULL) {
		//isPressedEscape = pressedEscape();
		isPressed = pressedEnter();
			if (state[SDL_SCANCODE_ESCAPE]) {
				menu();
			}
			switch (ev.type) {
			case SDL_QUIT:
				isRunning = false;
				break;

			case SDL_KEYDOWN:
				switch (ev.key.keysym.scancode) {
				/*case SDL_SCANCODE_ESCAPE: {
					menu(); 
					break;
				}*/
				case SDL_SCANCODE_Q:
					complete_the_quest(ren);
					break;
				case SDL_SCANCODE_TAB: character_leveling(ren); break;
				case SDL_SCANCODE_I: upgradeItems(ren); break;
				}

			case SDL_KEYUP:
				switch (ev.key.keysym.scancode) {
				case SDL_SCANCODE_LEFT: LEFT =	false; break;
				case SDL_SCANCODE_A:    LEFT =	false; break;
				}
			}


			switch (ev.window.event) {
			case SDL_WINDOWEVENT_SIZE_CHANGED:
				win_width = ev.window.data1;
				win_height = ev.window.data2;
				Xcoordinate = win_width / 2 - Xsize / 2;
				Ycoordinate = win_height / 2 - Ysize / 2;
				break;
			case SDL_WINDOWEVENT_MINIMIZED:
				SDL_Log("Window %d minimized", ev.window.windowID);
				pause = 1;
				printf("pause %d\n", pause);
				break;
			case SDL_WINDOWEVENT_RESTORED:
				pause = 0;
				printf("pause %d\n", pause);
				break;
			}


		}

		newtime = SDL_GetTicks();
		dt = newtime - lasttime;
		lasttime = newtime;

		if ((state[SDL_SCANCODE_UP] or state[SDL_SCANCODE_W]) and (!state[SDL_SCANCODE_DOWN] or !state[SDL_SCANCODE_S])) {
			if (!checkCollision(legs, rect8))
				lastPosXPlayer = Xcoordinate, lastPosYPlayer = Ycoordinate + 4;
			UP = 1;
			if (UP) {
				DOWN = 0, LEFT = 0, RIGHT = 0;
				Ycoordinate -= 4;
			}			
		}
		else if ((state[SDL_SCANCODE_DOWN] or state[SDL_SCANCODE_S]) and (!state[SDL_SCANCODE_UP] or !state[SDL_SCANCODE_W])) {
			DOWN = 1;
			if (!checkCollision(legs, rect8))
				lastPosXPlayer = Xcoordinate, lastPosYPlayer = Ycoordinate - 4;
			if (DOWN) {
				UP = 0, LEFT = 0, RIGHT = 0;
				Ycoordinate += 4;
			}
		}
		else if ((state[SDL_SCANCODE_LEFT] or state[SDL_SCANCODE_A]) and (!state[SDL_SCANCODE_RIGHT] or !state[SDL_SCANCODE_D])) {
			LEFT = 1;
			if (!checkCollision(legs, rect8))
				lastPosXPlayer = Xcoordinate + 4, lastPosYPlayer = Ycoordinate;
			if (LEFT) {
				UP = 0, RIGHT = 0, DOWN = 0;
				Xcoordinate -= 4;
			}			
		}
		else if ((state[SDL_SCANCODE_RIGHT] or state[SDL_SCANCODE_D]) and (!state[SDL_SCANCODE_LEFT] or !state[SDL_SCANCODE_A])) {
			RIGHT = 1;
			if (!checkCollision(legs, rect8))
				lastPosXPlayer = Xcoordinate - 4, lastPosYPlayer = Ycoordinate;
			if (RIGHT) {
				UP = 0, LEFT = 0, DOWN = 0;
				Xcoordinate += 4;
			}			
		}
		animation = UP or DOWN or LEFT or RIGHT;
		if (row == 1 and col == 1) {
			if (checkCollision(legs, rect1) or checkCollision(legs, rect2) or checkCollision(legs, rect3)) {
				Xcoordinate = lastPosXPlayer, Ycoordinate = lastPosYPlayer;
			}
		}
		if (row == 1 and col == 2) {
			if (checkCollision(legs, rect2)) {
				Xcoordinate = lastPosXPlayer, Ycoordinate = lastPosYPlayer;
			}
		}
		if (row == 2 and col == 1) {
			if (checkCollision(legs, rect4) or checkCollision(legs, rect5) or checkCollision(legs, rect6) or checkCollision(legs, rect7)
				or checkCollision(legs, rect8) or checkCollision(legs, rect9) or checkCollision(legs, rect10) or checkCollision(legs, rect11)
				or checkCollision(legs, rect12) or checkCollision(legs, rect13) or checkCollision(legs, rect14)	or checkCollision(legs, rect16) 
				or checkCollision(legs, rect17) or checkCollision(legs, rect18) or checkCollision(legs, rect19)) {
				Xcoordinate = lastPosXPlayer, Ycoordinate = lastPosYPlayer;
			}
		}
		
		if (row == 1 and col == 1) {
			if (keyCheckBat == 1) {
				if (!winnerBat)
					streing(BatX, BatY, i, flagEnemy1);
			}
			if (!winnerSlime)
				streing(SlimeX, SlimeY, i3, flagEnemy3);			
			if (!winnerRat)
				streing(RatX, RatY, i5, flagEnemy5);
		}
		if (row == 2 and col == 2 and keyCheckGoblin) {
			if (!winnerGoblin)
				streing(GoblinX, GoblinY, i2, flagEnemy2);
			if (!winnerWerewolf)
				streing(WerewolfX, WerewolfY, i4, flagEnemy4);
		}

		SDL_Rect srcrectCharacter = { 10, 10, 120, 120 };
		SDL_Rect dstrectCharacter = { Xcoordinate - 7, Ycoordinate - 5, Xsize+20, Ysize+20};
		SDL_Rect srcrectBat = { 10, 10, 100, 140 };
		SDL_Rect dstrect = { BatX - 19, BatY, XsizeEnemy, YsizeEnemy};
		SDL_Rect srcGoblin = { 77, 31, 134, 124 };
		SDL_Rect dstGoblin = { GoblinX, GoblinY, XsizeEnemy, YsizeEnemy };
		SDL_Rect dstSlime = { SlimeX, SlimeY, XsizeEnemy, YsizeEnemy };
		SDL_Rect dstWerewolf = { WerewolfX, WerewolfY, XsizeEnemy, YsizeEnemy };
		SDL_Rect srcWerewolf = { 106, 89, 162, 155 };
		SDL_Rect dstRat = { RatX, RatY, XsizeEnemy, YsizeEnemy };
		SDL_Rect srcRat = { 52, 34, 114, 88 };

		if (row == 1 and col == 1) {
			if (keyCheckBat == 1){
				if (checkCollision(player, bat)) {
					lastPosXbat = BatX, lastPosYbat = BatY;
					battle(BatX, BatY, switcherBat, Bat);
					winnerBat = true;
				}
			}			
			if (checkCollision(player, slime)) {
				lastPosXSlime = SlimeX, lastPosYSlime = SlimeY;
				battle(SlimeX, SlimeY, switcherSlime, Slime);
				winnerSlime = true;
			}			
			if (checkCollision(player, rat)) {
				lastPosXRat = RatX; lastPosYRat = RatY;
				battle(RatX, RatY, switcherRat, Rat);
				winnerRat = true;
			}
		}
		if (row == 2 and col == 2 and keyCheckGoblin) {
			if (checkCollision(player, goblin)) {
				lastPosXgoblin = GoblinX, lastPosYgoblin = GoblinY;
				battle(GoblinX, GoblinY, switcherGoblin, Goblin);
				winnerGoblin = true;
			}
			if (checkCollision(player, werewolf)) {
				lastPosXWerewolf = WerewolfX; lastPosYWerewolf = WerewolfY;
				battle(WerewolfX, WerewolfY, switcherWerewolf, Werewolf);
				winnerWerewolf = true;
			}
		}
		if (winnerBat or winnerGoblin or winnerSlime or winnerWerewolf or winnerRat) {
			startRespawn++;
		}
		if (startRespawn >= 250) {
			if (winnerBat) {
				BatX = lastPosXbat, BatY = lastPosYbat;
				winnerBat = false;
			}
			if (winnerGoblin) {
				GoblinX = lastPosXgoblin, GoblinY = lastPosYgoblin;
				winnerGoblin = false;
			}
			if (winnerSlime) {
				SlimeX = lastPosXSlime, SlimeY = lastPosYSlime;
				winnerSlime = false;
			}
			if (winnerWerewolf) {
				WerewolfX = lastPosXWerewolf, WerewolfY = lastPosYWerewolf;
				winnerWerewolf = false;
			}
			if (winnerRat) {
				RatX = lastPosXRat, RatY = lastPosYRat;
				winnerRat = false;
			}
			startRespawn = 0;
			recovery_character();
			printf("Respawned\n");
		}
		wall(player);

		SDL_SetRenderDrawColor(ren, 200, 200, 200, 0);
		SDL_RenderClear(ren);

		/*SDL_SetRenderDrawColor(ren, 200, 100, 0, 0);

		if (row == 1 and col == 1) {
			SDL_RenderFillRectF(ren, &bat);
			SDL_RenderFillRectF(ren, &NPC);
		}
		SDL_SetRenderDrawColor(ren, 200, 0, 0, 0);
		SDL_RenderFillRect(ren, &player);*/

		//отрисовка комнат
		if (row == 1 and col == 1) {
			SDL_RenderCopy(ren, textRoom1, NULL, NULL);
			SDL_FRect Plate2 = { 86,274,39,41 };
			if (checkCollision(player, Plate2) and state[SDL_SCANCODE_RETURN] and isPressed) {
				hint(ren);
			}
		}
		if (row == 2 and col == 1) {
			SDL_RenderCopy(ren, textRoom2, NULL, NULL);
			if (flagCode)//Кодовый замок
				SDL_RenderCopy(ren, textLockedChest, NULL, &dstLockedChest);
			if (flagCode == 0)
				SDL_RenderCopy(ren, textOpenChest, NULL, &dstOpenChest);
			if (checkCollision(player, chest) and state[SDL_SCANCODE_RETURN] and isPressed)
				code_lock(ren);
			if (flagLamps)//Лапмпа
				SDL_RenderCopy(ren, textLampOn, NULL, &dstLamp);
			if (flagLamps == 0) {
				dstLamp.x = dstOpenChest.x; dstLamp.w = dstOpenChest.w; dstLamp.h = dstOpenChest.h;
				dstFLamp.x = dstLamp.x; dstFLamp.w = dstLamp.w; dstFLamp.h = dstLamp.h;
				if (checkChest == 0) {
					SDL_RenderCopy(ren, textLockedChest, NULL, &dstLamp);
				}
				if (checkChest == 1) {
					SDL_RenderCopy(ren, textOpenChest, NULL, &dstLamp);
				}
				if (checkCollision(player, dstFLamp) and state[SDL_SCANCODE_RETURN] and isPressed) {
					hero.Gold += 300;
					checkChest = 1;
				}
			}
			if (checkCollision(player, dstFLamp) and state[SDL_SCANCODE_RETURN] and flagLamps and isPressed)
				lamps(ren, dstLamp);
		}
		if (row == 1 and col == 2) {
			SDL_RenderCopy(ren, textRoom3, NULL, NULL);
			SDL_RenderCopy(ren, textNPC, &srcNPC, &dstNPC);
			if (curQuest == 2)
				SDL_RenderCopy(ren, textNPC, &srcNPC2, &dstNPC2);

			//1144 274 40 42
			SDL_FRect NamePlate = { 1144,274,40,42 };
			if (checkCollision(player, NamePlate) and state[SDL_SCANCODE_RETURN] and isPressed)
				nameplate(ren);
		}
		if (row == 2 and col == 2) {
			SDL_RenderCopy(ren, textRoom4, NULL, NULL);
		}

		if (animation) {
			cur_frametime += dt;
			if (cur_frametime >= max_frametime) {
				cur_frametime -= max_frametime;
				frame = (frame + 1) % frame_count;
				srcrectCharacter.x = 120 * frame;
			}
		}
		if (row == 2 and col == 2) {//отрисовка рун и головоломка
			if (curQuest == 2) {
				//Water
				SDL_RenderCopy(ren, textRune, &srcrune, &dstrune);
				//Fire
				SDL_RenderCopy(ren, textRune, &srcrune2, &dstrune2);
				//Earth
				SDL_RenderCopy(ren, textRune, &srcrune3, &dstrune3);
			}
			//SDL_RenderFillRectF(ren, &RunesRect);
			if (flagRunes == 1)
				SDL_RenderCopy(ren, textRunesPuzzle, &srcRunesRect, &dstRunesRect);

			if (checkCollision(player, RunesRect) and state[SDL_SCANCODE_RETURN] and isPressed and flagRunes)
				runes_puzzle(ren);

			if (flagRunes == 0) {
				dstRunesRect.w = dstLockedChest.w; dstRunesRect.h = dstLockedChest.h;
				RunesRect.w = dstLockedChest.w; RunesRect.h = dstLockedChest.h;
				if (checkChest2 == 0) {
					SDL_RenderCopy(ren, textLockedChest, NULL, &dstRunesRect);
					if (checkCollision(player, RunesRect) and state[SDL_SCANCODE_RETURN] and isPressed) {
						hero.Gold += 500;
						checkChest2 = 1;
					}
				}
				if (checkChest2 == 1) {
					SDL_RenderCopy(ren, textOpenChest, NULL, &dstRunesRect);
				}
			}
		}
		if (row == 2 and col == 2 and curQuest == 2) {//коллизия рун
			if (checkCollision(player, rune) and state[SDL_SCANCODE_RETURN]) {//Water
				rune.x = -100, rune.y = -100;
				dstrune.x = dstrune.y = -100;
				remove_the_rune(runeWater, runeFire, runeEarth);
				runeWater = 1;
				set_runes(runeWater, runeFire, runeEarth);
			}
			if (checkCollision(player, rune2) and state[SDL_SCANCODE_RETURN]) {//Fire
				rune2.x = -100, rune2.y = -100;
				dstrune2.x = dstrune2.y = -100;
				remove_the_rune(runeWater, runeFire, runeEarth);
				runeFire = 1;
				set_runes(runeWater, runeFire, runeEarth);
			}
			if (checkCollision(player, rune3) and state[SDL_SCANCODE_RETURN]) {//Eatrh
				rune3.x = -100, rune3.y = -100;
				dstrune3.x = dstrune3.y = -100;
				remove_the_rune(runeWater, runeFire, runeEarth);
				runeEarth = 1;
				set_runes(runeWater, runeFire, runeEarth);
			}
		}
		//Portal
		if (row != 1)
			SDL_RenderCopy(ren, textPortal, &srcPortal, &dstPortal1);//левый
		if (row != 2)
			SDL_RenderCopy(ren, textPortal, &srcPortal, &dstPortal2);//правый
		if (col != 2)
			SDL_RenderCopy(ren, textPortal, &srcPortal, &dstPortal3);//верхний
		if (col != 1)
			SDL_RenderCopy(ren, textPortal, &srcPortal, &dstPortal4);//нижний

		//NPC
		if (checkCollision(player, NPC) and state[SDL_SCANCODE_RETURN] and isPressed and row == 1 and col == 2) {
			questFlag = 1;
			quest(ren);
		}
		if (checkCollision(player, NPC2) and state[SDL_SCANCODE_RETURN] and isPressed and row == 1 and col == 2 and curQuest == 2) {
			dialogue(ren);
		}
		//Порталы
		if (checkCollision(player, Portal1) and state[SDL_SCANCODE_RETURN] and isPressed) {//Левый портал
			if (row != 1) {
				Xcoordinate = dstPortal2.x + 25, Ycoordinate = dstPortal2.y + 10;
				row -= 1;
			}
		}
		if (checkCollision(player, Portal2) and state[SDL_SCANCODE_RETURN] and isPressed) {//Правый портал
			if (row != 2) {
				Xcoordinate = dstPortal1.x + 25, Ycoordinate = dstPortal1.y + 10;
				row += 1;
			}
		}
		if (checkCollision(player, Portal3) and state[SDL_SCANCODE_RETURN] and isPressed) {//Верхний портал
			if (col != 2) {
				Xcoordinate = dstPortal4.x + 25, Ycoordinate = dstPortal4.y + 10;
				col += 1;
			}
		}
		if (checkCollision(player, Portal4) and state[SDL_SCANCODE_RETURN] and isPressed) {//Нижний портал
			if (col != 1) {
				Xcoordinate = dstPortal3.x + 25, Ycoordinate = dstPortal3.y + 10;
				col -= 1;
			}
		}
		
		/*if (row == 1 and col == 1) {
			if (!checkCollision(legs, rect1) or !checkCollision(legs, rect2) or !checkCollision(legs, rect3)) {
				Xcoordinate = lastPosXPlayer, Ycoordinate = lastPosYPlayer;
			}
		}
		if (row == 2 and col == 1) {
			if (!checkCollision(legs, rect4) or !checkCollision(legs, rect5) or !checkCollision(legs, rect6) or !checkCollision(legs, rect7)
				or !checkCollision(legs, rect8) or !checkCollision(legs, rect9) or !checkCollision(legs, rect10) or !checkCollision(legs, rect11)
				or !checkCollision(legs, rect12) or !checkCollision(legs, rect13) or !checkCollision(legs, rect14) or !checkCollision(legs, rect15)
				or !checkCollision(legs, rect16) or !checkCollision(legs, rect17) or !checkCollision(legs, rect18) or !checkCollision(legs, rect19)) {
				Xcoordinate = lastPosXPlayer, Ycoordinate = lastPosYPlayer;
			}
		}*/
		if (row == 1 and col == 1) {
			if (checkCollision(player, rect1) or checkCollision(player, rect2) or checkCollision(player, rect3)) {
				SDL_RenderCopy(ren, textRoom1Collision, NULL, NULL);
				flagCollision = 1;
			}
		}
		if (row == 1 and col == 2) {
			if (checkCollision(player, rect2)) {
				SDL_RenderCopy(ren, textRoom3Collision, NULL, NULL);
				flagCollision = 1;
			}
		}
		if (row == 2 and col == 1) {
			if (checkCollision(player, rect4) or checkCollision(player, rect5) or checkCollision(player, rect6) or checkCollision(player, rect7)
				or checkCollision(player, rect8) or checkCollision(player, rect9) or checkCollision(player, rect10) or checkCollision(player, rect11)
				or checkCollision(player, rect12) or checkCollision(player, rect13) or checkCollision(player, rect14) or checkCollision(player, rect16) 
				or checkCollision(player, rect17) or checkCollision(player, rect18) or checkCollision(player, rect19)) {
				SDL_RenderCopy(ren, textRoom2Collision, NULL, NULL);
				flagCollision = 1;
			}
		}
		if (!animation)
			SDL_RenderCopy(ren, textCharacter, &srcrectCharacter, &dstrectCharacter);
		if (animation and RIGHT and !UP and !DOWN ) {
			srcrectCharacter.x, srcrectCharacter.y = 918, srcrectCharacter.w = 120, srcrectCharacter.h = 120;
			SDL_RenderCopy(ren, textCharacter, &srcrectCharacter, &dstrectCharacter);	
		}
		if (animation and LEFT and !UP and !DOWN ) {
			srcrectCharacter.x, srcrectCharacter.y = 660, srcrectCharacter.w = 120, srcrectCharacter.h = 120;
			SDL_RenderCopy(ren, textCharacter, &srcrectCharacter, &dstrectCharacter);
		}
		if (animation and UP) {
			srcrectCharacter.x, srcrectCharacter.y = 785, srcrectCharacter.w = 120, srcrectCharacter.h = 120;
			SDL_RenderCopy(ren, textCharacter, &srcrectCharacter, &dstrectCharacter);
		}
		if (animation and DOWN) {
			srcrectCharacter.x, srcrectCharacter.y = 530, srcrectCharacter.w = 120, srcrectCharacter.h = 120;
			SDL_RenderCopy(ren, textCharacter, &srcrectCharacter, &dstrectCharacter);
		}
		if (row == 1 and col == 1 and flagCollision == 0) {
			SDL_RenderCopy(ren, textRoom1Collision, NULL, NULL);
		}
		if (row == 1 and col == 2 and flagCollision == 0) {
			SDL_RenderCopy(ren, textRoom3Collision, NULL, NULL);
		}
		if (row == 2 and col == 1 and flagCollision == 0) {
			SDL_RenderCopy(ren, textRoom2Collision, NULL, NULL);
		}
		isPressed = 0;
		isPressedEscape = 0;
		if (row == 1 and col == 1) {
			if (keyCheckBat == 1)
				SDL_RenderCopy(ren, textBat, &srcrectBat, &dstrect);			
			SDL_RenderCopy(ren, textSlime, NULL, &dstSlime);		
			SDL_RenderCopy(ren, textRat, &srcRat, &dstRat);
		}
		if (row == 2 and col == 2 and keyCheckGoblin) {
			SDL_RenderCopy(ren, textWerewolf, &srcWerewolf, &dstWerewolf);
			SDL_RenderCopy(ren, textGoblin, &srcGoblin, &dstGoblin);
		}
		
		SDL_RenderPresent(ren);
		SDL_Delay(17);
		flagCollision = 0;
	}
	SDL_DestroyTexture(textRoom1);
	SDL_DestroyTexture(textRoom1Collision);
	SDL_DestroyTexture(textRoom2);
	SDL_DestroyTexture(textRoom2Collision);
	SDL_DestroyTexture(textRoom3);
	SDL_DestroyTexture(textRoom3Collision);
	SDL_DestroyTexture(textRoom4);
	SDL_DestroyTexture(textCharacter);
	SDL_DestroyTexture(textBat);
	SDL_DestroyTexture(textRune);
	SDL_DestroyTexture(textPortal);
	SDL_DestroyTexture(textNPC);
	SDL_DestroyTexture(textLampOff);
	SDL_DestroyTexture(textLampOn);
	SDL_DestroyTexture(textLockedChest);
	SDL_DestroyTexture(textOpenChest);
	SDL_DestroyTexture(textGoblin);
	SDL_DestroyTexture(textSlime);
	SDL_DestroyTexture(textWerewolf);
	SDL_DestroyTexture(textRat);

	de_init(0);
	return 0;
}