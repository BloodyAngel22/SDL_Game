#pragma once

void upgradeItems(SDL_Renderer* ren); void upgradeWeapon(SDL_Renderer* ren); 
void upgradeArmor(SDL_Renderer* ren); void upgradeNecklace(SDL_Renderer* ren);

struct upgradeLVL {
	int LVL1 = 100, LVL2 = 200, LVL3 = 300, LVL4 = 400, LVL5 = 500;
};
extern upgradeLVL itemUpgrade;