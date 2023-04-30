#include "Models.h"
#include <iostream>

void upgradeWeapon(); void upgradeArmor(); void upgradeNecklace();
upgradeLVL itemUpgrade;

void upgradeItems() {
	int choiche = 0;
	while (choiche == 0) {
		printf("Какой предмет прокачиваем?\n1 - weapon\n2 - armor\n3 - necklace\n");
		scanf_s("%d", &choiche);
	}

	if (choiche == 1) upgradeWeapon();
	if (choiche == 2) upgradeArmor();
	if (choiche == 3) upgradeNecklace();
}

void upgradeWeapon() {
	int levelWeapon = 0; int upgrade = 0;
	printf("Вы хотите улучшить оружие?\n");
	scanf_s("%d", &upgrade);
	while (upgrade == 1) {
		if (levelWeapon == 0 and upgrade == 1) {
			upgrade = 0;
			printf("Стоимость улучшения %d\n", itemUpgrade.LVL1);
			printf("Вы хотите прокачать?\n"); scanf_s("%d", &upgrade);
			if (upgrade == 1 and hero.Gold == itemUpgrade.LVL1) {
				hero.weapon += 10;
				upgrade = 0;
				levelWeapon = 1;
			}
			if (upgrade == 1 and hero.Gold < itemUpgrade.LVL1) {
				printf("У вас не достаточно денег\n");
				upgrade = 0;
			}
			if (upgrade == 0) return;
		}
		if (levelWeapon == 1 and upgrade == 1) {
			upgrade = 0;
			printf("Стоимость улучшения %d\n", itemUpgrade.LVL2);
			printf("Вы хотите прокачать?\n"); scanf_s("%d", &upgrade);
			if (upgrade == 1 and hero.Gold == itemUpgrade.LVL2) {
				hero.weapon += 10;
				upgrade = 0;
				levelWeapon = 2;
			}
			if (upgrade == 1 and hero.Gold < itemUpgrade.LVL2) {
				printf("У вас не достаточно денег\n");
				upgrade = 0;
			}
			if (upgrade == 0) return;
		}
		if (levelWeapon == 2 and upgrade == 1) {
			upgrade = 0;
			printf("Стоимость улучшения %d\n", itemUpgrade.LVL3);
			printf("Вы хотите прокачать?\n"); scanf_s("%d", &upgrade);
			if (upgrade == 1 and hero.Gold == itemUpgrade.LVL3) {
				hero.weapon += 10;
				upgrade = 0;
				levelWeapon = 3;
			}
			if (upgrade == 1 and hero.Gold < itemUpgrade.LVL3) {
				printf("У вас не достаточно денег\n");
				upgrade = 0;
			}
			if (upgrade == 0) return;
		}
		if (levelWeapon == 3 and upgrade == 1) {
			upgrade = 0;
			printf("Стоимость улучшения %d\n", itemUpgrade.LVL4);
			printf("Вы хотите прокачать?\n"); scanf_s("%d", &upgrade);
			if (upgrade == 1 and hero.Gold == itemUpgrade.LVL4) {
				hero.weapon += 10;
				upgrade = 0;
				levelWeapon = 4;
			}
			if (upgrade == 1 and hero.Gold < itemUpgrade.LVL4) {
				printf("У вас не достаточно денег\n");
				upgrade = 0;
			}
			if (upgrade == 0) return;
		}
		if (levelWeapon == 4 and upgrade == 1) {
			upgrade = 0;
			printf("Стоимость улучшения %d\n", itemUpgrade.LVL5);
			printf("Вы хотите прокачать?\n"); scanf_s("%d", &upgrade);
			if (upgrade == 1 and hero.Gold == itemUpgrade.LVL5) {
				hero.weapon += 10;
				upgrade = 0;
				levelWeapon = 5;
			}
			if (upgrade == 1 and hero.Gold < itemUpgrade.LVL5) {
				printf("У вас не достаточно денег\n");
				upgrade = 0;
			}
			if (upgrade == 0) return;
		}
		if (levelWeapon == 5 and upgrade == 1) {
			printf("У вас максимальный уровень оружия\nВам больше нечего прокачивать\n");
			upgrade = 0;
		}
	}
	if (upgrade == 0) return;
}

