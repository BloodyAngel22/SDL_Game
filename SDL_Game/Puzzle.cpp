#include "Puzzle.h"
#include "Models.h"
#include "Battle.h"

extern int flagCode = 1;
extern int flagLamps = 1;
extern int flagRunes = 1;

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
		//
		SDL_Surface* surfEnterChoice = IMG_Load("sprites\\puzzles\\ENTER_choice.png");
		SDL_Texture* textEnterChoice = SDL_CreateTextureFromSurface(ren, surfEnterChoice);
		SDL_FreeSurface(surfEnterChoice);
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
			if (pointer != 5)
				SDL_RenderCopy(ren, textENTER, NULL, &dstEnter);
			if (pointer == 5)
				SDL_RenderCopy(ren, textEnterChoice, NULL, &dstEnter);
			
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
					SDL_DestroyTexture(textEnterChoice);
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
					SDL_DestroyTexture(textEnterChoice);
					return;
				}
				SDL_RenderPresent(ren);
				SDL_Delay(17);
		}		
	}
}

void lamps(SDL_Renderer* ren, SDL_Rect &dstLamp) {//Логика ламп
	if (flagLamps == 1) {
#pragma region Texture
		//
		SDL_Surface* surfBackground = IMG_Load("sprites\\puzzles\\background.png");
		SDL_Texture* textBackground = SDL_CreateTextureFromSurface(ren, surfBackground);
		SDL_FreeSurface(surfBackground);
		//
		SDL_Surface* surfArrowUp = IMG_Load("sprites\\puzzles\\arrowUp.png");
		SDL_Texture* textArrowUp = SDL_CreateTextureFromSurface(ren, surfArrowUp);
		SDL_FreeSurface(surfArrowUp);
		//
		SDL_Surface* surfArrowDown = IMG_Load("sprites\\puzzles\\arrowDown.png");
		SDL_Texture* textArrowDown = SDL_CreateTextureFromSurface(ren, surfArrowDown);
		SDL_FreeSurface(surfArrowDown);
		//Lamp off
		SDL_Rect dstLamp = { 0,0, 100, 100 };
		SDL_Surface* surfLampOff = IMG_Load("sprites\\puzzles\\extinguished_lamp.png");
		SDL_Texture* textLampOff = SDL_CreateTextureFromSurface(ren, surfLampOff);
		SDL_FreeSurface(surfLampOff);
		//Lamp on
		SDL_Surface* surfLampOn = IMG_Load("sprites\\puzzles\\lit_lamp.png");
		SDL_Texture* textLampOn = SDL_CreateTextureFromSurface(ren, surfLampOn);
		SDL_FreeSurface(surfLampOn);
		//
#pragma endregion
		int lamp1 = 0, lamp2 = 0, lamp3 = 0, lamp4 = 0, lamp5 = 0, lamp6 = 0;
		int pointer = 1;
		const Uint8* State = SDL_GetKeyboardState(NULL);
		SDL_Rect dstArrow = { 0,0, 100, 50 };
		SDL_Event ev;
		SDL_PollEvent(&ev);


		while (flagLamps) {

			SDL_SetRenderDrawColor(ren, 200, 200, 200, 0);
			SDL_RenderClear(ren);
			SDL_RenderCopy(ren, textBackground, NULL, NULL);


			if (pointer == 1) {
				dstArrow.x = 200; dstArrow.y = 250;
				SDL_RenderCopy(ren, textArrowUp, NULL, &dstArrow);
				dstArrow.x = 200; dstArrow.y = 400;
				SDL_RenderCopy(ren, textArrowDown, NULL, &dstArrow);

			}
			if (pointer == 2) {
				dstArrow.x = 350; dstArrow.y = 250;
				SDL_RenderCopy(ren, textArrowUp, NULL, &dstArrow);
				dstArrow.x = 350; dstArrow.y = 400;
				SDL_RenderCopy(ren, textArrowDown, NULL, &dstArrow);
			}
			if (pointer == 3) {
				dstArrow.x = 500; dstArrow.y = 250;
				SDL_RenderCopy(ren, textArrowUp, NULL, &dstArrow);
				dstArrow.x = 500; dstArrow.y = 400;
				SDL_RenderCopy(ren, textArrowDown, NULL, &dstArrow);
			}
			if (pointer == 4) {
				dstArrow.x = 650; dstArrow.y = 250;
				SDL_RenderCopy(ren, textArrowUp, NULL, &dstArrow);
				dstArrow.x = 650; dstArrow.y = 400;
				SDL_RenderCopy(ren, textArrowDown, NULL, &dstArrow);
			}
			if (pointer == 5) {
				dstArrow.x = 800; dstArrow.y = 250;
				SDL_RenderCopy(ren, textArrowUp, NULL, &dstArrow);
				dstArrow.x = 800; dstArrow.y = 400;
				SDL_RenderCopy(ren, textArrowDown, NULL, &dstArrow);
			}
			if (pointer == 6) {
				dstArrow.x = 950; dstArrow.y = 250;
				SDL_RenderCopy(ren, textArrowUp, NULL, &dstArrow);
				dstArrow.x = 950; dstArrow.y = 400;
				SDL_RenderCopy(ren, textArrowDown, NULL, &dstArrow);
			}

			while (SDL_PollEvent(&ev) != NULL) {
				SDL_PollEvent(&ev);
				if (pointer == 1 and State[SDL_SCANCODE_W]) {
					if (lamp2 == 1)
						lamp2 = 0;
					else
						lamp2 = 1;
				}
				if (pointer == 1 and State[SDL_SCANCODE_S]) {
					if (lamp2 == 1)
						lamp2 = 0;
					else
						lamp2 = 1;
				}
				if (pointer == 2 and State[SDL_SCANCODE_W]) {
					if (lamp1 == 1)
						lamp1 = 0;
					else 
						lamp1 = 1; 
					if (lamp3 == 1)
						lamp3 = 0;
					else
						lamp3 = 1;
				}
				if (pointer == 2 and State[SDL_SCANCODE_S]) {
					if (lamp1 == 1)
						lamp1 = 0;
					else
						lamp1 = 1;
					if (lamp3 == 1)
						lamp3 = 0;
					else
						lamp3 = 1;
				}
				if (pointer == 3 and State[SDL_SCANCODE_W]) {
					if (lamp1 == 1)
						lamp1 = 0;
					else
						lamp1 = 1;
				}
				if (pointer == 3 and State[SDL_SCANCODE_S]) {
					if (lamp1 == 1)
						lamp1 = 0;
					else
						lamp1 = 1;
				}
				if (pointer == 4 and State[SDL_SCANCODE_W]) {
					if (lamp6 == 1)
						lamp6 = 0;
					else lamp6 = 1;
				}
				if (pointer == 4 and State[SDL_SCANCODE_S]) {
					if (lamp6 == 1)
						lamp6 = 0;
					else lamp6 = 1;
				}
				if (pointer == 5 and State[SDL_SCANCODE_W]) {
					if (lamp4 == 1)
						lamp4 = 0;
					else lamp4 = 1;
					if (lamp6 == 1)
						lamp6 = 0;
					else lamp6 = 1;
				}
				if (pointer == 5 and State[SDL_SCANCODE_S]) {
					if (lamp4 == 1)
						lamp4 = 0;
					else lamp4 = 1;
					if (lamp6 == 1)
						lamp6 = 0;
					else lamp6 = 1;
				}
				if (pointer == 6 and State[SDL_SCANCODE_W]) {
					if (lamp5 == 1)
						lamp5 = 0;
					else lamp5 = 1;
				}
				if (pointer == 6 and State[SDL_SCANCODE_S]) {
					if (lamp5 == 1)
						lamp5 = 0;
					else lamp5 = 1;
				}

				if (State[SDL_SCANCODE_D])
					pointer += 1;
				if (State[SDL_SCANCODE_A])
					pointer -= 1;
			}

			if (pointer == 0)
				pointer = 6;
			if (pointer == 7)
				pointer = 1;

			if (lamp1 == 1) {
				dstLamp.x = 200, dstLamp.y = 300;
				SDL_RenderCopy(ren, textLampOn, NULL, &dstLamp);
			}
			else if (lamp1 == 0) {
				dstLamp.x = 200, dstLamp.y = 300;
				SDL_RenderCopy(ren, textLampOff, NULL, &dstLamp);
			}
			if (lamp2 == 1) {
				dstLamp.x = 350, dstLamp.y = 300;
				SDL_RenderCopy(ren, textLampOn, NULL, &dstLamp);
			}
			else if (lamp2 == 0) {
				dstLamp.x = 350, dstLamp.y = 300;
				SDL_RenderCopy(ren, textLampOff, NULL, &dstLamp);
			}
			if (lamp3 == 1) {
				dstLamp.x = 500, dstLamp.y = 300;
				SDL_RenderCopy(ren, textLampOn, NULL, &dstLamp);
			}
			else {
				dstLamp.x = 500, dstLamp.y = 300;
				SDL_RenderCopy(ren, textLampOff, NULL, &dstLamp);
			}
			if (lamp4 == 1) {
				dstLamp.x = 650, dstLamp.y = 300;
				SDL_RenderCopy(ren, textLampOn, NULL, &dstLamp);
			}
			else {
				dstLamp.x = 650, dstLamp.y = 300;
				SDL_RenderCopy(ren, textLampOff, NULL, &dstLamp);
			}
			if (lamp5 == 1) {
				dstLamp.x = 800, dstLamp.y = 300;
				SDL_RenderCopy(ren, textLampOn, NULL, &dstLamp);
			}
			else {
				dstLamp.x = 800, dstLamp.y = 300;
				SDL_RenderCopy(ren, textLampOff, NULL, &dstLamp);
			}
			if (lamp6 == 1) {
				dstLamp.x = 950, dstLamp.y = 300;
				SDL_RenderCopy(ren, textLampOn, NULL, &dstLamp);
			}
			else {
				dstLamp.x = 950, dstLamp.y = 300;
				SDL_RenderCopy(ren, textLampOff, NULL, &dstLamp);
			}


			if (State[SDL_SCANCODE_ESCAPE]) {
				SDL_DestroyTexture(textBackground);
				SDL_DestroyTexture(textArrowUp);
				return;
			}

			if (lamp1 and lamp2 and lamp3 and lamp4 and lamp5 and lamp6) {
				flagLamps = 0;
				SDL_DestroyTexture(textBackground);
				SDL_DestroyTexture(textArrowUp);
				return;
			}
			SDL_RenderPresent(ren);
			SDL_Delay(50);
		}
	}
}

