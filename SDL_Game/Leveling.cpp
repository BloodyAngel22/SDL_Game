#define ATTACK 1
#define HEALTH 2
#define PROTECTION 3
#define ABILITYATTACK 4
#define EXIT 5
#include "Models.h"
#include "Ability.h"
#include <stdio.h>
#include <stdlib.h>
#include <SDL.h>


void level_up() {

	if ((hero.experience >= hero.levelUp) and (hero.level <= hero.maxLevel)) {
		hero.level += 1;
		hero.pointsLevel += 4;
		hero.experience = 0;
		hero.levelUp = hero.levelUp * 1.5;
		system("cls");
		printf("Level up\n");
	}
	if (hero.level % 3 == 0) {
		hero.pointsTree += 1;
		printf("pointsTree %d\n", hero.pointsTree);
	}
	if (hero.level % 10 == 0) {
		hero.pointsTree += 2;
		printf("pointsTree %d\n", hero.pointsTree);
	}
}

void character_leveling() {
	int choicheParameter = 0;
	SDL_Event ev;
	SDL_PollEvent(&ev);
	printf("Select devepmoment option\n");
	printf("Points %d\n", hero.pointsLevel);
	printf("1 - Attack\n2 - Health\n3 - Protection\n4 - AbilityAtack\nESC - EXIT\n");
	while (choicheParameter == 0) {
		while (SDL_PollEvent(&ev) != NULL) {
			switch (ev.type) {
			case SDL_KEYDOWN:
				switch (ev.key.keysym.scancode) {
				case SDL_SCANCODE_1:
					choicheParameter = ATTACK;
					break;
				case SDL_SCANCODE_2:
					choicheParameter = HEALTH;
					break;
				case SDL_SCANCODE_3:
					choicheParameter = PROTECTION;
					break;
				case SDL_SCANCODE_4:
					choicheParameter = ABILITYATTACK;
					break;
				case SDL_SCANCODE_ESCAPE:
					choicheParameter = EXIT;
					break;
				}
			}
		}
	}
	if (choicheParameter == EXIT) {
		system("cls");
		return;
	}
	if (hero.pointsLevel == 0) {
		system("cls");
		printf("You don't have points\n");
	}
	if (choicheParameter == ATTACK and hero.pointsLevel != 0) {
		hero.Attack = hero.Attack * 1.4;
		hero.maxAttack = hero.Attack * 1.4;
		system("cls");
		printf("Attack %d\n", hero.Attack);
		hero.pointsLevel--;
	}
	if (choicheParameter == HEALTH and hero.pointsLevel != 0) {
		hero.Health = hero.Health * 1.15;
		hero.maxHealth = hero.Health * 1.15;
		system("cls");
		printf("Health %d\n", hero.Health);
		hero.pointsLevel--;
	}
	if (choicheParameter == PROTECTION and hero.pointsLevel != 0) {
		hero.Defense = hero.Defense * 2;
		system("cls");
		printf("Defense %d\n", hero.Defense);
		hero.pointsLevel--;
	}
	if (choicheParameter == ABILITYATTACK and hero.pointsLevel != 0) {
		hero.Mana = hero.Mana * 1.3;
		hero.maxMana = hero.Mana * 1.3;
		abilityDamageFireball *= 1.3;
		abilityDamageLighting *= 1.2;
		abilityDamagePosion *= 1.2;
		system("cls");
		printf("Mana %d\n", hero.Mana);
		printf("abilityDamageFireball %d\n", abilityDamageFireball);
		printf("abilityDamageLighting %d\n", abilityDamageLighting);
		printf("abilityDamagePosion %d\n", abilityDamagePosion);
		hero.pointsLevel--;
	}
}

void skill_tree() {
	if (hero.pointsTree > 0) {
		hero.pointsTree--;
	}
	else printf("you don't have skill tree points\n");
}