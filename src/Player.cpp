#include "Player.h"

Player::Player()
{
	this->x = this->y = 0;
	this->p_dst = { SCREEN_WIDTH / 2, SCREEN_HEIGHT / 2, 64, 64 };
	this->hitbox = { 0, 0, PLAYER_WIDTH, PLAYER_HEIGHT };

	this->stamina = STAMINA_MAX;
	this->gliding = false;

	alive = true;
	kill = false;

	pickupClock = new Sound("assets/Sound/pickupClock.wav");
	pickupKey = new Sound("assets/Sound/pickupKey.wav");
	jump_sfx = new Sound("assets/Sound/flap.mp3");
	die_sfx = new Sound("assets/Sound/death_sfx.mp3");

	LoadImg(Player_PATH);
}

Player::~Player() 
{
	SDL_DestroyTexture(p_texture);
	delete pickupClock;
	delete pickupKey;
	delete jump_sfx;
	delete die_sfx;
}


void Player::LoadImg(const char* p_path)
{
	p_texture = Texture::loadTexture(p_path);
	if (p_texture == NULL) {
		std::cout << "Player NULL" << std::endl;
	}
}


void Player::Draw()
{ 
	int rows_index = 0;
	int skip_frame = 0;
	int frame = 1;
	int animationSpeed = 1;
	SDL_RendererFlip flip_type = SDL_FLIP_NONE;

	if (direction == LEFT) flip_type = SDL_FLIP_HORIZONTAL;

	if (x_vel == 0) {
		frame = 2;
		animationSpeed = 500;
	}
	else {
		skip_frame = 2;
		frame = 4;
		animationSpeed = 100;
	}

	if (y_vel < 0) {
		rows_index = frame = 1;
		skip_frame = 0;
	}
	else if (gliding && !OnGround) {
		rows_index = skip_frame = 1;
		frame = 2;
	}
	else if (!OnGround) {
		rows_index = skip_frame = frame = 1;
	}

	if (!alive) {
		skip_frame = 3;
		rows_index = 1;
	}

	p_src.x = Player_path_width_perframe * (skip_frame + ((int)((Game::time.getTime() / animationSpeed) % frame)) );
	p_src.y = rows_index * Player_path_height_perframe;
	p_src.w = Player_path_width_perframe;
	p_src.h = Player_path_height_perframe;

	Texture::drawTextureExtra(p_texture, p_src, p_dst, 0, NULL, flip_type);
}


//Get player input live time, no delay
void Player::Input(SDL_Event event)
{
	const Uint8* keystates = SDL_GetKeyboardState(NULL);

	if (keystates[SDL_SCANCODE_LEFT]) 
	{
		x_vel = -6.0f;
		direction = LEFT;
	}
	if (keystates[SDL_SCANCODE_RIGHT]) 
	{
		x_vel = 6.0f;
		direction = RIGHT;
	}

	if (keystates[SDL_SCANCODE_UP]) {
		if (!OnGround) 
		{
			gliding = true;
		}
		if (Game::tick == -1)
		{
			Jump();
		}
	}
	else gliding = false;
}

void Player::Jump()
{
	jump_sfx->PlaySound(2, 0);
	y_vel = -(Vy_max * 1.6f);
	jumped = true;
}

void Player::Glide()
{
	if (stamina != 0 && y_vel >= 0) {
		y_vel -= y_vel * 0.25f;
	}
	if(stamina > 0) stamina--;
}


//Update player position, status
void Player::Update(Map* level) {
	y_vel += GRAVITY;
	if (y_vel > Vy_max) y_vel = Vy_max;
	
	if (OnGround) stamina = STAMINA_MAX;

	CheckCollision(level);
	CheckEntity(level);

	if (x_vel > 0) x_vel -= 3.0f;
	if (x_vel < 0) x_vel += 3.0f;

	if (x >= level->getMapLength() * TILE_SIZE + 50 || x <= -100) alive = false;
	if (y >= level->getMapHeight() * TILE_SIZE + 50 || y <= -100) alive = false;
	if (kill)
	{
		kill = false;
		alive = false;
	}
	
	if (!alive) die_sfx->PlaySound(3, 0);

	p_dst.x = x - PLAYER_WIDTH/2 - Game::camera.x;
	p_dst.y = y - PLAYER_HEIGHT/2 - Game::camera.y;
}