void runes_puzzle(SDL_Renderer* ren) {
	if (flagRunes) {
		//Texture
		SDL_Surface* surfRunesPuzzle = IMG_Load("sprites\\puzzles\\puzzle3.png");
		SDL_Texture* textRunesPuzzle = SDL_CreateTextureFromSurface(ren, surfRunesPuzzle);
		SDL_FreeSurface(surfRunesPuzzle);
		//
		SDL_Surface* surfBackground = IMG_Load("sprites\\puzzles\\background.png");
		SDL_Texture* textBackground = SDL_CreateTextureFromSurface(ren, surfBackground);
		SDL_FreeSurface(surfBackground);
		//
		SDL_Surface* surfArrowUp = IMG_Load("sprites\\puzzles\\arrowUp.png");
		SDL_Texture* textArrowUp = SDL_CreateTextureFromSurface(ren, surfArrowUp);
		SDL_FreeSurface(surfArrowUp);
		//
		SDL_Surface* surfArrowDown = IMG_Load("sprites\\puzzles\\arrowDown.png");
		SDL_Texture* textArrowDown = SDL_CreateTextureFromSurface(ren, surfArrowDown);
		SDL_FreeSurface(surfArrowDown);
		//Options
		SDL_Rect dstRunesRect[5];
		for (int i = 0; i < 5; i++) {
			dstRunesRect[i].w = 100, dstRunesRect[i].h = 100; dstRunesRect[i].y = 300;
		}
		dstRunesRect[0].x = 200;
		dstRunesRect[1].x = 400;
		dstRunesRect[2].x = 600;
		dstRunesRect[3].x = 800;
		dstRunesRect[4].x = 1000;
		SDL_Rect srcRunesRect[9];
		srcRunesRect[0].x = 0, srcRunesRect[0].y = 34; srcRunesRect[0].w = 182, srcRunesRect[0].h = 147;
		srcRunesRect[1].x = 234, srcRunesRect[1].y = 19; srcRunesRect[1].w = 189, srcRunesRect[1].h = 175;
		srcRunesRect[2].x = 480, srcRunesRect[2].y = 15; srcRunesRect[2].w = 168, srcRunesRect[2].h = 179;
		srcRunesRect[3].x = 680, srcRunesRect[3].y = 20; srcRunesRect[3].w = 200, srcRunesRect[3].h = 177;
		srcRunesRect[4].x = 945, srcRunesRect[4].y = 20; srcRunesRect[4].w = 168, srcRunesRect[4].h = 175;
		srcRunesRect[5].x = 1180, srcRunesRect[5].y = 32; srcRunesRect[5].w = 180, srcRunesRect[5].h = 164;
		srcRunesRect[6].x = 1390, srcRunesRect[6].y = 40; srcRunesRect[6].w = 206, srcRunesRect[6].h = 142;
		srcRunesRect[7].x = 1640, srcRunesRect[7].y = 18; srcRunesRect[7].w = 187, srcRunesRect[7].h = 181;
		srcRunesRect[8].x = 1880, srcRunesRect[8].y = 20; srcRunesRect[8].w = 211, srcRunesRect[8].h = 182;

		int RunePtr1 = 1, RunePtr2 = 1, RunePtr3 = 1, RunePtr4 = 1, RunePtr5 = 1;
		int pointer = 1;
		int image = 1;

		int code[5] = { 5,8,2,1,9 };

		int row = 1; int col = 1;

		const Uint8* State = SDL_GetKeyboardState(NULL);
		SDL_Rect dstArrow = { 0,0, 100, 50 };
		SDL_Event ev;
		SDL_PollEvent(&ev);

		//Event
		while (flagRunes) {

			SDL_SetRenderDrawColor(ren, 200, 200, 200, 0);
			SDL_RenderClear(ren);
			SDL_RenderCopy(ren, textBackground, NULL, NULL);


			while (SDL_PollEvent(&ev) != NULL) {
				SDL_PollEvent(&ev);

				if (pointer == 1 and State[SDL_SCANCODE_W]) {
					RunePtr1 += 1;
					if (RunePtr1 == 10)
						RunePtr1 = 1;
				}
				if (pointer == 1 and State[SDL_SCANCODE_S]) {
					RunePtr1 -= 1;
					if (RunePtr1 == 0)
						RunePtr1 = 9;
				}
				if (pointer == 2 and State[SDL_SCANCODE_W]) {
					RunePtr2 += 1;
					if (RunePtr2 == 10)
						RunePtr2 = 1;
				}
				if (pointer == 2 and State[SDL_SCANCODE_S]) {
					RunePtr2 -= 1;
					if (RunePtr2 == 0)
						RunePtr2 = 9;
				}
				if (pointer == 3 and State[SDL_SCANCODE_W]) {
					RunePtr3 += 1;
					if (RunePtr3 == 10)
						RunePtr3 = 1;
				}
				if (pointer == 3 and State[SDL_SCANCODE_S]) {
					RunePtr3 -= 1;
					if (RunePtr3 == 0)
						RunePtr3 = 9;
				}
				if (pointer == 4 and State[SDL_SCANCODE_W]) {
					RunePtr4 += 1;
					if (RunePtr4 == 10)
						RunePtr4 = 1;
				}
				if (pointer == 4 and State[SDL_SCANCODE_S]) {
					RunePtr4 -= 1;
					if (RunePtr4 == 0)
						RunePtr4 = 9;
				}
				if (pointer == 5 and State[SDL_SCANCODE_W]) {
					RunePtr5 += 1;
					if (RunePtr5 == 10)
						RunePtr5 = 1;
				}
				if (pointer == 5 and State[SDL_SCANCODE_S]) {
					RunePtr5 -= 1;
					if (RunePtr5 == 0)
						RunePtr5 = 9;
				}


				if (State[SDL_SCANCODE_D]) {
					pointer += 1;
					if (pointer == 6)
						pointer = 1;
				}
				if (State[SDL_SCANCODE_A]) {
					pointer -= 1;
					if (pointer == 0)
						pointer = 5;
				}

				if (State[SDL_SCANCODE_ESCAPE]) {
					SDL_DestroyTexture(textArrowDown);
					SDL_DestroyTexture(textArrowUp);
					SDL_DestroyTexture(textBackground);
					SDL_DestroyTexture(textRunesPuzzle);
					return;
				}
			}

			if (RunePtr1 != 0) {
				if (pointer == 1) {
					dstArrow.x = dstRunesRect[0].x, dstArrow.y = dstRunesRect[0].y - 50;
					SDL_RenderCopy(ren, textArrowUp, NULL, &dstArrow);
					dstArrow.x = dstRunesRect[0].x, dstArrow.y = dstRunesRect[0].y + 100;
					SDL_RenderCopy(ren, textArrowDown, NULL, &dstArrow);
				}
				for (int i = 1; i <= 9; i++) {
					if (RunePtr1 == i) {
						SDL_RenderCopy(ren, textRunesPuzzle, &srcRunesRect[i - 1], &dstRunesRect[0]);
					}
				}
			}
			if (RunePtr2 != 0) {
				if (pointer == 2) {
					dstArrow.x = dstRunesRect[1].x, dstArrow.y = dstRunesRect[1].y - 50;
					SDL_RenderCopy(ren, textArrowUp, NULL, &dstArrow);
					dstArrow.x = dstRunesRect[1].x, dstArrow.y = dstRunesRect[1].y + 100;
					SDL_RenderCopy(ren, textArrowDown, NULL, &dstArrow);
				}
				for (int i = 1; i <= 9; i++) {
					if (RunePtr2 == i) {
						SDL_RenderCopy(ren, textRunesPuzzle, &srcRunesRect[i - 1], &dstRunesRect[1]);
					}
				}
			}
			if (RunePtr3 != 0) {
				if (pointer == 3) {
					dstArrow.x = dstRunesRect[2].x, dstArrow.y = dstRunesRect[2].y - 50;
					SDL_RenderCopy(ren, textArrowUp, NULL, &dstArrow);
					dstArrow.x = dstRunesRect[2].x, dstArrow.y = dstRunesRect[2].y + 100;
					SDL_RenderCopy(ren, textArrowDown, NULL, &dstArrow);
				}
				for (int i = 1; i <= 9; i++) {
					if (RunePtr3 == i) {
						SDL_RenderCopy(ren, textRunesPuzzle, &srcRunesRect[i - 1], &dstRunesRect[2]);
					}
				}
			}
			if (RunePtr4 != 0) {
				if (pointer == 4) {
					dstArrow.x = dstRunesRect[3].x, dstArrow.y = dstRunesRect[3].y - 50;
					SDL_RenderCopy(ren, textArrowUp, NULL, &dstArrow);
					dstArrow.x = dstRunesRect[3].x, dstArrow.y = dstRunesRect[3].y + 100;
					SDL_RenderCopy(ren, textArrowDown, NULL, &dstArrow);
				}
				for (int i = 1; i <= 9; i++) {
					if (RunePtr4 == i) {
						SDL_RenderCopy(ren, textRunesPuzzle, &srcRunesRect[i - 1], &dstRunesRect[3]);
					}
				}
			}
			if (RunePtr5 != 0) {
				if (pointer == 5) {
					dstArrow.x = dstRunesRect[4].x, dstArrow.y = dstRunesRect[4].y - 50;
					SDL_RenderCopy(ren, textArrowUp, NULL, &dstArrow);
					dstArrow.x = dstRunesRect[4].x, dstArrow.y = dstRunesRect[4].y + 100;
					SDL_RenderCopy(ren, textArrowDown, NULL, &dstArrow);
				}
				for (int i = 1; i <= 9; i++) {
					if (RunePtr5 == i) {
						SDL_RenderCopy(ren, textRunesPuzzle, &srcRunesRect[i - 1], &dstRunesRect[4]);
					}
				}
			}

			if (RunePtr1 == 5 and RunePtr2 == 8 and RunePtr3 == 2 and RunePtr4 == 1 and RunePtr5 == 9) {
				flagRunes = 0;
				SDL_DestroyTexture(textArrowDown);
				SDL_DestroyTexture(textArrowUp);
				SDL_DestroyTexture(textBackground);
				SDL_DestroyTexture(textRunesPuzzle);
				return;
				//win
			}

			SDL_RenderPresent(ren);
			SDL_Delay(50);
		}
	}
}

