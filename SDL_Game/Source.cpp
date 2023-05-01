#define _CRT_SECURE_NO_WARNINGS
#include <SDL.h>
#include <SDL_image.h>
#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include "Leveling.h"
#include "Battle.h"
#include "Models.h"
#include "SDL_general.h"
#define  EnemyUp 1
#define  EnemyRight 2
#define  EnemyDown 3
#define  EnemyLeft 4


void init(); void de_init(int error);

float win_width = 1000, win_height = 600;
SDL_Window* win = 0;
SDL_Renderer* ren = 0;

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

	win = SDL_CreateWindow("Window", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED,
		win_width, win_height, SDL_WINDOW_SHOWN | SDL_WINDOW_RESIZABLE);
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
		if (opponent.Health <= 0) {
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
	if (surfMainMenu == NULL) {
		printf("couldn't load main menu\n");
		de_init(1);
	}
	else printf("main menu load\n");
	SDL_Texture* textMainMenu = SDL_CreateTextureFromSurface(ren, surfMainMenu);
	SDL_FreeSurface(surfMainMenu);
	//Arrow
	SDL_Surface* surfArrow = IMG_Load("sprites\\menu\\arrow.png");
	if (surfArrow == NULL) {
		printf("couldn't load arrow\n");
		de_init(1);
	}
	else printf("arrow load\n");
	SDL_Texture* textArrow = SDL_CreateTextureFromSurface(ren, surfArrow);
	SDL_FreeSurface(surfArrow);
#pragma endregion
	int mainMenu = 0;
	SDL_Event ev;
	SDL_PollEvent(&ev);

	int xArrow = 250, yArrow = 135;
	int pointer = 1;
	const Uint8* arrowState = SDL_GetKeyboardState(NULL);
	SDL_Rect srcrectArrow = { 0, 0, 100, 140 };
	SDL_Rect dstrectArrow;
	int flag = 0;
	while (mainMenu == 0) {
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
						yArrow -= 87;
						pointer--;
					}
					break;
				case SDL_SCANCODE_W:
					if (pointer != 1) {
						yArrow -= 87;
						pointer--;
					}
					break;
				case SDL_SCANCODE_DOWN:
					if (pointer != 4) {
						yArrow += 87;
						pointer++;
					}
						break;
				case SDL_SCANCODE_S:
					if (pointer != 4) {
						yArrow += 87;
						pointer++;
						break;
					}
				}
			}
			SDL_SetRenderDrawColor(ren, 200, 200, 200, 0);
			SDL_RenderClear(ren);
			SDL_RenderCopy(ren, textMainMenu, NULL, NULL);
			SDL_RenderCopy(ren, textArrow, &srcrectArrow, &dstrectArrow);
			SDL_RenderPresent(ren);
			SDL_Delay(8);

		}
		if (pointer == 1 and arrowState[SDL_SCANCODE_RETURN]) {
			SDL_DestroyTexture(textMainMenu);
			SDL_DestroyTexture(textArrow);
			return;
		}
		if (pointer == 2 and arrowState[SDL_SCANCODE_RETURN]);
		if (pointer == 3 and arrowState[SDL_SCANCODE_RETURN]) {
			if (flag == 0) {
				printf("creator: Zhigalkin Maxim\n");
				flag = 1;
			}
		}
		if (pointer == 4 and arrowState[SDL_SCANCODE_RETURN]) {
			SDL_DestroyTexture(textMainMenu);
			SDL_DestroyTexture(textArrow);
			de_init(1);
		}
	}


}