void Player::CheckCollision(Map* level)
{
	//Check if player is inside collision tiles
	if ((level->getTileType((x + 1) / TILE_SIZE, (y + 1) / TILE_SIZE) == COLLIDE) ||
		(level->getTileType((x + PLAYER_WIDTH - 1) / TILE_SIZE, (y + 1) / TILE_SIZE)) == COLLIDE ||
		(level->getTileType((x + 1) / TILE_SIZE, (y + PLAYER_HEIGHT - 1) / TILE_SIZE)) == COLLIDE ||
		(level->getTileType((x + PLAYER_WIDTH - 1) / TILE_SIZE, (y + PLAYER_HEIGHT - 1) / TILE_SIZE)) == COLLIDE) 
	{
		alive = false;
	}

	//Check collision with normal map tiles
	double new_x = (x + x_vel) / TILE_SIZE;
	double new_y = (y + y_vel) / TILE_SIZE;
	double new_x2 = (x + x_vel + PLAYER_WIDTH) / TILE_SIZE;
	double new_y2 = (y + y_vel + PLAYER_HEIGHT) / TILE_SIZE;

	double old_y = y / TILE_SIZE;
	double old_y2 = (y + PLAYER_HEIGHT - 1) / TILE_SIZE;

	//Horizontal
	if (x_vel <= 0)
	{
		if ((level->getTileType(new_x, old_y) == COLLIDE && level->getTileType(new_x, old_y) != SPIKE) || 
			(level->getTileType(new_x, old_y2) == COLLIDE && level->getTileType(new_x, old_y2) != SPIKE))
		{
			new_x = new_x + (1 - new_x + (int)new_x);
			x_vel = 0;
		}
	}
	else
	{
		if ((level->getTileType(new_x2, old_y) == COLLIDE && level->getTileType(new_x2, old_y) != SPIKE) || 
			(level->getTileType(new_x2, old_y2) == COLLIDE && level->getTileType(new_x2, old_y2) != SPIKE))
		{
			new_x -= (new_x2 - (int)new_x2);
			x_vel = 0;
		}
	}
	x = new_x * TILE_SIZE;
	new_x = x / TILE_SIZE;
	new_x2 = (x + PLAYER_WIDTH - 1) / TILE_SIZE;

	//Vertical
	if (y_vel <= 0)
	{
		if ((level->getTileType(new_x, new_y) == COLLIDE && level->getTileType(new_x, new_y) != SPIKE) || 
			(level->getTileType(new_x2, new_y) == COLLIDE && level->getTileType(new_x2, new_y) != SPIKE))
		{
			new_y = new_y + (1 - new_y + (int)new_y);
			y_vel = 0;
		}
		else
		{
			OnGround = false;
		}
	}
	else
	{
		if ((level->getTileType(new_x, new_y2) == COLLIDE && level->getTileType(new_x, new_y2) != SPIKE) || 
			(level->getTileType(new_x2, new_y2) == COLLIDE && level->getTileType(new_x2, new_y2) != SPIKE))
		{
			OnGround = true;
			new_y = new_y - (new_y2 - (int)new_y2);
			y_vel = 0;
		}
		else 
		{
			OnGround = false;
		}
	}
	y = new_y * TILE_SIZE;


	//Check collision with spike tile
	int x1 = (x) / TILE_SIZE;
	int y1 = (y) / TILE_SIZE;
	int x2 = (x + PLAYER_WIDTH - 1) / TILE_SIZE;
	int y2 = (y + PLAYER_HEIGHT - 1) / TILE_SIZE;

	SDL_Rect Player_Hitbox = { (int)x, (int)y, PLAYER_WIDTH, PLAYER_HEIGHT };
	SDL_Rect Spike_Hitbox;
	//Check spike above
	if (level->getTileID(x1, y1) == spike_down || level->getTileID(x2, y1) == spike_down) {
		Spike_Hitbox = { x1 * TILE_SIZE + 1, y1 * TILE_SIZE, TILE_SIZE - 2, TILE_SIZE / 2 };
		if (SDL_HasIntersection(&Player_Hitbox, &Spike_Hitbox)) {
			alive = false;
		}
		Spike_Hitbox = { x2 * TILE_SIZE + 1, y1 * TILE_SIZE, TILE_SIZE - 2, TILE_SIZE / 2 };
		if (SDL_HasIntersection(&Player_Hitbox, &Spike_Hitbox)) {
			alive = false;
		}
	}
	//Check spike below
	if (level->getTileID(x1, y2) == spike_up || level->getTileID(x2, y2) == spike_up) {
		Spike_Hitbox = { x1 * TILE_SIZE + 1, y2 * TILE_SIZE + TILE_SIZE / 2, TILE_SIZE - 2, TILE_SIZE / 2 };
		if (SDL_HasIntersection(&Player_Hitbox, &Spike_Hitbox)) {
			alive = false;
		}
		Spike_Hitbox = { x2 * TILE_SIZE + 1, y2 * TILE_SIZE + TILE_SIZE / 2, TILE_SIZE - 2, TILE_SIZE / 2 };
		if (SDL_HasIntersection(&Player_Hitbox, &Spike_Hitbox)) {
			alive = false;
		}
	}
	//Check spike on the left
	if (level->getTileID(x1, y1) == spike_right || level->getTileID(x1, y2) == spike_right) {
		Spike_Hitbox = { x1 * TILE_SIZE, y1 * TILE_SIZE + 1, TILE_SIZE / 2, TILE_SIZE - 2 };
		if (SDL_HasIntersection(&Player_Hitbox, &Spike_Hitbox)) {
			alive = false;
		}
		Spike_Hitbox = { x1 * TILE_SIZE, y2 * TILE_SIZE + 1, TILE_SIZE / 2, TILE_SIZE - 2 };
		if (SDL_HasIntersection(&Player_Hitbox, &Spike_Hitbox)) {
			alive = false;
		}
	}
	//Check spike on the right
	if (level->getTileID(x2, y1) == spike_left || level->getTileID(x2, y2) == spike_left) {
		Spike_Hitbox = { x2 * TILE_SIZE + TILE_SIZE / 2, y1 * TILE_SIZE + 1, TILE_SIZE / 2, TILE_SIZE - 2 };
		if (SDL_HasIntersection(&Player_Hitbox, &Spike_Hitbox)) {
			alive = false;
		}
		Spike_Hitbox = { x2 * TILE_SIZE + TILE_SIZE / 2, y2 * TILE_SIZE + 1, TILE_SIZE / 2, TILE_SIZE - 2 };
		if (SDL_HasIntersection(&Player_Hitbox, &Spike_Hitbox)) {
			alive = false;
		}
	}
}																						
							
