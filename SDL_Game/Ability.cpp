#include <stdio.h>
#include "Models.h"
#include "Battle.h"

//int abilityDamageLighting = 12, abilityDamageFireball = 30, abilityDamagePosion = 6;
//extern bool posionEffect = false;
//extern bool lightingEffect = false;
//int choiceEnemy;
//
//void Fireball() {
//	abilityDamageFireball;
//	if (hero.Mana >= 15) {
//		hero.Mana -= 15;
//		if (choiceEnemy == 1)
//			enemy1.health -= abilityDamageFireball;
//		else if (choiceEnemy == 2)
//			enemy2.health -= abilityDamageFireball;
//		else if (choiceEnemy == 3)
//			enemy3.health -= abilityDamageFireball;
//	}
//	else printf("not enough mana\n");
//}
//
//void Lightning() {
//	int steps = 4;
//	int DamageLighting = abilityDamageLighting * steps;
//	if (hero.Mana >= 25 and lightingEffect == false) {
//		lightingEffect = true;
//		hero.Mana -= 25;
//	}
//	if (lightingEffect == true) {
//		enemy1.health -= DamageLighting;
//		steps--;
//	}
//	if (steps == 0) lightingEffect == false;
//}
//
//void Poison() {
//	abilityDamagePosion;
//	if (hero.Mana >= 18 and posionEffect == false) {
//		posionEffect = true;
//		hero.Mana -= 18;
//	}
//	else if(hero.Mana < 18) printf("not enough mana\n");
//	if (posionEffect == true and enemy1.health <= 0)
//		posionEffect = false;
//	if (posionEffect == true) {
//		enemy1.health -= abilityDamagePosion;
//		abilityDamagePosion--;
//	}
//	if (abilityDamagePosion == 0)
//		posionEffect = false;
//}