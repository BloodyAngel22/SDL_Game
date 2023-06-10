#include "SDL_general.h"
#include "Battle.h"
#include "Models.h"
#include <iostream>

extern int counterKilledEnemies = 0;
extern int curQuest = 1;
extern int questFlag = 0;
extern int keyCheckBat = 0;
extern int keyCheckGoblin = 0;
void quest(SDL_Renderer* ren) {//Взять квест

#pragma region Texture
	//Отрисовка диалогов квестов
	SDL_Surface* surfQuest1 = IMG_Load("sprites\\npc\\quest1.png");
	SDL_Texture* textQuest1 = SDL_CreateTextureFromSurface(ren, surfQuest1);
	SDL_FreeSurface(surfQuest1);
	//
	SDL_Surface* surfQuest2 = IMG_Load("sprites\\npc\\quest2.png");
	SDL_Texture* textQuest2 = SDL_CreateTextureFromSurface(ren, surfQuest2);
	SDL_FreeSurface(surfQuest2);
	//
	SDL_Surface* surfQuest3 = IMG_Load("sprites\\npc\\quest3.png");
	SDL_Texture* textQuest3 = SDL_CreateTextureFromSurface(ren, surfQuest3);
	SDL_FreeSurface(surfQuest3);
	//
	SDL_Surface* surfFinalAward = IMG_Load("sprites\\npc\\final_award.png");
	SDL_Texture* textFinalAward = SDL_CreateTextureFromSurface(ren, surfFinalAward);
	SDL_FreeSurface(surfFinalAward);
	//
	SDL_Surface* surfFinalDialogue = IMG_Load("sprites\\npc\\final_dialogue.png");
	SDL_Texture* textFinalDialogue = SDL_CreateTextureFromSurface(ren, surfFinalDialogue);
	SDL_FreeSurface(surfFinalDialogue);
	SDL_Rect dstQuest = {0, 360, 1280, 360};
	//
	SDL_Surface* surfAward = IMG_Load("sprites\\npc\\award.png");
	SDL_Texture* textAward = SDL_CreateTextureFromSurface(ren, surfAward);
	SDL_FreeSurface(surfAward);
#pragma endregion

	const Uint8* state = SDL_GetKeyboardState(NULL);
	SDL_Event ev;

	//логика при активном квесте

	if (curQuest == 1 and counterKilledEnemies < 5 and questFlag) {
		SDL_RenderCopy(ren, textQuest1, NULL, &dstQuest);
		keyCheckBat = 1;
	}
	if (curQuest == 2 and counterKilledEnemies < 5 and questFlag) {
		SDL_RenderCopy(ren, textQuest2, NULL, &dstQuest);
	}
	if (curQuest == 3 and counterKilledEnemies < 7 and questFlag) {
		SDL_RenderCopy(ren, textQuest3, NULL, &dstQuest);
		keyCheckGoblin = 1;
	}
	if (curQuest == 4 and questFlag) {
		SDL_RenderCopy(ren, textFinalDialogue, NULL, &dstQuest);
	}
	//логика при получении награды за квест
	if (curQuest == 1 and counterKilledEnemies >= 5 and questFlag) {
		hero.Gold += 100;
		counterKilledEnemies = 0;
		curQuest = 2;
		questFlag = 0;
	}
	if (curQuest == 2 and counterKilledEnemies >= 5 and questFlag) {
		hero.Gold += 200;
		counterKilledEnemies = 0;
		curQuest = 3;
		questFlag = 0;
	}
	if (curQuest == 3 and counterKilledEnemies >= 7 and questFlag) {
		hero.Gold += 300;
		counterKilledEnemies = 0;
		curQuest = 4;
		questFlag = 0;
	}
	if (questFlag == 0) {
		SDL_RenderCopy(ren, textAward, NULL, &dstQuest);
	}
	SDL_RenderPresent(ren);
	while (true) {
		SDL_PollEvent(&ev);
		isPressed = pressedEnter();
		if (state[SDL_SCANCODE_RETURN] and isPressed) {
			SDL_DestroyTexture(textFinalAward);
			SDL_DestroyTexture(textFinalDialogue);
			SDL_DestroyTexture(textQuest1);
			SDL_DestroyTexture(textQuest2);
			SDL_DestroyTexture(textQuest3);
			SDL_DestroyTexture(textAward);
			return;
		}
		isPressed = 0;
	}
}

