#pragma once

#include "Game.h"
#include "Texture.h"

class Animation
{
public:
	Animation(const char* path);
	Animation(const char* path, int nFrame, int nFrameSpeed, int nFrameSize);
	~Animation() {};

	void Animate();

private:
	const char* path;

	SDL_Texture* texture;
	SDL_Rect src;
	int nFrame;
	int nFrameSpeed;
	int nFrameSize;
};