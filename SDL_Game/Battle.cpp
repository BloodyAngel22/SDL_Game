#include <stdio.h>
#include <stdlib.h>
#include "Models.h"
#include "Leveling.h"
#include "Ability.h"

int ratio;
Character hero;
Enemy opponent;

void MenuBattle(); void StartBattle(); void Battle(); int escape();

void MenuBattle() {
	int choiche;
	StartBattle();
	while ((hero.Health > 0) and (opponent.Health > 0)) {
		printf("Health %d, Attack %d, Mana %d\n", hero.Health, hero.Attack, hero.Mana);
		printf("1 - Battle\n2 - Ability\n3 - Inventory\n4 - Escape\n");
		scanf_s("%d", &choiche);
		if (choiche == 1) {
			system("cls");
			Battle();
			if (posionEffect == true) Posion();
			printf("%d\n", opponent.Health);
		}
		if (choiche == 2) {
			system("cls");
			int choiceSpell;
			printf("1 - Firebolt\n2 - Lightning\n3 - Posion\n");
			scanf_s("%d", &choiceSpell);
			if (choiceSpell == 1){
				Fireball();
				printf("%d\n", opponent.Health);
				hero.Health -= opponent.Attack;
				if (hero.Health <= 0)
					exit(1);
			}
			else if (choiceSpell == 2){
				Lightning();
				printf("%d\n", opponent.Health);
				hero.Health -= opponent.Attack;
				if (hero.Health <= 0)
					exit(1);
			}
			else if (choiceSpell == 3){
				Posion();
				printf("%d\n", opponent.Health);
				hero.Health -= opponent.Attack;
				if (hero.Health <= 0)
					exit(1);
			}
			if (opponent.Health <= 0) {
				printf("%d\n", opponent.Health);
				hero.experience += opponent.experienceEnemy;
				if (hero.experience >= hero.levelUp)
					level_up();
			}
		}
		if (choiche == 3);
		if (choiche == 4) {
			int storageEscape = escape();
			if (65 >= storageEscape) {
				printf("You managed to escape\n");
				opponent.Health = 0;
			}
			else { 
				printf("You failed to escape\n"); 
				hero.Health -= opponent.Attack;
				printf("the enemy has damaged you %d\n", opponent.Attack);
				if (hero.Health <= 0)
					exit(1);
			}
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
		printf("Health Enemy %d\n", opponent.Health);
		if (opponent.Health <= 0) {
			printf("%d\n", opponent.Health);
			hero.experience += opponent.experienceEnemy;
			if (hero.experience >= hero.levelUp)
				level_up();
		}
	}
	if (hero.AtSpeed < opponent.AtSpeed) {
		if (ratio >= 2)
			hero.Health -= opponent.Attack * ratio;
		else if (ratio == 1)
			hero.Health -= opponent.Attack;
	}

}

void recovery_character() {
	hero.Health = hero.maxHealth;
	hero.Mana = hero.maxMana;
}

void recovery_enemy() {
	opponent.Health = opponent.maxHealth;
}

int escape() {
	return rand() % 100;
}

//int main() {
//	MenuBattle();
//}