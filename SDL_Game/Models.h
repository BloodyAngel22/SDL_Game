#pragma once

struct Character {
	/*ITEMS*/ int weapon /*damage*/ = 10; int armorHealth = 20, armorDefense = 0.05; int necklace /*mana*/ = 20;

	int Health, Attack, Mana, 
		Gold, level = 1,
		maxLevel = 100, levelUp = 100, experience = 0, pointsLevel = 0, pointsTree = 0,
		maxAttack = Attack, maxHealth = Health, maxMana = Mana;
	float AtSpeed = 1.0;
	float Defense;
	int coordinationCharacterX, coordinationCharacterY;
};
extern Character hero;

struct ClassWarrior {
	/*ITEMS*/ int weapon /*damage*/ = 10; int armorHealth = 20; float armorDefense = 0.05; int necklace /*mana*/ = 20;
	int Health = 500 + armorHealth, Attack = 20 + weapon, Mana = 100 + necklace,
		Gold = 500, level = 1,
		maxLevel = 100, levelUp = 100, experience = 0, pointsLevel = 0, pointsTree = 0,
		maxAttack = Attack, maxHealth = Health, maxMana = Mana;
	float AtSpeed = 1.0;
	float Defense = 0.05 + armorDefense;
	int coordinationCharacterX, coordinationCharacterY;
};
extern ClassWarrior warrior;

struct ClassMage {
	/*ITEMS*/ int weapon /*damage*/ = 10; int armorHealth = 20; float armorDefense = 0.05; int necklace /*mana*/ = 20;
	int Health = 250 + armorHealth, Attack = 50 + weapon, Mana = 200 + necklace,
		Gold = 800, level = 1,
		maxLevel = 100, levelUp = 100, experience = 0, pointsLevel = 20, pointsTree = 0,
		maxAttack = Attack, maxHealth = Health, maxMana = Mana;
	float AtSpeed = 1.0;
	float Defense = 0.05 + armorDefense;
	int coordinationCharacterX, coordinationCharacterY;
};
extern ClassMage mage;

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
	int maxHealth;
	bool isPoison;
};
extern genEnemy enemy1, enemy2, enemy3, enemy4;