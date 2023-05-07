#include "Texture.h"


//Load texture image and return a texture
SDL_Texture* Texture::loadTexture(const char* path)
{
	SDL_Surface* tmp_Surface = IMG_Load(path);
	SDL_Texture* Tex = nullptr;

	//Remove texture background
	if (tmp_Surface != NULL) 
	{
		SDL_SetColorKey(tmp_Surface, SDL_TRUE, SDL_MapRGB(tmp_Surface->format, 255, 255, 255));
		Tex = SDL_CreateTextureFromSurface(Game::renderer, tmp_Surface);
		std::cout << "Texture path: " << path << " loaded." << std::endl;
	}

	SDL_FreeSurface(tmp_Surface);
	if (Tex == NULL) std::cout << "Texture null: " << path << std::endl;
	return Tex;
}

SDL_Texture* Texture::loadFullTexture(const char* path) 
{
	SDL_Surface* tmp_Surface = IMG_Load(path);
	SDL_Texture* Tex = nullptr;

	if (tmp_Surface != NULL) 
	{
		Tex = SDL_CreateTextureFromSurface(Game::renderer, tmp_Surface);
		std::cout << "Texture path: " << path << " loaded." << std::endl;
	}

	SDL_FreeSurface(tmp_Surface);
	if (Tex == NULL) std::cout << "Texture null: " << path << std::endl;
	return Tex;
}

void Texture::drawText(SDL_Texture* tex, SDL_Rect dst) 
{
	SDL_RenderCopy(Game::renderer, tex, NULL, &dst);
}


void Texture::drawTexture(SDL_Texture* tex, SDL_Rect srcRect, SDL_Rect dstRect) 
{
	SDL_RenderCopy(Game::renderer, tex, &srcRect, &dstRect);
}


//Draw texture to the renderer with degree
void Texture::drawTextureExtra(SDL_Texture* tex, SDL_Rect srcRect, SDL_Rect dstRect, const double angle, SDL_Point* center, SDL_RendererFlip flipType) 
{
	SDL_RenderCopyEx(Game::renderer, tex, &srcRect, &dstRect, angle, center, flipType);
}


SDL_Texture* Texture::loadTextureText(TTF_Font* font, std::string text, SDL_Color color) 
{
	SDL_Surface* tmp_Surface = TTF_RenderText_Solid(font, text.c_str(), color);
	SDL_Texture* Tex = nullptr;

	if (tmp_Surface != NULL) 
	{
		Tex = SDL_CreateTextureFromSurface(Game::renderer, tmp_Surface);
	}

	SDL_FreeSurface(tmp_Surface);
	if (Tex == NULL) std::cout << "Texture font null" << std::endl;
	return Tex;
}