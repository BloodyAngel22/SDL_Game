#pragma once

struct warrior {
	/*ITEMS*/ int weapon /*damage*/ = 10; int armorHealth = 20, armorDefense = 5; int necklace /*mana*/ = 20;

	int Health = 500 + armorHealth, Attack = 20 + weapon, Defense = 5 + armorDefense, Mana = 100 + necklace, 
		Gold = 1000, level = 1,
		maxLevel = 100, levelUp = 100, experience = 0, pointsLevel = 0, pointsTree = 0,
		maxAttack = Attack, maxHealth = Health, maxMana = Mana;
	float AtSpeed = 1.0;
	int coordinationCharacterX, coordinationCharacterY;
};
extern warrior hero;

struct Enemy {
	int Health = 100, Attack = 20, Gold = 50, level = 1, experienceEnemy = 150,
		maxHealth = 100;
	float AtSpeed = 0.5;
	int coordinationEnemyX, coordinationEnemyY;
};
extern Enemy opponent;

struct upgradeLVL {
	int LVL1 = 100, LVL2 = 200, LVL3 = 300, LVL4 = 400, LVL5 = 500;
};
extern upgradeLVL itemUpgrade;

struct genEnemy {
	int atk, health, gold, level;
	bool isPoison;
};
extern genEnemy enemy1, enemy2, enemy3, enemy4;