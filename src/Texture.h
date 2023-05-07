#pragma once

#include "Game.h"

class Texture
{
public:
	static SDL_Texture* loadTexture(const char* path);
	static SDL_Texture* loadFullTexture(const char* path);
	static SDL_Texture* loadTextureText(TTF_Font* font, std::string text, SDL_Color color);
	static void drawText(SDL_Texture* tex, SDL_Rect dst);
	static void drawTexture(SDL_Texture* tex, SDL_Rect srcRect, SDL_Rect dstRect);
	static void drawTextureExtra(SDL_Texture* tex, SDL_Rect srcRect, SDL_Rect dstRect, 
								 const double angle, 
								 SDL_Point* center, 
								 SDL_RendererFlip flipType);


};