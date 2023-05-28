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

void battle(float& EnemyX, float& EnemyY, bool& switcher) {
	int counter = 0;
	switcher = true;
	while (switcher == true) {
		MenuBattle(ren);
		if (livedEnemies < 1) {
			EnemyX = -300; EnemyY = -300;
			switcher = false;
		}
	}
}

bool checkCollision(SDL_Rect a, SDL_FRect b)
{
	//The sides of the rectangles
	int leftA, leftB;
	int rightA, rightB;
	int topA, topB;
	int bottomA, bottomB;

	//Calculate the sides of rect A
	leftA = a.x;
	rightA = a.x + a.w;
	topA = a.y;
	bottomA = a.y + a.h;

	//Calculate the sides of rect B
	leftB = b.x;
	rightB = b.x + b.w;
	topB = b.y;
	bottomB = b.y + b.h;
	//If any of the sides from A are outside of B
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

	//If none of the sides from A are outside B
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
		isPressed = pressedEscape();
		while (SDL_PollEvent(&ev) != NULL) {
			switch (ev.type) {
			case SDL_KEYDOWN:
				switch (ev.key.keysym.scancode) {
				case SDL_SCANCODE_ESCAPE:
					if (isPressed) {
						SDL_DestroyTexture(textMenu);
						SDL_DestroyTexture(textArrow);
						return;
						break;
					}
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
	bool winner = false;
	bool isRunning = true;
	bool switcher = true;
	int pause = 0;
	int i = 0;
	int startRespawn = 0;
	int endRespawn = 0;
	int flagEnemy1 = EnemyUp;
	int flagEnemy2 = EnemyDown;
	int shiftX = win_width / 2, shiftY = win_height / 2, Xsize = 40, Ysize = 40;
	Xcoordinate = shiftX - Xsize / 2, Ycoordinate = shiftY - Ysize / 2;
	float EnemyX = shiftX + 200, EnemyY = shiftY + 100, XsizeEnemy = 40, YsizeEnemy = 40;
	SDL_FRect enemy = { EnemyX, EnemyY, Xsize, Ysize };
	SDL_FRect enemy1 = { EnemyX, EnemyY, Xsize, Ysize };
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
	//room2
	SDL_Surface* surfRoom2 = IMG_Load("sprites\\background\\part2.png");
	SDL_Texture* textRoom2 = SDL_CreateTextureFromSurface(ren, surfRoom2);
	SDL_FreeSurface(surfRoom2);
	//room3
	SDL_Surface* surfRoom3 = IMG_Load("sprites\\background\\part3.png");
	SDL_Texture* textRoom3 = SDL_CreateTextureFromSurface(ren, surfRoom3);
	SDL_FreeSurface(surfRoom3);
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
	player.w = player.h;
	SDL_FreeSurface(surfCharacter);
	//Bat
	SDL_Surface* surfBat = IMG_Load("sprites\\enemy\\bat.png");
	SDL_Texture* textBat = SDL_CreateTextureFromSurface(ren, surfBat);
	SDL_FreeSurface(surfBat);
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
	SDL_Rect srcNPC = { 232, 40, 99, 118};
	SDL_Rect dstNPC = { 200, 200, sizeNPC, sizeNPC};
	SDL_FRect NPC = { dstNPC.x, dstNPC.y, sizeNPC, sizeNPC};
#pragma endregion

	int frame = 0, frame_count = 10, cur_frametime = 0, max_frametime = 1000/120;
	int lasttime = SDL_GetTicks(); int newtime = SDL_GetTicks();
	int	dt = 0;
	bool animation = false;

	main_menu();
	while (isRunning) {
		UP = DOWN = LEFT = RIGHT = 0;
		player = { Xcoordinate, Ycoordinate, Xsize, Ysize };
		enemy = { EnemyX, EnemyY, XsizeEnemy, YsizeEnemy };
		enemy1 = { EnemyX, EnemyY - 200, XsizeEnemy, YsizeEnemy };
		bool hitbox = checkCollision(player, enemy);
		while (SDL_PollEvent(&ev) != NULL) {

			switch (ev.type) {
			case SDL_QUIT:
				isRunning = false;
				break;

			case SDL_KEYDOWN:
				switch (ev.key.keysym.scancode) {
				case SDL_SCANCODE_ESCAPE: 
					menu(); 
					break;
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
			UP = 1;
			if (UP) {
				DOWN = 0, LEFT = 0, RIGHT = 0;
			}
			Ycoordinate -= 4;
		}
		if ((state[SDL_SCANCODE_DOWN] or state[SDL_SCANCODE_S]) and (!state[SDL_SCANCODE_UP] or !state[SDL_SCANCODE_W])) {
			DOWN = 1;
			if (DOWN) {
				UP = 0, LEFT = 0, RIGHT = 0;
			}
			Ycoordinate += 4;
		}
		if ((state[SDL_SCANCODE_LEFT] or state[SDL_SCANCODE_A]) and (!state[SDL_SCANCODE_RIGHT] or !state[SDL_SCANCODE_D])) {
			LEFT = 1;
			if (LEFT) {
				UP = 0, RIGHT = 0, DOWN = 0;
			}
			Xcoordinate -= 4;
		}
		if ((state[SDL_SCANCODE_RIGHT] or state[SDL_SCANCODE_D]) and (!state[SDL_SCANCODE_LEFT] or !state[SDL_SCANCODE_A])) {
			RIGHT = 1;
			if (RIGHT) {
				UP = 0, LEFT = 0, DOWN = 0;
			}
			Xcoordinate += 4;
		}
		isPressed = pressedEnter();

		animation = UP or DOWN or LEFT or RIGHT;
		
		if (row == 1 and col == 1)
			streing(EnemyX, EnemyY, i, flagEnemy1);

		SDL_Rect srcrectCharacter = { 10, 10, 120, 120 };
		SDL_Rect dstrectCharacter = { Xcoordinate - 7, Ycoordinate - 5, Xsize+20, Ysize+20};
		SDL_Rect srcrectBat = { 10, 10, 100, 140 };
		SDL_Rect dstrectBat = { EnemyX - 19, EnemyY, XsizeEnemy + 25, YsizeEnemy + 25};

		if (hitbox == true and row == 1 and col == 1) {
			battle(EnemyX, EnemyY, switcher);
			winner = true;
			//printf("true\n");
			//system("cls");
		}
		if (winner) {
			startRespawn++;
		}
		if (startRespawn >= 250) {
			EnemyX = shiftX + 200, EnemyY = shiftY + 100;
			startRespawn = 0;
			winner = false;
			recovery_character();
			printf("Respawned\n");
			flag = 0;
		}
		wall(player);

		SDL_SetRenderDrawColor(ren, 200, 200, 200, 0);
		SDL_RenderClear(ren);

		SDL_SetRenderDrawColor(ren, 200, 100, 0, 0);

		if (row == 1 and col == 1) {
			SDL_RenderFillRectF(ren, &enemy);
			SDL_RenderFillRectF(ren, &NPC);
		}
		SDL_SetRenderDrawColor(ren, 200, 0, 0, 0);
		SDL_RenderFillRect(ren, &player);

		//отрисовка комнат
		if (row == 1 and col == 1) {
			SDL_RenderCopy(ren, textRoom1, NULL, NULL);
			SDL_RenderCopy(ren, textNPC, &srcNPC, &dstNPC);
		}
		if (row == 2 and col == 1) {
			SDL_RenderCopy(ren, textRoom2, NULL, NULL);
		}
		if (row == 1 and col == 2) {
			SDL_RenderCopy(ren, textRoom3, NULL, NULL);
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
		if (row == 2 and col == 2) {//отрисовка рун
			//Water
			SDL_RenderCopy(ren, textRune, &srcrune, &dstrune);
			//Fire
			SDL_RenderCopy(ren, textRune, &srcrune2, &dstrune2);
			//Earth
			SDL_RenderCopy(ren, textRune, &srcrune3, &dstrune3);
		}
		if (row == 2 and col == 2) {//коллизия рун
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
		if (checkCollision(player, NPC) and state[SDL_SCANCODE_RETURN] and isPressed) {
			questFlag = 1;
			quest(ren);
		}

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
		isPressed = 0;
		if (row == 1 and col == 1)
			SDL_RenderCopy(ren, textBat, &srcrectBat, &dstrectBat);
		
		SDL_RenderPresent(ren);
		SDL_Delay(17);

	}
	SDL_DestroyTexture(textRoom1);
	SDL_DestroyTexture(textCharacter);
	SDL_DestroyTexture(textBat);
	SDL_DestroyTexture(textRune);
	SDL_DestroyTexture(textPortal);
	SDL_DestroyTexture(textNPC);
	de_init(0);
	return 0;
}