#include "Puzzle.h"
#include "Models.h"

extern int flagCode = 1;

void code_lock(SDL_Renderer* ren) {//Логика кодового замка
	if (flagCode) {
#pragma region Texture
		//
		SDL_Surface* surfR = IMG_Load("sprites\\puzzles\\R.png");
		SDL_Texture* textR = SDL_CreateTextureFromSurface(ren, surfR);
		SDL_FreeSurface(surfR);
		//
		SDL_Surface* surfX = IMG_Load("sprites\\puzzles\\X.png");
		SDL_Texture* textX = SDL_CreateTextureFromSurface(ren, surfX);
		SDL_FreeSurface(surfX);
		//
		SDL_Surface* surfM = IMG_Load("sprites\\puzzles\\M.png");
		SDL_Texture* textM = SDL_CreateTextureFromSurface(ren, surfM);
		SDL_FreeSurface(surfM);
		//
		SDL_Surface* surfN = IMG_Load("sprites\\puzzles\\N.png");
		SDL_Texture* textN = SDL_CreateTextureFromSurface(ren, surfN);
		SDL_FreeSurface(surfN);
		//
		SDL_Surface* surfO = IMG_Load("sprites\\puzzles\\O.png");
		SDL_Texture* textO = SDL_CreateTextureFromSurface(ren, surfO);
		SDL_FreeSurface(surfO);
		//
		SDL_Surface* surfP = IMG_Load("sprites\\puzzles\\P.png");
		SDL_Texture* textP = SDL_CreateTextureFromSurface(ren, surfP);
		SDL_FreeSurface(surfP);
		//
		SDL_Surface* surfA = IMG_Load("sprites\\puzzles\\A.png");
		SDL_Texture* textA = SDL_CreateTextureFromSurface(ren, surfA);
		SDL_FreeSurface(surfA);
		//
		SDL_Surface* surfB = IMG_Load("sprites\\puzzles\\B.png");
		SDL_Texture* textB = SDL_CreateTextureFromSurface(ren, surfB);
		SDL_FreeSurface(surfB);
		//
		SDL_Surface* surfD = IMG_Load("sprites\\puzzles\\D.png");
		SDL_Texture* textD = SDL_CreateTextureFromSurface(ren, surfD);
		SDL_FreeSurface(surfD);
		//
		SDL_Surface* surfE = IMG_Load("sprites\\puzzles\\E.png");
		SDL_Texture* textE = SDL_CreateTextureFromSurface(ren, surfE);
		SDL_FreeSurface(surfE);
		//
		SDL_Surface* surfENTER = IMG_Load("sprites\\puzzles\\ENTER.png");
		SDL_Texture* textENTER = SDL_CreateTextureFromSurface(ren, surfENTER);
		SDL_FreeSurface(surfENTER);
		//
		SDL_Surface* surfArrowUp = IMG_Load("sprites\\puzzles\\arrowUp.png");
		SDL_Texture* textArrowUp = SDL_CreateTextureFromSurface(ren, surfArrowUp);
		SDL_FreeSurface(surfArrowUp);
		//
		SDL_Surface* surfArrowDown = IMG_Load("sprites\\puzzles\\arrowDown.png");
		SDL_Texture* textArrowDown = SDL_CreateTextureFromSurface(ren, surfArrowDown);
		SDL_FreeSurface(surfArrowDown);
		//
		SDL_Surface* surfBackground = IMG_Load("sprites\\puzzles\\background.png");
		SDL_Texture* textBackground = SDL_CreateTextureFromSurface(ren, surfBackground);
		SDL_FreeSurface(surfBackground);
#pragma endregion
		int firstPtr = 2;
		int secondPtr = 2;
		int thirdPtr = 1;
		int fourthPtr = 2;
		int Enter = 0;
		SDL_Rect dstPtr = {0,0, 100,100};
		SDL_Rect dstArrow = { 0,0, 100, 50 };
		SDL_Rect dstEnter = { 0,0, 200, 100 };

		SDL_Event ev;
		SDL_PollEvent(&ev);
		const Uint8* State = SDL_GetKeyboardState(NULL);

		int pointer = 1;

		while (flagCode) {

			SDL_SetRenderDrawColor(ren, 200, 200, 200, 0);
			SDL_RenderClear(ren);
			SDL_RenderCopy(ren, textBackground, NULL, NULL);
			if (firstPtr != 0) {
				dstPtr.x = 200; dstPtr.y = 200;
				if (firstPtr == 1)
					SDL_RenderCopy(ren, textN, NULL, &dstPtr);
				if (firstPtr == 2) 
					SDL_RenderCopy(ren, textR, NULL, &dstPtr);
				if (firstPtr == 3) 
					SDL_RenderCopy(ren, textB, NULL, &dstPtr);
			}
			if (secondPtr != 0) {
				dstPtr.x = 400; dstPtr.y = 200;
				if (secondPtr == 1)
					SDL_RenderCopy(ren, textE, NULL, &dstPtr);
				if (secondPtr == 2)
					SDL_RenderCopy(ren, textO, NULL, &dstPtr);
				if (secondPtr == 3)
					SDL_RenderCopy(ren, textA, NULL, &dstPtr);
			}
			if (thirdPtr != 0) {
				dstPtr.x = 600; dstPtr.y = 200;
				if (thirdPtr == 1)
					SDL_RenderCopy(ren, textP, NULL, &dstPtr);
				if (thirdPtr == 2)
					SDL_RenderCopy(ren, textO, NULL, &dstPtr);
				if (thirdPtr == 3)
					SDL_RenderCopy(ren, textX, NULL, &dstPtr);
			}
			if (fourthPtr != 0) {
				dstPtr.x = 800; dstPtr.y = 200;
				if (fourthPtr == 1)
					SDL_RenderCopy(ren, textO, NULL, &dstPtr);
				if (fourthPtr == 2)
					SDL_RenderCopy(ren, textD, NULL, &dstPtr);
				if (fourthPtr == 3)
					SDL_RenderCopy(ren, textM, NULL, &dstPtr);
			}
			dstEnter.x = 1000; dstEnter.y = 200;
			SDL_RenderCopy(ren, textENTER, NULL, &dstEnter);
			
			if (pointer == 1) {
				dstArrow.x = 200; dstArrow.y = 150;
				SDL_RenderCopy(ren, textArrowUp, NULL, &dstArrow);
				dstArrow.x = 200; dstArrow.y = 300;
				SDL_RenderCopy(ren, textArrowDown, NULL, &dstArrow);
			}
			if (pointer == 2) {
				dstArrow.x = 400; dstArrow.y = 150;
				SDL_RenderCopy(ren, textArrowUp, NULL, &dstArrow);
				dstArrow.x = 400; dstArrow.y = 300;
				SDL_RenderCopy(ren, textArrowDown, NULL, &dstArrow);
			}
			if (pointer == 3) {
				dstArrow.x = 600; dstArrow.y = 150;
				SDL_RenderCopy(ren, textArrowUp, NULL, &dstArrow);
				dstArrow.x = 600; dstArrow.y = 300;
				SDL_RenderCopy(ren, textArrowDown, NULL, &dstArrow);
			}
			if (pointer == 4) {
				dstArrow.x = 800; dstArrow.y = 150;
				SDL_RenderCopy(ren, textArrowUp, NULL, &dstArrow);
				dstArrow.x = 800; dstArrow.y = 300;
				SDL_RenderCopy(ren, textArrowDown, NULL, &dstArrow);
			}

			Enter = 0;
			
			SDL_PollEvent(&ev);
			while (SDL_PollEvent(&ev) != NULL) {
					//Первая кнопка
					if (pointer == 1) {

						if (State[SDL_SCANCODE_W] or State[SDL_SCANCODE_UP]) {//вверх
							firstPtr += 1;
							if (firstPtr == 4) firstPtr = 1;
						}
						if (State[SDL_SCANCODE_S] or State[SDL_SCANCODE_DOWN]) {//вниз
							firstPtr -= 1;
							if (firstPtr == 0) firstPtr = 3;
						}
					}
					//Вторая кнопка
					if (pointer == 2) {
						if (State[SDL_SCANCODE_W] or State[SDL_SCANCODE_UP]) {//вверх
							secondPtr += 1;
							if (secondPtr == 4) secondPtr = 1;
						}
						if (State[SDL_SCANCODE_S] or State[SDL_SCANCODE_DOWN]) {//вниз
							secondPtr -= 1;
							if (secondPtr == 0) secondPtr = 3;
						}
					}
					//Третья кнопка
					if (pointer == 3) {

						if (State[SDL_SCANCODE_W] or State[SDL_SCANCODE_UP]) {//вверх
							thirdPtr += 1;
							if (thirdPtr == 4) thirdPtr = 1;
						}
						if (State[SDL_SCANCODE_S] or State[SDL_SCANCODE_DOWN]) {//вниз
							thirdPtr -= 1;
							if (thirdPtr == 0) thirdPtr = 3;
						}
					}
					//Четвертая
					if (pointer == 4) {

						if (State[SDL_SCANCODE_W] or State[SDL_SCANCODE_UP]) {//вверх
							fourthPtr += 1;
							if (fourthPtr == 4) fourthPtr = 1;
						}
						if (State[SDL_SCANCODE_S] or State[SDL_SCANCODE_DOWN]) {//вниз
							fourthPtr -= 1;
							if (fourthPtr == 0) fourthPtr = 3;
						}
					}
					//Кнопка для проверки кода
					if (State[SDL_SCANCODE_RETURN] and pointer == 5)
						Enter = 1;
					//Переход к другому сектору
					if (State[SDL_SCANCODE_D] or State[SDL_SCANCODE_RIGHT]) {
						pointer += 1;
						if (pointer == 6)
							pointer = 1;
					}
					if (State[SDL_SCANCODE_A] or State[SDL_SCANCODE_LEFT]) {
						pointer -= 1;
						if (pointer == 0)
							pointer = 5;
					}
				}
				//Код подошел
				if (firstPtr == 1 and secondPtr == 1 and thirdPtr == 1 and fourthPtr == 1 and pointer == 5 and State[SDL_SCANCODE_RETURN]) {
					flagCode = 0;
					hero.Gold += 300;
					SDL_DestroyTexture(textA);
					SDL_DestroyTexture(textArrowDown);
					SDL_DestroyTexture(textArrowUp);
					SDL_DestroyTexture(textB);
					SDL_DestroyTexture(textBackground);
					SDL_DestroyTexture(textD);
					SDL_DestroyTexture(textE);
					SDL_DestroyTexture(textENTER);
					SDL_DestroyTexture(textM);
					SDL_DestroyTexture(textO);
					SDL_DestroyTexture(textP);
					SDL_DestroyTexture(textR);
					SDL_DestroyTexture(textX);
					return;
				}
				if (State[SDL_SCANCODE_ESCAPE]) {
					SDL_DestroyTexture(textA);
					SDL_DestroyTexture(textArrowDown);
					SDL_DestroyTexture(textArrowUp);
					SDL_DestroyTexture(textB);
					SDL_DestroyTexture(textBackground);
					SDL_DestroyTexture(textD);
					SDL_DestroyTexture(textE);
					SDL_DestroyTexture(textENTER);
					SDL_DestroyTexture(textM);
					SDL_DestroyTexture(textO);
					SDL_DestroyTexture(textP);
					SDL_DestroyTexture(textR);
					SDL_DestroyTexture(textX);
					return;
				}
				SDL_RenderPresent(ren);
				SDL_Delay(17);
		}		
	}
}