void upgradeArmor() {
	int levelArmor = 0; int upgrade = 0;
	printf("Вы хотите улучшить броню?\n");
	scanf_s("%d", &upgrade);
	while (upgrade == 1) {
		if (levelArmor == 0 and upgrade == 1) {
			upgrade = 0;
			printf("Стоимость улучшения %d\n", itemUpgrade.LVL1);
			printf("Вы хотите прокачать?\n"); scanf_s("%d", &upgrade);
			if (upgrade == 1 and hero.Gold == itemUpgrade.LVL1) {
				hero.armorHealth += 30;
				hero.armorDefense += 5;
				upgrade = 0;
				levelArmor = 1;
			}
			if (upgrade == 1 and hero.Gold < itemUpgrade.LVL1) {
				printf("У вас не достаточно денег\n");
				upgrade = 0;
			}
			if (upgrade == 0) return;
		}
		if (levelArmor == 1 and upgrade == 1) {
			upgrade = 0;
			printf("Стоимость улучшения %d\n", itemUpgrade.LVL2);
			printf("Вы хотите прокачать?\n"); scanf_s("%d", &upgrade);
			if (upgrade == 1 and hero.Gold == itemUpgrade.LVL2) {
				hero.armorHealth += 30;
				hero.armorDefense += 5;
				upgrade = 0;
				levelArmor = 2;
			}
			if (upgrade == 1 and hero.Gold < itemUpgrade.LVL2) {
				printf("У вас не достаточно денег\n");
				upgrade = 0;
			}
			if (upgrade == 0) return;
		}
		if (levelArmor == 2 and upgrade == 1) {
			upgrade = 0;
			printf("Стоимость улучшения %d\n", itemUpgrade.LVL3);
			printf("Вы хотите прокачать?\n"); scanf_s("%d", &upgrade);
			if (upgrade == 1 and hero.Gold == itemUpgrade.LVL3) {
				hero.armorHealth += 30;
				hero.armorDefense += 5;
				upgrade = 0;
				levelArmor = 3;
			}
			if (upgrade == 1 and hero.Gold < itemUpgrade.LVL3) {
				printf("У вас не достаточно денег\n");
				upgrade = 0;
			}
			if (upgrade == 0) return;
		}
		if (levelArmor == 3 and upgrade == 1) {
			upgrade = 0;
			printf("Стоимость улучшения %d\n", itemUpgrade.LVL4);
			printf("Вы хотите прокачать?\n"); scanf_s("%d", &upgrade);
			if (upgrade == 1 and hero.Gold == itemUpgrade.LVL4) {
				hero.armorHealth += 30;
				hero.armorDefense += 5;
				upgrade = 0;
				levelArmor = 4;
			}
			if (upgrade == 1 and hero.Gold < itemUpgrade.LVL4) {
				printf("У вас не достаточно денег\n");
				upgrade = 0;
			}
			if (upgrade == 0) return;
		}
		if (levelArmor == 4 and upgrade == 1) {
			upgrade = 0;
			printf("Стоимость улучшения %d\n", itemUpgrade.LVL5);
			printf("Вы хотите прокачать?\n"); scanf_s("%d", &upgrade);
			if (upgrade == 1 and hero.Gold == itemUpgrade.LVL5) {
				hero.armorHealth += 30;
				hero.armorDefense += 5;
				upgrade = 0;
				levelArmor = 5;
			}
			if (upgrade == 1 and hero.Gold < itemUpgrade.LVL5) {
				printf("У вас не достаточно денег\n");
				upgrade = 0;
			}
			if (upgrade == 0) return;
		}
		if (levelArmor == 5 and upgrade == 1) {
			printf("У вас максимальный уровень брони\nВам больше нечего прокачивать\n");
			upgrade = 0;
		}
	}
	if (upgrade == 0) return;
}

