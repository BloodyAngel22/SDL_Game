#pragma once

struct Character {
	int Health = 500, Attack = 20, Defense = 5, Mana = 100, Gold = 0, level = 1, maxLevel = 100, levelUp = 100, experience = 0, pointsLevel = 0;
	float AtSpeed = 1.0;
	int coordinationCharacterX, coordinationCharacterY;
};

struct Enemy {
	int Health = 100, Attack = 20, Gold = 50, level = 1, experienceEnemy = 150;
	float AtSpeed = 0.5;
	int coordinationEnemyX, coordinationEnemyY;
};

extern Character hero;
extern Enemy opponent;
