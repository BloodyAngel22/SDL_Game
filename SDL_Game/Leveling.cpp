#define ATTACK 1
#define HEALTH 2
#define PROTECTION 3
#define ABILITYATTACK 4
#include "Models.h"
#include <stdio.h>


void level_up() {

	if ((hero.experience >= hero.levelUp) and (hero.level <= hero.maxLevel)) {
		hero.level += 1;
		hero.pointsLevel += 4;
		hero.experience = 0;
		hero.levelUp = hero.levelUp * 1.5;
		printf("Level up\n");
	}
}

void character_leveling() {
	int choicheParameter = 0;
	if (choicheParameter == ATTACK and hero.pointsLevel != 0) {
		hero.Attack = hero.Attack * 1.4;
		hero.pointsLevel--;
	}
	if (choicheParameter == HEALTH and hero.pointsLevel != 0) {
		hero.Health = hero.Health * 1.15;
		hero.pointsLevel--;
	}
	if (choicheParameter == PROTECTION and hero.pointsLevel != 0) {
		hero.Defense = hero.Defense * 2;
		hero.pointsLevel--;
	}
	if (choicheParameter == ABILITYATTACK and hero.pointsLevel != 0) {

		hero.pointsLevel--;
	}
}