void Player::CheckEntity(Map* level)
{
	int x1, y1, x2, y2;
	x1 = x; y1 = y;
	x2 = PLAYER_WIDTH;
	y2 = PLAYER_HEIGHT;
	SDL_Rect Player_Hitbox = { x1, y1, x2, y2 };


	SDL_Rect Clock_Hitbox;
	for (int i = 0; i < (int)level->clocks.size(); i++) 
	{
		Clock_Hitbox = { (int)level->clocks[i].getX(), 
						 (int)level->clocks[i].getY(), 
						 (int)level->clocks[i].getW(), 
						 (int)level->clocks[i].getH() };
		
		if (SDL_HasIntersection(&Player_Hitbox, &Clock_Hitbox)) 
		{
			Game::tick += level->clocks[i].getType();
			pickupClock->PlaySound(5, 0);
			level->clocks[i].Delete();
			level->clocks.erase(level->clocks.begin() + i);
		}
	}

	SDL_Rect Key_Hitbox;
	for (int i = 0; i < (int)level->keys.size(); i++) 
	{
		Key_Hitbox = { (int)level->keys[i].getX(),
						 (int)level->keys[i].getY(),
						 (int)level->keys[i].getW(),
						 (int)level->keys[i].getH() };

		if (SDL_HasIntersection(&Player_Hitbox, &Key_Hitbox)) 
		{
			level->keyModify(level->keys[i]);
			pickupKey->PlaySound(4, 0);
			level->keys[i].Delete();
			level->keys.erase(level->keys.begin() + i);
		}
	}


	SDL_Rect Bread_Hitbox = { level->getGoal().getX(),
							  level->getGoal().getY(),
							  level->getGoal().getW(),
							  level->getGoal().getH() };
	if (SDL_HasIntersection(&Player_Hitbox, &Bread_Hitbox)) 
	{
		level->setMapStatus(true);
	}
}
