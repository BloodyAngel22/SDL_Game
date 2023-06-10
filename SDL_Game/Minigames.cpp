#define Rock 1
#define Scissors 2
#define Paper 3
#include "Minigames.h"
#include "Battle.h"

int player;
int bot;
int draw, win, defeat;

SDL_Rect srcRock = { 19, 25, 189, 222 };
SDL_Rect srcScissors = { 559, 15, 145, 224 };
SDL_Rect srcPaper = { 276, 10, 198, 228 };
SDL_Rect srcWin = { 29, 85, 143, 71 };
SDL_Rect srcDefeat = { 224, 85, 244, 71 };
SDL_Rect srcDraw = { 521, 91, 193, 67 };

void rock_scissors_paper_menu(SDL_Renderer* ren) {
	//Texture
	SDL_Surface* surfRockScissorsPaper = IMG_Load("sprites\\minigames\\rock_scissors_paper.png");
	SDL_Texture* textRockScissorsPaper = SDL_CreateTextureFromSurface(ren, surfRockScissorsPaper);
	SDL_FreeSurface(surfRockScissorsPaper);

	SDL_Surface* surfWinDefeatDraw = IMG_Load("sprites\\minigames\\win_defeat_draw.png");
	SDL_Texture* textWinDefeatDraw = SDL_CreateTextureFromSurface(ren, surfWinDefeatDraw);
	SDL_FreeSurface(surfWinDefeatDraw);

	SDL_Surface* surfArrowUp = IMG_Load("sprites\\puzzles\\arrowUp.png");
	SDL_Texture* textArrowUp = SDL_CreateTextureFromSurface(ren, surfArrowUp);
	SDL_FreeSurface(surfArrowUp);

	SDL_Surface* surfBackground = IMG_Load("sprites\\puzzles\\background.png");
	SDL_Texture* textBackground = SDL_CreateTextureFromSurface(ren, surfBackground);
	SDL_FreeSurface(surfBackground);
	//

	SDL_Rect position = { 0, 0, 150, 150 };
	SDL_Rect arrowPosition = { 0, 0, 200, 100 };

	int running = 1;
	int winningStreak = 0;

	SDL_Event ev;
	SDL_PollEvent(&ev);
	const Uint8* State = SDL_GetKeyboardState(NULL);

	int pointer = 1;

	while (running == 1) {

		player = 0;
		bot = random();
		draw = 0, win = 0, defeat = 0;

		SDL_SetRenderDrawColor(ren, 200, 200, 200, 0);
		SDL_RenderClear(ren);
		SDL_RenderCopy(ren, textBackground, NULL, NULL);

		position.x = 300, position.y = 280;
		SDL_RenderCopy(ren, textRockScissorsPaper, &srcRock, &position);
		position.x = 600, position.y = 280;
		SDL_RenderCopy(ren, textRockScissorsPaper, &srcScissors, &position);
		position.x = 900, position.y = 280;
		SDL_RenderCopy(ren, textRockScissorsPaper, &srcPaper, &position);

		if (pointer == 1) {
			arrowPosition.x = 300 - 15, arrowPosition.y = 430;
			SDL_RenderCopy(ren, textArrowUp, NULL, &arrowPosition);
		}
		if (pointer == 2) {
			arrowPosition.x = 600 - 15, arrowPosition.y = 430;
			SDL_RenderCopy(ren, textArrowUp, NULL, &arrowPosition);
		}
		if (pointer == 3) {
			arrowPosition.x = 900 - 15, arrowPosition.y = 430;
			SDL_RenderCopy(ren, textArrowUp, NULL, &arrowPosition);
		}

		while (SDL_PollEvent(&ev) != NULL) {
			SDL_PollEvent(&ev);
			isPressed = pressedEnter();

			if (pointer == 1 and State[SDL_SCANCODE_RETURN] and isPressed)
				player = Rock;
			if (pointer == 2 and State[SDL_SCANCODE_RETURN] and isPressed)
				player = Scissors;
			if (pointer == 3 and State[SDL_SCANCODE_RETURN] and isPressed)
				player = Paper;

			if (State[SDL_SCANCODE_D])
				pointer++;
			if (State[SDL_SCANCODE_A])
				pointer--;
		}
		if (pointer == 4)
			pointer = 1;
		if (pointer == 0)
			pointer = 3;
		if (player != 0) {
			if (player == Rock and bot == Rock)
				draw = 1;
			if (player == Rock and bot == Scissors)
				win = 1;
			if (player == Rock and bot == Paper)
				defeat = 1;
			if (player == Scissors and bot == Rock)
				defeat = 1;
			if (player == Scissors and bot == Scissors)
				draw = 1;
			if (player == Scissors and bot == Paper)
				win = 1;
			if (player == Paper and bot == Rock)
				win = 1;
			if (player == Paper and bot == Scissors)
				defeat = 1;
			if (player == Paper and bot == Paper)
				draw = 1;

			if (win == 1) {
				winningStreak += 1;
				while (running == 1) {
					SDL_SetRenderDrawColor(ren, 200, 200, 200, 0);
					SDL_RenderClear(ren);
					SDL_RenderCopy(ren, textBackground, NULL, NULL);

					position.w = 300;
					position.x = 1280 / 2 - position.w/2, position.y = 720 / 2 - position.h/2;
					SDL_RenderCopy(ren, textWinDefeatDraw, &srcWin, &position);

					render_result(ren);

					while (SDL_PollEvent(&ev) != NULL) {
						SDL_PollEvent(&ev);
						isPressed = pressedEnter();
						if (State[SDL_SCANCODE_RETURN] and isPressed)
							running = 0;
					}
					isPressed = 0;
					SDL_RenderPresent(ren);
					SDL_Delay(17);
				}
			}
			if (draw == 1) {
				while (running == 1) {
					SDL_SetRenderDrawColor(ren, 200, 200, 200, 0);
					SDL_RenderClear(ren);
					SDL_RenderCopy(ren, textBackground, NULL, NULL);

					position.w = 300;
					position.x = 1280 / 2 - position.w/2, position.y = 720 / 2 - position.h/2;
					SDL_RenderCopy(ren, textWinDefeatDraw, &srcDraw, &position);

					render_result(ren);

					while (SDL_PollEvent(&ev) != NULL) {
						SDL_PollEvent(&ev);
						isPressed = pressedEnter();
						if (State[SDL_SCANCODE_RETURN] and isPressed)
							running = 0;
					}
					isPressed = 0;
					SDL_RenderPresent(ren);
					SDL_Delay(17);
				}
			}
			if (defeat == 1) {
				winningStreak = 0;
				while (running == 1) {
					SDL_SetRenderDrawColor(ren, 200, 200, 200, 0);
					SDL_RenderClear(ren);
					SDL_RenderCopy(ren, textBackground, NULL, NULL);

					position.w = 300;
					position.x = 1280 / 2 - position.w/2, position.y = 720 / 2 - position.h/2;
					SDL_RenderCopy(ren, textWinDefeatDraw, &srcDefeat, &position);

					render_result(ren);

					while (SDL_PollEvent(&ev) != NULL) {
						SDL_PollEvent(&ev);
						isPressed = pressedEnter();
						if (State[SDL_SCANCODE_RETURN] and isPressed)
							running = 0;
					}
					isPressed = 0;
					SDL_RenderPresent(ren);
					SDL_Delay(17);
				}
			}
		}
		isPressed = 0;

		SDL_RenderPresent(ren);
		SDL_Delay(17);
	}
	if (running == 0) {
		SDL_DestroyTexture(textArrowUp);
		SDL_DestroyTexture(textBackground);
		SDL_DestroyTexture(textRockScissorsPaper);
		SDL_DestroyTexture(textWinDefeatDraw);
	}
}

