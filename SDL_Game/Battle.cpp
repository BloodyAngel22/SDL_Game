#include <stdio.h>
#include <stdlib.h>
#include "Models.h"
#include "Leveling.h"

int ratio;
Character hero;
Enemy opponent;

void MenuBattle(); void StartBattle(); void Battle();

void MenuBattle() {
	int choiche;
	StartBattle();
	while ((hero.Health > 0) and (opponent.Health > 0)) {
		printf("1 - Battle\n2 - Ability\n3 - Inventory\n4 - Escape\n");
		scanf_s("%d", &choiche);
		if (choiche == 1) {
			system("cls");
			printf("%d\n", opponent.Health);
			Battle();
		}
	}
}

void Battle() {
	if (hero.Health > 0)
		opponent.Health -= hero.Attack;
	if (opponent.Health <= 0) {
		printf("%d\n", opponent.Health);
		hero.experience += opponent.experienceEnemy;
		if (hero.experience >= hero.levelUp)
			level_up();
	}
	if (opponent.Health > 0)
		hero.Health -= opponent.Attack;
	if (hero.Health <= 0)
		exit(1);
}

void StartBattle() {
	ratio = hero.AtSpeed / opponent.AtSpeed;
	if (hero.AtSpeed > opponent.AtSpeed) {
		if (ratio >= 2)
			opponent.Health -= hero.Attack * ratio;
		else if (ratio == 1)
			opponent.Health -= hero.Attack;
	}
	if (hero.AtSpeed < opponent.AtSpeed) {
		if (ratio >= 2)
			hero.Health -= opponent.Attack * ratio;
		else if (ratio == 1)
			hero.Health -= opponent.Attack;
	}

}

int main() {
	MenuBattle();
}