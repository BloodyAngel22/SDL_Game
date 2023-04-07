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
	while (true) {
		printf("select the weapon you want to buy\n");
		scanf_s("%d", &boughtWeapon);
		for (int i = 0; i < sizeof(purchasedWeapons) / sizeof(int); i++) {
			if (boughtWeapon - 1 == i and purchasedWeapons[boughtWeapon - 1] == false) {
				purchasedWeapons[boughtWeapon - 1] = true;
				//gold--;
				printf("you bought %d weapon id\n", i);
			}
			else if (purchasedWeapons[boughtWeapon - 1] == true and boughtWeapon - 1 == i)
				printf("this item has already been purchased\n");
		}
	}
}

int main() {
	Shop();
}