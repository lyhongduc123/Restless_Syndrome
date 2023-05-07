#include "LevelsAttribute.h"

LevelsAttribute::LevelsAttribute()
{
	currentLevel = 0;
	map = new Map();
	player = new Player();
}


LevelsAttribute::~LevelsAttribute()
{

}



void LevelsAttribute::loadLevel() 
{
	mapReset();
	//std::cout << currentLevel << std::endl;
	switch (currentLevel) 
	{
	case 0:
		break;
	case 1:
		Level1();
		break;
	case 2:
		Level2();
		break;
	case 3:
		Level3();
		break;
	case 4:
		Level4();
		break;
	case 5:
		Level5();
		break;
	case 6:
		Level6();
		break;
	case 7:
		Level7();
		break;
	case 8:
		Level8();
		break;
	case 9:
		Level9();
		break;
	case 10:
		Level10();
		break;
	case 11:
		Level11();
		break;
	case 12:
		Level12();
		break;
	default: break;
	}
}

void LevelsAttribute::increaseLevel() 
{
	if (currentLevel < 12) {
		currentLevel++;
	}
}

void LevelsAttribute::mapReset() 
{
	if (map != nullptr) {
		delete map;
		map = new Map();
		std::cout << "Map Reset Success!" << std::endl;
	}
	else std::cout << "-----MAP NULL----" << std::endl;
}


void LevelsAttribute::Level1() 
{
	player->resetStats();
	player->setPos(150, 600);
	player->setAlive();

	map->objective = Objective(447, 256);
	map->setPath(Level_1);
	map->loadMap();

	Game::tick = Game::const_tick = 4;
	Game::timePerTick = 520;
}

void LevelsAttribute::Level2() 
{
	player->resetStats();
	player->setPos(195, 245);
	player->setAlive();

	map->objective = Objective(1000, 640);
	map->setPath(Level_2);
	map->loadMap();

	Game::tick = Game::const_tick = 4;
	Game::timePerTick = 520;
}

void LevelsAttribute::Level3() 
{
	player->resetStats();
	player->setPos(200, 200);
	player->setAlive();

	map->objective = Objective(1540, 480);
	map->setPath(Level_3);
	map->loadMap();

	Game::tick = Game::const_tick = 4;
	Game::timePerTick = 520;
}
void LevelsAttribute::Level4() 
{
	player->resetStats();
	player->setPos(700, 500);
	player->setAlive();

	map->objective = Objective(1113, 174);
	map->setPath(Level_4);
	map->loadMap();

	Game::tick = Game::const_tick = 4;
	Game::timePerTick = 320;
}
void LevelsAttribute::Level5() 
{
	player->resetStats();
	player->setPos(200, 100);
	player->setAlive();

	map->objective = Objective(410, 765);
	map->setPath(Level_5);
	map->loadMap();

	Game::tick = Game::const_tick = 4;
	Game::timePerTick = 420;
}
void LevelsAttribute::Level6() 
{
	player->resetStats();
	player->setPos(270, 300);
	player->setAlive();

	map->objective = Objective(1400, 230);
	map->setPath(Level_6);
	map->loadMap();

	Game::tick = Game::const_tick = 4;
	Game::timePerTick = 155;
}

void LevelsAttribute::Level7() 
{
	player->resetStats();
	player->setPos(1000, 240);
	player->setAlive();

	map->objective = Objective(900, 500);
	map->setPath(Level_7);
	map->loadMap();

	Game::tick = Game::const_tick = 6;
	Game::timePerTick = 520;
}

void LevelsAttribute::Level8() 
{
	player->resetStats();
	player->setPos(160, 200);
	player->setAlive();

	Clock c1 = Clock(345, 210, -3);
	Clock c2 = Clock(1550, 550, 3);

	map->clocks.push_back(c1);
	map->clocks.push_back(c2);
	map->objective = Objective(1955, 435);
	map->setPath(Level_8);
	map->loadMap();

	Game::tick = Game::const_tick = 6;
	Game::timePerTick = 420;
}

void LevelsAttribute::Level9() 
{
	player->resetStats();
	player->setPos(280, 315);
	player->setAlive();

	Clock c1 = Clock(460, 245, -5);
	Clock c2 = Clock(690, 250, -2);
	Clock c3 = Clock(1345, 542, -3);

	map->clocks.push_back(c1);
	map->clocks.push_back(c2);
	map->clocks.push_back(c3);
	map->objective = Objective(1800, 800);
	map->setPath(Level_9);
	map->loadMap();

	Game::tick = Game::const_tick = 6;
	Game::timePerTick = 520;
}

void LevelsAttribute::Level10() 
{
	player->resetStats();
	player->setPos(690, 1050);
	player->setAlive();

	Clock c1 = Clock(840, 850, -3);
	Clock c2 = Clock(450, 490, -5);
	map->clocks.push_back(c1);
	map->clocks.push_back(c2);

	map->objective = Objective(1425, 397);
	map->setPath(Level_10);
	map->loadMap();

	Game::tick = Game::const_tick = 6;
	Game::timePerTick = 320;
}


void LevelsAttribute::Level11()
{
	player->resetStats();
	player->setPos(450, 590);
	player->setAlive();

	Clock c1 = Clock(738, 420, -5);
	map->clocks.push_back(c1);

	Key k1 = Key(1077, 336, 10, 10, 10, 10);
	map->keys.push_back(k1);

	map->objective = Objective(160, 540);
	map->setPath(Level_11);
	map->loadMap();

	Game::tick = Game::const_tick = 6;
	Game::timePerTick = 520;
}

void LevelsAttribute::Level12()
{
	player->resetStats();
	player->setPos(235, 167);
	player->setAlive();

	map->objective = Objective(-100, -100);
	map->setPath(Level_12);
	map->loadMap();

	Game::tick = Game::const_tick = -1;
	Game::timePerTick = 520;
}