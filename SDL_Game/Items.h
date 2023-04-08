#pragma once

struct weapons {
	//damage weapon			//gold cost			//whether the item was purchased
	int weapon1Damage = 10, costWeapon1 = 50;	bool boughtWeapon1 = false;
	int weapon2Damage = 15, costWeapon2 = 100;	bool boughtWeapon2 = false;
	int weapon3Damage = 20, costWeapon3 = 150;	bool boughtWeapon3 = false;
	int weapon4Damage = 25, costWeapon4 = 200;	bool boughtWeapon4 = false;
};
extern weapons StWeapon;

struct armors {
	//health weapon			//amount of armor  //goldcost		//whether the item was purchased
	int armor1Health = 30, amountArmor1 = 10, costArmor1 = 50;	 bool boughtArmor1 = false;
	int armor2Health = 60, amountArmor2 = 20, costArmor2 = 100;  bool boughtArmor2 = false;
	int armor3Health = 90, amountArmor3 = 30, costArmor3 = 150;	 bool boughtArmor3 = false;
	int armor4Health = 120, amountArmor4 = 40, costArmor4 = 200; bool boughtArmor4 = false;
};
extern armors StArmors;

struct inventoryForBattle {
	//health potion
	int healthPotion1 = 50, healthPotion2 = 100, healthPotion3 = 150, healthPotion4 = 200;
	//mana potion
	int manaPotion1 = 40, manaPotion2 = 80, manaPotion3 = 120, manaPotion4 = 160;
};
extern inventoryForBattle battleInventory;