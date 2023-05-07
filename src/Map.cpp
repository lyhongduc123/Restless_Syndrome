#include "Map.h"
#include "Texture.h"
#include <iostream>
#include <fstream>

Map::Map()
{
	dst = { 0, 0, TILE_SIZE, TILE_SIZE };
	src = { 0, 0, TILE_SIZE, TILE_SIZE };

	map_height = 0;
	map_length = 0;
	loadTick = false;

	completed = false;
}

Map::~Map()
{
}


//Load map from file to a vector2D
void Map::loadMap()
{
	int tile;

	std::ifstream mapFile;
	mapFile.open(path);
	if (!mapFile.is_open()) {
		std::cout << "Can't open map files." << std::endl;
	}

	mapFile >> map_height >> map_length;
	mapFile.ignore();

	for (int y = 0; y < map_height; y++) {
		std::vector<int> vec;
		for (int x = 0; x < map_length; x++) {
			mapFile >> tile;
			
			vec.push_back(tile);
			mapFile.ignore();
		}
		map_arr.push_back(vec);
	} 

	mapFile.close();
}


//Draw map to render from vector
void Map::drawMap()
{	
	SDL_Rect background_dst = { 0 - Game::camera.x * 0.5, -10, SCREEN_WIDTH * 1.5, SCREEN_HEIGHT + 10};
	SDL_RenderCopy(Game::renderer, Game::background, NULL, &background_dst);

	int tile;
	for (int rows = 0; rows < map_arr.size(); rows++) {
		for (int cols = 0; cols < map_arr[rows].size(); cols++) {
			tile = map_arr[rows][cols];
		
			moveMap(cols, rows);
			//std::cout << dst.x << " " << dst.y << std::endl;
			switch (tile) {
			case TileID::grass_topleft:
				src.x = 8;
				src.y = 64;
				src.w = src.h = 8;
				Texture::drawTexture(Game::grass, src, dst);
				break;
			case TileID::grass_topright:
				src.x = 40;
				src.y = 64;
				src.w = src.h = 8;
				Texture::drawTexture(Game::grass, src, dst);
				break;
			case TileID::grass_botleft:
				src.x = 8;
				src.y = 96;
				src.w = src.h = 8;
				Texture::drawTexture(Game::grass, src, dst);
				break;
			case TileID::grass_botright:
				src.x = 40;
				src.y = 96;
				src.w = src.h = 8;
				Texture::drawTexture(Game::grass, src, dst);
				break;
			case TileID::grass_top:
				src.x = 16;
				src.y = 64;
				src.w = src.h = 8;
				Texture::drawTexture(Game::grass, src, dst);
				break;
			case TileID::grass_bot:
				src.x = 16;
				src.y = 96;
				src.w = src.h = 8;
				Texture::drawTexture(Game::grass, src, dst);
				break;
			case TileID::grass_right:
				src.x = 40;
				src.y = 72;
				src.w = src.h = 8;
				Texture::drawTexture(Game::grass, src, dst);
				break;
			case TileID::grass_left:
				src.x = 8;
				src.y = 72;
				src.w = src.h = 8;
				Texture::drawTexture(Game::grass, src, dst);
				break;
			case TileID::dirt:
				src.x = 16;
				src.y = 80;
				src.w = src.h = 8;
				Texture::drawTexture(Game::dirt, src, dst);
				break;
			case TileID::spike_up:
				src.x = 0;
				src.y = 0;
				src.w = 16;
				src.h = 16;
				Texture::drawTexture(Game::spike, src, dst);
				break;
			case TileID::spike_down:
				src.x = 0;
				src.y = 0;
				src.w = 16;
				src.h = 16;
				Texture::drawTextureExtra(Game::spike, src, dst, 180, NULL, SDL_FLIP_NONE);
				break;
			case TileID::spike_left:
				src.x = 0;
				src.y = 0;
				src.w = 16;
				src.h = 16;
				Texture::drawTextureExtra(Game::spike, src, dst, 270, NULL, SDL_FLIP_NONE);
				break;
			case TileID::spike_right:
				src.x = 0;
				src.y = 0;
				src.w = 16;
				src.h = 16;
				Texture::drawTextureExtra(Game::spike, src, dst, 90, NULL, SDL_FLIP_NONE);
				break;
			case TileID::blueBlock:
				if (loadTick) {
					src.x = 32;
					src.y = 0;
				}
				else {
					src.x = 0;
					src.y = 0;
				}
				src.w = src.h = 32;
				Texture::drawTexture(Game::blue_box, src, dst);
				break;
			case TileID::greenBlock:
				if (!loadTick) {
					src.x = 32;
					src.y = 0;
				}
				else {
					src.x = 0;
					src.y = 0;
				}
				src.w = src.h = 32;
				Texture::drawTexture(Game::green_box, src, dst);
				break;
			case TileID::keyBlock:
				src.x = src.y = 0;
				src.w = src.h = 32;
				Texture::drawTexture(Game::key_box, src, dst);
			default: break;
			}
		}
	}

	//Because we only want to update the render destination as the camera change, calling the entity update here
	for (int i = 0; i < (int)clocks.size(); i++) {
		clocks[i].Update();
		clocks[i].Draw();
	}
	for (int i = 0; i < (int)keys.size(); i++) {
		keys[i].Update();
		keys[i].Draw();
	}
	objective.Update();
	objective.Draw();
}

//Set map render position
void Map::moveMap(int x, int y)
{
	dst.x = (x * TILE_SIZE) - Game::camera.x + Game::randVar.x;
	dst.y = (y * TILE_SIZE) - Game::camera.y + Game::randVar.y;
}

//Return the map's tile type
int Map::getTileType(int x, int y)
{
	if (x >= map_length || y >= map_height || x < 0 || y < 0) return TileID::sky;
	switch (map_arr[y][x]) {
	case TileID::sky:
		return NON_COLLIDE;
	case TileID::greenBlock:
		if (loadTick) return COLLIDE;
		else return NON_COLLIDE;
	case TileID::blueBlock:
		if (!loadTick) return COLLIDE;
		else return NON_COLLIDE;
	case TileID::spike_up: 
	case TileID::spike_down: 
	case TileID::spike_right: 
	case TileID::spike_left:
		return SPIKE;
	default: 
		break;
	}
	return COLLIDE;
}

//Return map's block id
int Map::getTileID(int x, int y)
{
	if (x >= map_length || y >= map_height || x < 0 || y < 0) return TileID::sky;
	return map_arr[y][x];
}

void Map::keyModify(Key key)
{
	for (int i = 0; i < key.getCordinate().h; i++) {
		for (int j = 0; j < key.getCordinate().w; j++) {
			int y = key.getCordinate().y + i;
			int x = key.getCordinate().x + j;
			if (x >= 0 && y >= 0 && x < map_length && y < map_height)
			{
				if(map_arr[y][x] == keyBlock) map_arr[y][x] = sky;
			}
		}
	}
}