void menu() {
#pragma region Texture
	//Main menu
	SDL_Surface* surfMenu = IMG_Load("sprites\\menu\\menu.png");
	if (surfMenu == NULL) {
		printf("couldn't load menu\n");
		de_init(1);
	}
	else printf("main menu load\n");
	SDL_Texture* textMenu = SDL_CreateTextureFromSurface(ren, surfMenu);
	SDL_FreeSurface(surfMenu);
	//Arrow
	SDL_Surface* surfArrow = IMG_Load("sprites\\menu\\arrow.png");
	if (surfArrow == NULL) {
		printf("couldn't load arrow\n");
		de_init(1);
	}
	else printf("arrow load\n");
	SDL_Texture* textArrow = SDL_CreateTextureFromSurface(ren, surfArrow);
	SDL_FreeSurface(surfArrow);
#pragma endregion
	int menu = 0;
	SDL_Event ev;
	SDL_PollEvent(&ev);
	int xArrow = 300, yArrow = 140;
	int pointer = 1;
	const Uint8* arrowState = SDL_GetKeyboardState(NULL);
	SDL_Rect srcrectArrow = { 0, 0, 100, 140 };
	SDL_Rect dstrectArrow;
	while (menu == 0) {
		dstrectArrow = { xArrow, yArrow, 75, 75 };
		while (SDL_PollEvent(&ev) != NULL) {
			switch (ev.type) {
			case SDL_KEYDOWN:
				switch (ev.key.keysym.scancode) {
				case SDL_SCANCODE_ESCAPE:
					return;
					break;
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
						break;
					}
				}
			}
			SDL_SetRenderDrawColor(ren, 200, 200, 200, 0);
			SDL_RenderClear(ren);
			SDL_RenderCopy(ren, textMenu, NULL, NULL);
			SDL_RenderCopy(ren, textArrow, &srcrectArrow, &dstrectArrow);
			SDL_RenderPresent(ren);
			SDL_Delay(8);

		}

		if (pointer == 1 and arrowState[SDL_SCANCODE_RETURN]) {
			SDL_DestroyTexture(textMenu);
			SDL_DestroyTexture(textArrow);
			return; //continue
		}
		if (pointer == 2 and arrowState[SDL_SCANCODE_RETURN]) {
			SDL_DestroyTexture(textMenu);
			SDL_DestroyTexture(textArrow);
			printf("You save a game\n");
			return; //save
		}
		if (pointer == 3 and arrowState[SDL_SCANCODE_RETURN]) {
			SDL_DestroyTexture(textMenu);
			SDL_DestroyTexture(textArrow);
			de_init(1); //exit
		}
	}
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
	int Xcoordinate = shiftX - Xsize / 2, Ycoordinate = shiftY - Ysize / 2;
	float EnemyX = shiftX + 200, EnemyY = shiftY + 100, XsizeEnemy = 40, YsizeEnemy = 40;
	SDL_Rect r = { Xcoordinate, Ycoordinate, Xsize, Ysize };
	SDL_FRect enemy = { EnemyX, EnemyY, Xsize, Ysize };
	SDL_FRect enemy1 = { EnemyX, EnemyY, Xsize, Ysize };
	SDL_Event ev;
	bool UP, DOWN, RIGHT, LEFT;
	const Uint8* state = SDL_GetKeyboardState(NULL);
	UP = DOWN = RIGHT = LEFT = 0;
	Xcoordinate = shiftX - Xsize / 2, Ycoordinate = shiftY - Ysize / 2;
	SDL_PollEvent(&ev);

	#pragma region Texture
		//room
		SDL_Surface* surfRoom = IMG_Load("sprites\\background\\mainMap.png");
		if (surfRoom == NULL) {
			printf("couldn't load room\n");
			de_init(1);
		}else printf("room load\n");
		SDL_Texture* textRoom = SDL_CreateTextureFromSurface(ren, surfRoom);
		SDL_FreeSurface(surfRoom);
		// character 
		SDL_Surface* surfCharacter = IMG_Load("sprites\\character\\character.png");
		if (surfCharacter == NULL) {
			printf("couldn't load character\n");
			de_init(1);
		}
		else printf("character load\n");
		SDL_Texture* textCharacter = SDL_CreateTextureFromSurface(ren, surfCharacter);
		SDL_FreeSurface(surfCharacter);
		//Bat
		SDL_Surface* surfBat = IMG_Load("sprites\\enemy\\bat.png");
		if (surfBat == NULL) {
			printf("couldn't load bat\n");
			de_init(1);
		}
		else printf("bat load\n");
		SDL_Texture* textBat = SDL_CreateTextureFromSurface(ren, surfBat);
		SDL_FreeSurface(surfBat);
	#pragma endregion

		main_menu();
	while (isRunning) {
		r = { Xcoordinate, Ycoordinate, Xsize, Ysize };
		enemy = { EnemyX, EnemyY, XsizeEnemy, YsizeEnemy };
		enemy1 = { EnemyX, EnemyY - 200, XsizeEnemy, YsizeEnemy };
		bool hitbox = checkCollision(r, enemy);
		while (SDL_PollEvent(&ev) != NULL) {

			switch (ev.type) {
			case SDL_QUIT:
				isRunning = false;
				break;

			case SDL_KEYDOWN:
				switch (ev.key.keysym.scancode) {
				case SDL_SCANCODE_ESCAPE: menu(); break;
				case SDL_SCANCODE_TAB: character_leveling(ren); break;
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
		if ((state[SDL_SCANCODE_UP] or state[SDL_SCANCODE_W]) and (!state[SDL_SCANCODE_DOWN] or !state[SDL_SCANCODE_S]))	Ycoordinate	-= 4;
		if ((state[SDL_SCANCODE_DOWN] or state[SDL_SCANCODE_S]) and (!state[SDL_SCANCODE_UP] or !state[SDL_SCANCODE_W]))	Ycoordinate	+=	4;
		if ((state[SDL_SCANCODE_RIGHT] or state[SDL_SCANCODE_D]) and (!state[SDL_SCANCODE_LEFT] or !state[SDL_SCANCODE_A])) Xcoordinate += 4;
		if ((state[SDL_SCANCODE_LEFT] or state[SDL_SCANCODE_A]) and (!state[SDL_SCANCODE_RIGHT] or !state[SDL_SCANCODE_D])) Xcoordinate -= 4;


		streing(EnemyX, EnemyY, i, flagEnemy1);

		SDL_Rect srcrectCharacter = { 10, 10, 100, 140 };
		SDL_Rect dstrectCharacter = { Xcoordinate - 7, Ycoordinate - 5, Xsize + 20, Ysize + 20};
		SDL_Rect srcrectBat = { 10, 10, 100, 140 };
		SDL_Rect dstrectBat = { EnemyX - 19, EnemyY, XsizeEnemy + 25, YsizeEnemy + 25};

		if (hitbox == true) {
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
			recovery_enemy();
			printf("Respawned\n");
		}

		SDL_SetRenderDrawColor(ren, 200, 200, 200, 0);
		SDL_RenderClear(ren);

		SDL_SetRenderDrawColor(ren, 200, 100, 0, 0);
		SDL_RenderFillRectF(ren, &enemy);
		SDL_SetRenderDrawColor(ren, 200, 0, 0, 0);
		SDL_RenderFillRect(ren, &r);

		SDL_RenderCopy(ren, textRoom, NULL, NULL);
		SDL_RenderCopy(ren, textCharacter, &srcrectCharacter, &dstrectCharacter);
		SDL_RenderCopy(ren, textBat, &srcrectBat, &dstrectBat);
		SDL_RenderPresent(ren);
		SDL_Delay(16);

	}
	SDL_DestroyTexture(textRoom);
	SDL_DestroyTexture(textCharacter);
	SDL_DestroyTexture(textBat);
	de_init(0);
	return 0;
}