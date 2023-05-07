#pragma once

#include "SDL.h"
#include "SDL_image.h"
#include "Texture.h"
#include "Game.h"


class Entity
{
public:

	Entity();
	~Entity();

	void Draw();
	virtual void Update();
	virtual void Delete();

	void setTexture(SDL_Texture* tex) { this->texture = tex; };
	void setSrc(SDL_Rect src) { this->src = src; };
	//void setExistence(bool bool_) { this->existing = bool_; };
	void setX(float _x) { x = _x; };
	void setY(float _y) { y = _y; };
	void setW(float _w) { w = _w; };
	void setH(float _h) { h = _h; };
	void setAnimate(bool animation, int nFrame, int speed) {
		this->animation = animation;
		this->nFrame = nFrame;
		this->animate_speed = speed;
	};

	SDL_Rect getDst() { return dst; };
	float getX() { return x; };
	float getY() { return y; };
	float getW() { return w; };
	float getH() { return h; };
private:
	float x, y;
	float w, h;
	bool existing;

	bool animation;
	int nFrame, animate_speed;

	SDL_Texture* texture;
	SDL_Rect src; 
	SDL_Rect dst;
};


