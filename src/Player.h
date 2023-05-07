#pragma once
#include "Entity.h"
#include "Map.h"
#include <vector>

#define GRAVITY 0.7f
#define STAMINA_MAX 100
#define Vy_max 9.8f
#define Vx_max 5.0f


enum Direction
{
	LEFT = 1, RIGHT = 2
};



class Player
{
public:
	Player();
	~Player();

	void Draw();
	void LoadImg(const char* p_path);
	void Input(SDL_Event event);
	void Jump();
	void Glide();
	void Update(Map* level);
	void CheckCollision(Map* level);
	void CheckEntity(Map* level);

	//----------------------Set and get------------------------
	void setAlive() { this->alive = true; };
	void setKill() { this->kill = true; };
	void setPos(float x, float y) 
	{
		this->x = x;
		this->y = y;
	};
	void resetStats()
	{
		this->direction = RIGHT;
		this->jumped = false;
		this->gliding = false;
		this->x_vel = 0;
		this->y_vel = 0;
	};

	int getX() { return x; };
	int getY() { return y; };
	SDL_Rect getHitbox() { return { (int)x, (int)y, PLAYER_WIDTH, PLAYER_HEIGHT }; };
	SDL_Rect getDst() { return p_dst; };
	bool isAlive() { return alive; };
	bool hasJumped() { return jumped; };
	bool isGliding() { return gliding; };
	int getStamina() { return stamina; };
private:
	float x, y;
	float x_vel, y_vel;

	int direction;
	bool OnGround;
	bool alive;
	bool gliding;
	bool jumped;
	bool kill;

	int stamina;

	Sound* pickupClock;
	Sound* pickupKey;
	Sound* jump_sfx;
	Sound* die_sfx;

	SDL_Texture* p_texture;
	SDL_Rect p_src;
	SDL_Rect p_dst;
	SDL_Rect hitbox;
};

