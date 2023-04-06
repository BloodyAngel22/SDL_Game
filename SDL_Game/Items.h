#pragma once

struct weapons {
	//damage weapon			//gold cost
	int weapon1Damage = 10, costWeapon1 = 50;
	int weapon2Damage = 15, costWeapon2 = 100;
	int weapon3Damage = 20, costWeapon3 = 150;
	int weapon4Damage = 25, costWeapon4 = 200;
};
extern weapons StWeapon;

struct armors {
	//health weapon			//amount of armor		//goldcost
	int armor1Health = 30, amountArmor1 = 10, costArmor1 = 50;
	int armor2Health = 60, amountArmor2 = 20, costArmor2 = 100;
	int armor3Health = 90, amountArmor3 = 30, costArmor3 = 150;
	int armor4Health = 120, amountArmor4 = 40, costArmor4 = 200;
};
extern armors StArmors;