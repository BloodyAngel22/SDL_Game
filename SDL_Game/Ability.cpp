#include <stdio.h>
#include "Models.h"

int abilityDamage;


void Fireboll() {
	abilityDamage = 30;
	if (hero.Mana >= 15)
		hero.Mana -= 15;
	else printf("not enough mana");
}

void Lightning() {
	abilityDamage = 12;
	if (hero.Mana >= 20)
		hero.Mana -= 20;
	else printf("not enough mana");
}