void nameplate(SDL_Renderer* ren) {
	//Nameplate
	SDL_Surface* surfNameplate = IMG_Load("sprites\\puzzles\\nameplate.png");
	SDL_Texture* textNameplate = SDL_CreateTextureFromSurface(ren, surfNameplate);
	SDL_FreeSurface(surfNameplate);

	const Uint8* State = SDL_GetKeyboardState(NULL);
	SDL_Event ev;
	SDL_PollEvent(&ev);

	while (true) {
		SDL_SetRenderDrawColor(ren, 200, 200, 200, 0);
		SDL_RenderClear(ren);
		SDL_RenderCopy(ren, textNameplate, NULL, NULL);

		while (SDL_PollEvent(&ev) != NULL) {
		isPressed = pressedEnter();
			SDL_PollEvent(&ev);

			if (State[SDL_SCANCODE_ESCAPE]) {
				SDL_DestroyTexture(textNameplate);
				return;
			}
			if (State[SDL_SCANCODE_RETURN] and isPressed) {
				SDL_DestroyTexture(textNameplate);
				return;
			}
		}

		SDL_RenderPresent(ren);
		isPressed = 0;
	}
}

void hint(SDL_Renderer* ren) {
	//Hint
	SDL_Surface* surfHint = IMG_Load("sprites\\puzzles\\hint.png");
	SDL_Texture* textHint = SDL_CreateTextureFromSurface(ren, surfHint);
	SDL_FreeSurface(surfHint);

	const Uint8* State = SDL_GetKeyboardState(NULL);
	SDL_Event ev;
	SDL_PollEvent(&ev);

	while (true) {
		SDL_SetRenderDrawColor(ren, 200, 200, 200, 0);
		SDL_RenderClear(ren);
		SDL_RenderCopy(ren, textHint, NULL, NULL);

		while (SDL_PollEvent(&ev) != NULL) {
			isPressed = pressedEnter();
			SDL_PollEvent(&ev);

			if (State[SDL_SCANCODE_ESCAPE]) {
				SDL_DestroyTexture(textHint);
				return;
			}
			if (State[SDL_SCANCODE_RETURN] and isPressed) {
				SDL_DestroyTexture(textHint);
				return;
			}
		}

		SDL_RenderPresent(ren);
		isPressed = 0;
	}
}