void complete_the_quest(SDL_Renderer* ren) {//Прогресс квестов и отображение
	//Текстура окна квестов
#pragma region Texture
	SDL_Surface* surfQuest = IMG_Load("sprites\\npc\\quest_list.png");
	SDL_Texture* textQuest = SDL_CreateTextureFromSurface(ren, surfQuest);
	SDL_FreeSurface(surfQuest);
	//
	TTF_Font* questTTF = TTF_OpenFont("fonts\\BAUHS93.TTF", 75);
	char quest[100] = "Points";
	SDL_Surface* surfQuestTTF = TTF_RenderText_Blended(questTTF, quest, { 255, 255, 255, 255 });
	SDL_Texture* textQuestTTF = SDL_CreateTextureFromSurface(ren, surfQuestTTF);
	SDL_Rect size = { 0, 0, surfQuestTTF->w, surfQuestTTF->h };
	int xPoint = 500, yPoint = 50;
	SDL_Rect pointsTTF = { xPoint, yPoint, 400, 75 };
	SDL_FreeSurface(surfQuestTTF);
#pragma endregion

	const Uint8* state = SDL_GetKeyboardState(NULL);
	SDL_Event ev;

	while (true) {

		SDL_PollEvent(&ev);
		SDL_SetRenderDrawColor(ren, 200, 200, 200, 0);
		SDL_RenderClear(ren);
		SDL_RenderCopy(ren, textQuest, NULL, NULL);
		isPressed = pressedEscape();
		int killEnemies;
		if (curQuest == 1 and questFlag) {
			killEnemies = 5;
			xPoint = 200, yPoint = 150;
			pointsTTF = { xPoint, yPoint, 850, 100 };
			sprintf_s(quest, "Kill %d bats. Reward %d gold. Killed %d/%d", killEnemies, 100 ,counterKilledEnemies, killEnemies);
			surfQuestTTF = TTF_RenderText_Blended(questTTF, quest, { 255, 255, 255, 255 });
			size = { 0, 0, surfQuestTTF->w, surfQuestTTF->h };
			textQuestTTF = SDL_CreateTextureFromSurface(ren, surfQuestTTF);
			SDL_RenderCopy(ren, textQuestTTF, &size, &pointsTTF);
			SDL_FreeSurface(surfQuestTTF);
			SDL_DestroyTexture(textQuestTTF);
		}
		if (curQuest == 2 and questFlag) {
			killEnemies = 5;
			xPoint = 200, yPoint = 150;
			pointsTTF = { xPoint, yPoint, 850, 100 };
			sprintf_s(quest, "Kill %d bats. Reward %d gold. Killed %d/%d", killEnemies, 200, counterKilledEnemies, killEnemies );
			surfQuestTTF = TTF_RenderText_Blended(questTTF, quest, { 255, 255, 255, 255 });
			size = { 0, 0, surfQuestTTF->w, surfQuestTTF->h };
			textQuestTTF = SDL_CreateTextureFromSurface(ren, surfQuestTTF);
			SDL_RenderCopy(ren, textQuestTTF, &size, &pointsTTF);
			SDL_FreeSurface(surfQuestTTF);
			SDL_DestroyTexture(textQuestTTF);
		}
		if (curQuest == 3 and questFlag) {
			killEnemies = 7;
			xPoint = 200, yPoint = 150;
			pointsTTF = { xPoint, yPoint, 850, 100 };
			sprintf_s(quest, "Kill %d goblins. Reward %d gold. Killed %d/%d", killEnemies, 300, counterKilledEnemies, killEnemies);
			surfQuestTTF = TTF_RenderText_Blended(questTTF, quest, { 255, 255, 255, 255 });
			size = { 0, 0, surfQuestTTF->w, surfQuestTTF->h };
			textQuestTTF = SDL_CreateTextureFromSurface(ren, surfQuestTTF);
			SDL_RenderCopy(ren, textQuestTTF, &size, &pointsTTF);
			SDL_FreeSurface(surfQuestTTF);
			SDL_DestroyTexture(textQuestTTF);			
		}
		if (state[SDL_SCANCODE_ESCAPE] and isPressed) {
			SDL_DestroyTexture(textQuest);
			SDL_DestroyTexture(textQuestTTF);
			TTF_CloseFont(questTTF);
			return;
		}
		SDL_RenderPresent(ren);
		isPressed = 0;
	}
}