void upgradeNecklace() {
	int levelNecklace = 0; int upgrade = 0;
	printf("Вы хотите улучшить броню?\n");
	scanf_s("%d", &upgrade);
	while (upgrade == 1) {
		if (levelNecklace == 0 and upgrade == 1) {
			upgrade = 0;
			printf("Стоимость улучшения %d\n", itemUpgrade.LVL1);
			printf("Вы хотите прокачать?\n"); scanf_s("%d", &upgrade);
			if (upgrade == 1 and hero.Gold == itemUpgrade.LVL1) {
				hero.necklace += 10;
				upgrade = 0;
				levelNecklace = 1;
			}
			if (upgrade == 1 and hero.Gold < itemUpgrade.LVL1) {
				printf("У вас не достаточно денег\n");
				upgrade = 0;
			}
			if (upgrade == 0) return;
		}
		if (levelNecklace == 1 and upgrade == 1) {
			upgrade = 0;
			printf("Стоимость улучшения %d\n", itemUpgrade.LVL2);
			printf("Вы хотите прокачать?\n"); scanf_s("%d", &upgrade);
			if (upgrade == 1 and hero.Gold == itemUpgrade.LVL2) {
				hero.necklace += 10;
				upgrade = 0;
				levelNecklace = 2;
			}
			if (upgrade == 1 and hero.Gold < itemUpgrade.LVL2) {
				printf("У вас не достаточно денег\n");
				upgrade = 0;
			}
			if (upgrade == 0) return;
		}
		if (levelNecklace == 2 and upgrade == 1) {
			upgrade = 0;
			printf("Стоимость улучшения %d\n", itemUpgrade.LVL3);
			printf("Вы хотите прокачать?\n"); scanf_s("%d", &upgrade);
			if (upgrade == 1 and hero.Gold == itemUpgrade.LVL3) {
				hero.necklace += 10;
				upgrade = 0;
				levelNecklace = 3;
			}
			if (upgrade == 1 and hero.Gold < itemUpgrade.LVL3) {
				printf("У вас не достаточно денег\n");
				upgrade = 0;
			}
			if (upgrade == 0) return;
		}
		if (levelNecklace == 3 and upgrade == 1) {
			upgrade = 0;
			printf("Стоимость улучшения %d\n", itemUpgrade.LVL4);
			printf("Вы хотите прокачать?\n"); scanf_s("%d", &upgrade);
			if (upgrade == 1 and hero.Gold == itemUpgrade.LVL4) {
				hero.necklace += 10;
				upgrade = 0;
				levelNecklace = 4;
			}
			if (upgrade == 1 and hero.Gold < itemUpgrade.LVL4) {
				printf("У вас не достаточно денег\n");
				upgrade = 0;
			}
			if (upgrade == 0) return;
		}
		if (levelNecklace == 4 and upgrade == 1) {
			upgrade = 0;
			printf("Стоимость улучшения %d\n", itemUpgrade.LVL5);
			printf("Вы хотите прокачать?\n"); scanf_s("%d", &upgrade);
			if (upgrade == 1 and hero.Gold == itemUpgrade.LVL5) {
				hero.necklace += 10;
				upgrade = 0;
				levelNecklace = 5;
			}
			if (upgrade == 1 and hero.Gold < itemUpgrade.LVL5) {
				printf("У вас не достаточно денег\n");
				upgrade = 0;
			}
			if (upgrade == 0) return;
		}
		if (levelNecklace == 5 and upgrade == 1) {
			printf("У вас максимальный уровень ожерелья\nВам больше нечего прокачивать\n");
			upgrade = 0;
		}
	}
	if (upgrade == 0) return;
}

int main() {
	system("chcp 1251");
	upgradeItems();
}