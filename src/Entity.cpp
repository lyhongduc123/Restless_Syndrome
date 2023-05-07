#include "Entity.h"

Entity::Entity()
{
	existing = true;

	animation = false;
	nFrame = animate_speed = 0;

	x = y = w = h = 0;

	texture = nullptr;
	dst = { 0, 0, 80, 80 };
	src = { 0, 0, 32, 32 };
}

Entity::~Entity() {}


//Draw entity
void Entity::Draw() 
{
	if (animation) {
		src.x = src.w * ((int)((Game::time.getTime() / animate_speed) % nFrame));
	}
	if (existing) Texture::drawTexture(texture, src, dst);
}


//Update entity position
void Entity::Update()
{
	dst.x = x - Game::camera.x + Game::randVar.x;
	dst.y = y - Game::camera.y + Game::randVar.y;
}


void Entity::Delete()
{
	setX(-1.0f);
	setY(-1.0f);
	existing = false;
	std::cout << "DELETE SUCCESS" << std::endl;
}