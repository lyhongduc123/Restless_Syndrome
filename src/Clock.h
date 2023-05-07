#pragma once
#include "Entity.h"

#define CLOCK_HEIGHT 64
#define CLOCK_WIDTH 64


class Clock : public Entity
{
public:
	Clock(float x, float y, int typeClock) {
		type = typeClock;
		setX(x);
		setW(CLOCK_WIDTH);
		setY(y);
		setH(CLOCK_HEIGHT);
		
		setTexture(Game::clock);
		SDL_Rect src = { 0, 0, 32, 32 };

		switch (type) {
		case -2:
			src.x = src.y = 0;
			break;
		case -3:
			src.x = 32;
			break;
		case -5:
			src.x = 64;
			break;
		case 2:
			src.y = 32;
			break;
		case 3:
			src.x = 32;
			src.y = 32;
			break;
		case 5:
			src.x = 64;
			src.y = 32;
			break;
		default: std::cout << "NONE TYPE WERE DETECTED" << std::endl;
		}

		setSrc(src);
	};
	~Clock() {};

	int getType() { return type; };
private:
	int type;
};