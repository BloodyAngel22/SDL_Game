#include <stdio.h>
#include <stdlib.h>
#include "Items.h"
#include "Models.h"

weapons StWeapon;
armors StArmors;
extern bool lockItems;
extern bool purchasedItem;
void Invenory() {
	int arrayWeapons[100] = { StWeapon.weapon1Damage, StWeapon.weapon2Damage, StWeapon.weapon3Damage, 
		StWeapon.weapon4Damage
	};
	int arrayArmors[100] = { StArmors.armor1Health, StArmors.armor2Health, StArmors.armor3Health, 
		StArmors.armor4Health 
	};
	int choiceItem;
	printf("1 - Weapons\n2 - Armors\n");
	scanf_s("%d", &choiceItem);
	if (choiceItem == 1) {
		int choiceWeapon;
		printf("Choose a weapon\n");
		scanf_s("%d", &choiceWeapon);

		#pragma region Weapon1
		if (StWeapon.costWeapon1 == choiceWeapon and lockItems == false and purchasedItem == true) {
			hero.Attack += StWeapon.weapon1Damage;
			lockItems = true;
		}
		else if (StWeapon.costWeapon1 == choiceWeapon and lockItems == true and purchasedItem == true) {
			printf("you removed the item\n");
			hero.Attack -= StWeapon.weapon1Damage;
		}
		else if (StWeapon.costWeapon1 == choiceWeapon and purchasedItem == false) {
			printf("This item has not been purchased\n");
		}
		#pragma endregion

		#pragma region Weapon2
		if (StWeapon.costWeapon2 == choiceWeapon and lockItems == false and purchasedItem == true) {
			hero.Attack += StWeapon.weapon2Damage;
			lockItems = true;
		}
		else if (StWeapon.costWeapon2 == choiceWeapon and lockItems == true and purchasedItem == true and useThisItem) {
			printf("you removed the item\n");
			hero.Attack -= StWeapon.weapon2Damage;
		}
		else if (StWeapon.costWeapon2 == choiceWeapon and purchasedItem == false) {
			printf("This item has not been purchased\n");
		}
		#pragma endregion

		#pragma region Weapon3
		if (StWeapon.costWeapon3 == choiceWeapon and lockItems == false and purchasedItem == true) {
			hero.Attack += StWeapon.weapon3Damage;
			lockItems = true;
		}
		else if (StWeapon.costWeapon3 == choiceWeapon and lockItems == true and purchasedItem == true) {
			printf("you removed the item\n");
			hero.Attack -= StWeapon.weapon3Damage;
		}
		else if (StWeapon.costWeapon3 == choiceWeapon and purchasedItem == false) {
			printf("This item has not been purchased\n");
		}
#pragma endregion

		#pragma region Weapon4
		if (StWeapon.costWeapon4 == choiceWeapon and lockItems == false and purchasedItem == true) {
			hero.Attack += StWeapon.weapon4Damage;
			lockItems = true;
		}
		else if (StWeapon.costWeapon4 == choiceWeapon and lockItems == true and purchasedItem == true) {
			printf("you removed the item\n");
			hero.Attack -= StWeapon.weapon4Damage;
		}
		else if (StWeapon.costWeapon4 == choiceWeapon and purchasedItem == false) {
			printf("This item has not been purchased\n");
		}
#pragma endregion
	}
	if (choiceItem == 2);
}

void Inventory_Battle() {

}