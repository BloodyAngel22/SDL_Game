#include <stdio.h>
#include <stdlib.h>
#include "Items.h"
#include "Models.h"


void Shop() {
	int purchasedWeapons[100] = { StWeapon.boughtWeapon1, StWeapon.boughtWeapon2,
	StWeapon.boughtWeapon3, StWeapon.boughtWeapon4 
	};
	int purchasedArmors[100] = { StArmors.boughtArmor1, StArmors.boughtArmor2,
		StArmors.boughtArmor3, StArmors.boughtArmor4
	};
	int boughtWeapon;
	int boughtArmor;
	int choicheBought;
	bool Return = true;
	while (Return) {
		printf("what item do you want to buy?\n1 - weapon\n2 - armor\n3 - exit\n");
		scanf_s("%d", &choicheBought);
		if (choicheBought == 3) Return = false;
		if (choicheBought == 1) {
			printf("select the weapon you want to buy\n");
			scanf_s("%d", &boughtWeapon);
			for (int i = 0; i < sizeof(purchasedWeapons) / sizeof(int); i++) {
				if (boughtWeapon - 1 == i and purchasedWeapons[boughtWeapon - 1] == false) {
					purchasedWeapons[boughtWeapon - 1] = true;
					//gold--;
					printf("you bought %d weapon id\n", i);
				}
				else if (purchasedWeapons[boughtWeapon - 1] == true and boughtWeapon - 1 == i)
					printf("this weapon has already been purchased\n");
			}
		}
		if (choicheBought == 2) {
			printf("select the armor you want to buy\n");
			scanf_s("%d", &boughtArmor);
			for (int i = 0; i < sizeof(purchasedArmors) / sizeof(int); i++) {
				if (boughtArmor - 1 == i and purchasedArmors[boughtArmor - 1] == false) {
					purchasedArmors[boughtArmor - 1] = true;
					//gold--;
					printf("you bought %d armor id\n", i);
				}
				else if (purchasedArmors[boughtArmor - 1] == true and boughtArmor - 1 == i)
					printf("this armor has already been purchased\n");
			}
		}
	}
}

//int main() {
//	Shop();
//}