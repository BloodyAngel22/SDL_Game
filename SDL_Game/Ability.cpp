#include <stdio.h>
#include "Models.h"

int abilityDamageLighting = 12, abilityDamageFireball = 30, abilityDamagePosion = 6;
extern bool posionEffect = false;
extern bool lightingEffect = false;

void Fireball() {
	abilityDamageFireball;
	if (hero.Mana >= 15) {
		hero.Mana -= 15;
		opponent.Health -= abilityDamageFireball;
	}
	else printf("not enough mana\n");
}

void Lightning() {
	int steps = 4;
	int DamageLighting = abilityDamageLighting * steps;
	if (hero.Mana >= 25 and lightingEffect == false) {
		lightingEffect = true;
		hero.Mana -= 25;
	}
	if (lightingEffect == true) {
		opponent.Health -= DamageLighting;
		steps--;
	}
	if (steps == 0) lightingEffect == false;
}

void Posion() {
	abilityDamagePosion;
	if (hero.Mana >= 18 and posionEffect == false) {
		posionEffect = true;
		hero.Mana -= 18;
	}
	else if(hero.Mana < 18) printf("not enough mana\n");
	if (posionEffect == true and opponent.Health <= 0)
		posionEffect = false;
	if (posionEffect == true) {
		opponent.Health -= abilityDamagePosion;
		abilityDamagePosion--;
	}
	if (abilityDamagePosion == 0)
		posionEffect = false;
}