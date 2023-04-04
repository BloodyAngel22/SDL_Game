#define _CRT_SECURE_NO_WARNINGS
#include <SDL.h>
#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#define  EnemyUp 1
#define  EnemyRight 2
#define  EnemyDown 3
#define  EnemyLeft 4

float win_width = 1000, win_height = 600;
SDL_Window* win = 0;
SDL_Renderer* ren = 0;
float Ox = win_width / 2, Oy = win_height / 2;

void init(); void de_init(int error);

void init() {

	if (SDL_Init(SDL_INIT_VIDEO) != 0) {
		printf("Couldn't init sdl, Error %s", SDL_GetError());
		system("pause");
		de_init(1);
	}

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
		counter++;
		SDL_Delay(15);
		if (counter >= 100) {
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

int main(int argc, char* argv[]) {
	init();
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
	Xcoordinate = shiftX - Xsize / 2, Ycoordinate = shiftY - Ysize / 2;
	SDL_PollEvent(&ev);
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

			case SDL_MOUSEBUTTONDOWN:
				if (ev.button.button == SDL_BUTTON_LEFT) {
					Xcoordinate = ev.button.x - Xsize / 2;
					Ycoordinate = ev.button.y - Ysize / 2;
				}
				if (ev.button.button == SDL_BUTTON_MIDDLE) {
					Xsize = 40; Ysize = 40;
				}
				break;

			case SDL_MOUSEWHEEL:
				if (ev.wheel.y > 0) {
					if (Xsize >= win_width and Ysize >= win_height) {
						Xsize = 10; Ysize = 10;
					}
					Xsize += 3;
					Ysize += 3;
				}
				if (ev.wheel.y < 0) {
					if (Xsize > 0 and Ysize > 0) {
						Xsize -= 3;
						Ysize -= 3;
					}
					if (Xsize <= 0 and Ysize <= 0) {
						Xsize = 1; Ysize = 1;
					}
				}
				break;

			case SDL_KEYDOWN:
				switch (ev.key.keysym.scancode) {
				case SDL_SCANCODE_UP: Ycoordinate -= 10; break;
				case SDL_SCANCODE_W: Ycoordinate -= 10; break;
				case SDL_SCANCODE_DOWN: Ycoordinate += 10; break;
				case SDL_SCANCODE_S: Ycoordinate += 10; break;
				case SDL_SCANCODE_RIGHT: Xcoordinate += 10; break;
				case SDL_SCANCODE_D: Xcoordinate += 10; break;
				case SDL_SCANCODE_LEFT: Xcoordinate -= 10; break;
				case SDL_SCANCODE_A: Xcoordinate -= 10; break;
				case SDL_SCANCODE_ESCAPE: isRunning = false;
				}
				break;
			}

			switch (ev.window.event) {
			case SDL_WINDOWEVENT_MOVED:
				SDL_Log("Window %d moved to %d,%d",
					ev.window.windowID, ev.window.data1,
					ev.window.data2);
				break;
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

		SDL_SetRenderDrawColor(ren, 200, 200, 200, 0);
		SDL_RenderClear(ren);

		SDL_SetRenderDrawColor(ren, 200, 100, 0, 0);
		SDL_RenderFillRectF(ren, &enemy);
		//SDL_SetRenderDrawColor(ren, 200, 100, 0, 0);
		//SDL_RenderFillRectF(ren, &enemy1);
		SDL_SetRenderDrawColor(ren, 200, 0, 0, 0);
		SDL_RenderFillRect(ren, &r);

		streing(EnemyX, EnemyY, i, flagEnemy1);


		SDL_RenderPresent(ren);
		SDL_Delay(16);

		if (hitbox == true) {
			battle(EnemyX, EnemyY, switcher);
			winner = true;
			SDL_Delay(300);
			//printf("true\n");
			//system("cls");
		}
		if (winner) {
			startRespawn++;
		}
		if (startRespawn >= 300) {
			EnemyX = shiftX + 200, EnemyY = shiftY + 100;
			startRespawn = 0;
			winner = false;
			printf("Respawned\n");
		}
	}
	de_init(0);
	return 0;
}