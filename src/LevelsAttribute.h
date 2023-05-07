#pragma once

#include "Game.h"
#include "GameConfig.h"
#include "Map.h"
#include "Player.h"

class LevelsAttribute
{
public:
	LevelsAttribute();
	~LevelsAttribute();

	void update();
	void loadLevel();
	void mapReset();
	void increaseLevel();

	void Level1();
	void Level2();
	void Level3();
	void Level4();
	void Level5();
	void Level6();
	void Level7();
	void Level8();
	void Level9();
	void Level10();
	void Level11();
	void Level12();

	int getLevel() { return currentLevel; };

	Map* map;
	Player* player;

private:
	int currentLevel;
};