void render_result(SDL_Renderer* ren) {
	SDL_Surface* surfRockScissorsPaper = IMG_Load("sprites\\minigames\\rock_scissors_paper.png");
	SDL_Texture* textRockScissorsPaper = SDL_CreateTextureFromSurface(ren, surfRockScissorsPaper);
	SDL_FreeSurface(surfRockScissorsPaper);

	SDL_Rect position = { 0, 0, 150, 150 };
	position.y = 720 / 2 - position.h / 2;
	if (player == Rock) {
		position.x = 300;
		SDL_RenderCopy(ren, textRockScissorsPaper, &srcRock, &position);
	}
	if (player == Scissors) {
		position.x = 300;
		SDL_RenderCopy(ren, textRockScissorsPaper, &srcScissors, &position);
	}
	if (player == Paper) {
		position.x = 300;
		SDL_RenderCopy(ren, textRockScissorsPaper, &srcPaper, &position);
	}
	if (bot == Rock) {
		position.x = 800;
		SDL_RenderCopy(ren, textRockScissorsPaper, &srcRock, &position);
	}
	if (bot == Scissors) {
		position.x = 800;
		SDL_RenderCopy(ren, textRockScissorsPaper, &srcScissors, &position);
	}
	if (bot == Paper) {
		position.x = 800;
		SDL_RenderCopy(ren, textRockScissorsPaper, &srcPaper, &position);
	}

	SDL_DestroyTexture(textRockScissorsPaper);
}

int random() {
	return rand() % (3 - 1 + 1) + 1;
}