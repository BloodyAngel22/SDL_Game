#include <stdio.h>
#include <stdlib.h>
#include "Items.h"
#include "Models.h"

weapons StWeapon;
armors StArmors;
bool lockItemsWeapon = false;
bool lockItemsArmor = false;
bool purchasedItem = true;
int selectAnItem;
int choiceItem;
int removeItem;
int choiceWeapon;

void Invenory() {
	int arrayWeapons[100] = { StWeapon.weapon1Damage, StWeapon.weapon2Damage, StWeapon.weapon3Damage, 
		StWeapon.weapon4Damage
	};
	int idPastWeapon;
	int idPastArmor;
	int arrayArmors[100] = { StArmors.armor1Health, StArmors.armor2Health, StArmors.armor3Health, 
		StArmors.armor4Health 
	};
	bool Return_2 = true;
	printf("do you want to select an item?\n0 - no\n1 - yes\n");
	scanf_s("%d", &selectAnItem);
	if (selectAnItem == 0) Return_2 = false;
	while (Return_2) {
		printf("1 - Weapons\n2 - Armors\n3 - exit\n");
		scanf_s("%d", &choiceItem);
		if (choiceItem == 1) {
			bool Return = true;
			while (Return) {
				if (lockItemsWeapon == true) {
					printf("Do you want to remove an item?\n0 - no\n1 - yes\n");
					scanf_s("%d", &removeItem);
					if (removeItem == 0) {
						Return = false;
					}
				}
				if (lockItemsWeapon == false) {
					printf("Choose a weapon\n");
					scanf_s("%d", &choiceWeapon);
				}
				for (int i = 0; i < sizeof(arrayWeapons) / sizeof(int); i++) { //Кол-во элементов массива
#pragma region Weapon
					if (i == choiceWeapon - 1 and lockItemsWeapon == false and purchasedItem == true) {
						hero.Attack += arrayWeapons[i];
						lockItemsWeapon = true;
						idPastWeapon = i;
						printf("Your damage %d\n", hero.Attack);
					}
					else if (i == choiceWeapon - 1 and lockItemsWeapon == true and purchasedItem == true and removeItem == 1) {
						printf("you removed the item\n");
						hero.Attack -= arrayWeapons[idPastWeapon];
						printf("Your damage %d\n", hero.Attack);
						lockItemsWeapon = false;
					}
					else if (i == choiceWeapon - 1 and purchasedItem == false) {
						printf("This item has not been purchased\n");
					}
				}
			}
#pragma endregion

		}
		if (choiceItem == 2) {
			int choiceArmor;
			bool Return = true;
			while (Return) {
				if (lockItemsArmor == true) {
					printf("Do you want to remove an item?\n0 - no\n1 - yes\n");
					scanf_s("%d", &removeItem);
					if (removeItem == 0) {
						Return = false;
					}
				}
				if (lockItemsArmor == false) {
					printf("Choose a armor\n");
					scanf_s("%d", &choiceArmor);
				}
				for (int i = 0; i < sizeof(arrayArmors) / sizeof(int); i++) { //Кол-во элементов массива
#pragma region Armor
					if (i == choiceArmor - 1 and lockItemsArmor == false and purchasedItem == true) {
						hero.Health += arrayArmors[i];
						lockItemsArmor = true;
						idPastArmor = i;
						printf("Your health %d\n", hero.Health);
					}
					else if (i == choiceArmor - 1 and lockItemsArmor == true and purchasedItem == true and removeItem == 1) {
						printf("you removed the item\n");
						hero.Health -= arrayArmors[idPastArmor];
						printf("Your health %d\n", hero.Health);
						lockItemsArmor = false;
					}
					else if (i == choiceArmor - 1 and purchasedItem == false) {
						printf("This item has not been purchased\n");
					}
				}
			}
#pragma endregion
		}
		if (choiceItem == 3) Return_2 = false;
	}
}

void Inventory_Battle() {

}

int main() {
	Invenory();
}