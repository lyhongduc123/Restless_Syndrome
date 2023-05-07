#pragma once
#include "Game.h"
#include "Clock.h"
#include "Objective.h"
#include "Key.h"
#include <vector>


enum TileID
{
	sky = -1,
	grass_topleft = 193,
	grass_topright = 197,
	grass_botleft = 289,
	grass_botright = 293,
	grass_top = 194,
	grass_bot = 290,
	grass_right = 245,
	grass_left = 217,
	dirt = 243,

	spike_up = 0,
	spike_down = 1,
	spike_right = 2,
	spike_left = 3,
	blueBlock = 209,
	greenBlock = 210,
	keyBlock = 235
};


enum TileType 
{
	COLLIDE = 1000,
	NON_COLLIDE = 1001,
	SPIKE = 1002
};



class Map
{
public:
	Map();
	~Map();
	
	void loadMap();
	void drawMap();
	void moveMap(int x, int y);
	void keyModify(Key k);

	/*--------------Set and get-------------*/
	void setPath(const char* path) { this->path = path; };
	void setMapStatus(bool completed) { this->completed = completed; };
	void setBread(Objective des) { this->objective = des; };
	void setClock(const std::vector<Clock> &clocks_vec) { this->clocks = clocks_vec; };
	void setMapTick(bool tick) { this->loadTick = tick; };

	int getTileType(int x, int y);
	int getTileID(int x, int y);
	int getMapX() { return dst.x; };
	int getMapY() { return dst.y; };
	int getMapLength() { return map_length; };
	int getMapHeight() { return map_height; };
	
	//SDL_Rect getSpawnPoint() { return spawnPoint; };
	//std::vector<Clock> getClock() { return clocks; };
	Objective getGoal() { return objective; };

	bool getMapStatus() { return completed; };
	bool getMapTick() { return loadTick; };

	/*--------------Delete and spawn--------------*/

	void deleteClock(int idx) {
		clocks[idx].Delete();
		clocks.erase(clocks.begin() + idx);
	}
	void deleteBread() {
		objective.Delete();
	}

	std::vector<Clock> clocks;
	std::vector<Key> keys;
	Objective objective;

private:
	const char* path;

	SDL_Rect src, dst;
	SDL_Rect map_shake;
	//SDL_Rect spawnPoint;
	
	std::vector<std::vector<int>> map_arr;
	int map_length, map_height;
	bool loadTick;

	bool completed;
};