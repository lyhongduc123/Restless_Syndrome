#pragma once

#include "Entity.h"

#define BREAD_WIDTH 64
#define BREAD_HEIGHT 64

class Objective : public Entity
{
public:
	Objective(float x = 0, float y = 0) 
	{
		setX(x);
		setY(y);
		setW(BREAD_WIDTH);
		setH(BREAD_HEIGHT);

		SDL_Rect src = { 0, 0, 32, 32 };
		setTexture(Game::toaster);
		setSrc(src);
		setAnimate(true, 7, 100);
	};
	~Objective() {};
};