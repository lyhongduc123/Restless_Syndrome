#pragma once

#include "Entity.h"

#define KEY_WIDTH 64
#define KEY_HEIGHT 64

class Key : public Entity
{
public:
	Key(float x, float y, int startBlockX = 0, int startBlockY = 0, int numRows = 0, int numCols = 0) {
		setX(x);
		setY(y);
		setW(KEY_WIDTH);
		setH(KEY_HEIGHT);

		this->cordinate.x = startBlockX;
		this->cordinate.y = startBlockY;
		this->cordinate.w = numCols;
		this->cordinate.h = numRows;

		SDL_Rect src = { 0 ,0 ,32 ,32 };
		setSrc(src);
		setTexture(Game::key);
		setAnimate(true, 7, 100);
	}
	~Key() {};
	
	SDL_Rect getCordinate() { return cordinate; };

private:
	SDL_Rect cordinate;
};