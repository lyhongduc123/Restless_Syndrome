#include "Game.h"
#include "Texture.h"
#include "Entity.h"
#include "Map.h"
#include "Player.h"
#include "LevelsAttribute.h"

Game::Game() {}

Game::~Game() {}

//
SDL_Renderer* Game::renderer = nullptr;
SDL_Rect Game::camera = { 0, 0, SCREEN_WIDTH, SCREEN_HEIGHT };
SDL_Rect Game::randVar;
LTimer Game::time;

LevelsAttribute* Level;

//
SDL_Texture* Game::background = nullptr;
SDL_Texture* Game::grass = nullptr;
SDL_Texture* Game::dirt = nullptr;
SDL_Texture* Game::spike = nullptr;
SDL_Texture* Game::blue_box = nullptr;
SDL_Texture* Game::green_box = nullptr;
SDL_Texture* Game::key_box = nullptr;
SDL_Texture* Game::clock = nullptr;
SDL_Texture* Game::toaster = nullptr;
SDL_Texture* Game::key = nullptr;

int Game::tick = 4;
int Game::pre_tick = 0;
int Game::const_tick = 4;
int Game::timePerTick = 520;

SDL_Rect main_screen_text_rect = { SCREEN_WIDTH / 3, SCREEN_HEIGHT * 3 / 5, SCREEN_WIDTH / 3, 50 };

void Game::createGame(const char* title, int _x, int _y, int width, int height, int flags) 
{
	if (SDL_Init(SDL_INIT_EVERYTHING) == 0) 
	{
		std::cout << "SDL initialized sucessful." << std::endl;

		window = SDL_CreateWindow(title, _x, _y, width, height, flags);
		if (window == NULL)
		{
			std::cout << "Failed to create window: " << SDL_GetError() << std::endl;
		}

		renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED);
		if (renderer == NULL) 
		{
			std::cout << "Failed to create renderer: " << SDL_GetError() << std::endl;
			SDL_SetRenderDrawColor(renderer, 255, 255, 255, 0);
		}

		if (TTF_Init() == -1) 
		{
			std::cout << "Failed to initialize TTF... : " << TTF_GetError() << std::endl;
		}

		title_font = TTF_OpenFont(FONT_PATH, 32);
		if (title_font == nullptr) 
		{
			std::cout << "Could not load font!" << std::endl;
			exit(1);
		}

		isRunning = true;
		isPlaying = false;
		stopUpdate = false;

		loadResources();
		Level = new LevelsAttribute();
		Level->loadLevel();
		gameOST->PlaySound(100);
	}
	else 
	{
		std::cout << "Failed to initialize SDL... : " << SDL_GetError() << std::endl;
		isRunning = false;
	}
}



void Game::loadResources() 
{
	//Map tile
	background = Texture::loadTexture("assets/Background/level_background.jpg");
	grass = Texture::loadTexture("assets/Tile/tiles.png");
	dirt = Texture::loadTexture("assets/Tile/tiles.png");
	spike = Texture::loadTexture(SPIKE_PATH);
	blue_box = Texture::loadTexture("assets/Tile/blue_block_v2.png");
	green_box = Texture::loadTexture("assets/Tile/green_block_v2.png");
	key_box = Texture::loadTexture("assets/Tile/key_block.png");
	//Entity
	clock = Texture::loadTexture("assets/Entity/clock.png");
	toaster = Texture::loadTexture("assets/Entity/toaster.png");
	key = Texture::loadTexture("assets/Entity/key.png");
	//Stamina bar
	staminaBar = Texture::loadTexture("assets/UI/stamina_bar.png");
	staminaBar_bg = Texture::loadTexture("assets/UI/dark_stamina_bar.png");
	//Cooldown tick bar
	tickBar = Texture::loadTexture("assets/UI/tick.png");
	non_tickBar = Texture::loadTexture("assets/UI/non_tick.png");
	//Sfx
	level_complete = new Sound("assets/Sound/level_pass.wav");
	cd_sfx = new Sound("assets/Sound/cd.wav");
	//Music
	gameOST = new Music("assets/Sound/Leko - Restless Wing Syndrome OST_noncopyrighted.mp3");
	//Animation
	square_animation = Texture::loadFullTexture("assets/UI/square.png");


	//Menu, text
	main_screen_background = Texture::loadFullTexture("assets/Background/main_screen_background.png");
	menu_control = Texture::loadFullTexture("assets/UI/MENU.png");
	game_title = Texture::loadTextureText(title_font, "Restless Syndrome", { 0, 0, 255 });
	main_screen_text = Texture::loadTextureText(title_font, "Press any key to start", { 255, 55, 255 });
	menu_button = Texture::loadTextureText(title_font, "'C' to show control", { 255, 255, 255 });
	level_indicator = Texture::loadTextureText(title_font, "Lvl 1", { 255, 0, 255 });
	flap_metter = Texture::loadTextureText(title_font, "FLAP METTER", { 255, 255, 255 });
}


void Game::hanbleInput() 
{
	SDL_Event event;
	SDL_PollEvent(&event);

	switch (event.type) {
		case SDL_QUIT:
			isRunning = false;
			break;
		case SDL_KEYDOWN:
			if (!isPlaying)
			{
				stopUpdate = true;
			}
			if (isPlaying)
			{
				if (event.key.keysym.sym == SDLK_s)
				{
					if (time.getTime() - pre_EventTick <= 200) 
					{
						Level->increaseLevel();
						Level->loadLevel();
					}
					pre_EventTick = time.getTime();
				}
				if (event.key.keysym.sym == SDLK_c) 
				{
					if (openMenu) openMenu = false;
					else openMenu = true;

					SDL_DestroyTexture(menu_button);
					if(openMenu) menu_button = Texture::loadTextureText(title_font, "\"C\" TO HIDE CONTROL", { 255, 255, 255 });
					else menu_button = Texture::loadTextureText(title_font, "\"C\" TO SHOW CONTROL", { 255, 255, 255 });
				}
			}
			
			if (event.key.keysym.sym == SDLK_m) 
			{
				if (gameOST->GetVolume() == 0) 
				{
					gameOST->SetVolume(MIX_MAX_VOLUME);
				}
				else gameOST->SetVolume(0);
			}

			if (event.key.keysym.sym == SDLK_n) 
			{
				if (mute_sfx) mute_sfx = false;
				else mute_sfx = true;
			}

			if (event.key.keysym.sym == SDLK_r)
			{
				Level->player->setKill();
			}
			break;
		case SDL_MOUSEBUTTONDOWN:
			int xMouse, yMouse;
			SDL_GetMouseState(&xMouse, &yMouse);
			std::cout << xMouse + camera.x << "," << yMouse + camera.y << std::endl;
			break;
		default:
			break;
	}
	if (isPlaying) {
		Level->player->Input(event);
	}
	
}


void Game::Update() 
{
	if (isPlaying) {
		if (mute_sfx)
		{
			Mix_MasterVolume(0);
		}
		else
		{
			Mix_MasterVolume(MIX_MAX_VOLUME);
		}

		camera.x = Level->player->getX() - SCREEN_WIDTH / 2;
		camera.y = Level->player->getY() - SCREEN_HEIGHT / 2;

		//Clamp camera to game boundaries
		if (camera.x < 0) camera.x = 0;
		if (camera.y < TILE_SIZE) camera.y = TILE_SIZE;
		if (camera.x + camera.w >= Level->map->getMapLength() * TILE_SIZE) camera.x = Level->map->getMapLength() * TILE_SIZE - camera.w;
		if (camera.y + camera.h >= Level->map->getMapHeight() * TILE_SIZE - TILE_SIZE) camera.y = Level->map->getMapHeight() * TILE_SIZE - camera.h - TILE_SIZE;

		curTime = time.getTime();
		if (Level->player->isAlive())
		{
			//Jump ticking cooldown
			if (!stopUpdate)
			{
				if (curTime / timePerTick != preTime / timePerTick && tick > 0)
				{
					cd_sfx->PlaySound(1, 0);
					pre_tick = tick;
					tick--;
				}
				preTime = curTime;

				if (tick == 0)
				{
					Level->player->Jump();
					jumpTick = true;

					if (Level->map->getMapTick()) Level->map->setMapTick(false);
					else Level->map->setMapTick(true);
				}

				if (tick > const_tick || tick == 0)
				{
					tick = const_tick;
				}
			}

			//Gliding - update player status
			if (Level->player->isGliding())
			{
				Level->player->Glide();
			}
			
			Level->player->Update(Level->map);
		}
		else
		{
			if (curTime - preTime >= 2000 && !stopUpdate) {
				Level->loadLevel();
				Level->player->Update(Level->map);
			}
		}

		//Camera shake
		if ((!Level->player->isAlive() && curTime - preTime <= 100) || jumpTick) {
			randVar.x = (rand() % 20 + 1) - 10;		//Shake x
			randVar.y = (rand() % 20 + 1) - 10;		//Shake y
			jumpTick = false;
		}
		else {
			randVar.x = randVar.y = 0;
		}
		
		//Check level status
		if (Level->map->getMapStatus()) {
			if(!stopUpdate) level_complete->PlaySound(-1, 0);
			stopUpdate = true;
			if (switchLevel) {
				Level->increaseLevel();
				Level->loadLevel();
			}
		}

		if (level_indicator != nullptr) SDL_DestroyTexture(level_indicator);
		std::string str = "LVL ";
		str += std::to_string(Level->getLevel());
		level_indicator = Texture::loadTextureText(title_font, str, { 255, 255, 255 });
	}
}

//Variable for animated title
bool increaseHeight = false;
SDL_Rect game_title_rect = { SCREEN_WIDTH / 4, SCREEN_HEIGHT / 4, SCREEN_WIDTH / 2, 100 };

void Game::Render() {
	SDL_RenderClear(renderer);
	
	if (isPlaying) 
	{
		Level->map->drawMap();
		Level->player->Draw();

		if (Level->player->getStamina() != STAMINA_MAX && Level->player->isAlive()) 
		{
			SDL_Rect bar = { Level->player->getDst().x, Level->player->getDst().y - PLAYER_HEIGHT/2, PLAYER_WIDTH*2, PLAYER_HEIGHT };
			Texture::drawText(staminaBar_bg, bar);
			bar.w = (Level->player->getStamina() * bar.w)/STAMINA_MAX;
			SDL_RenderCopy(renderer, staminaBar, NULL, &bar);
		}

		int width_values = 400 / const_tick;
		for (int i = 0; i < const_tick; i++) 
		{
			SDL_Rect dst = { 20 + i * width_values, 0, width_values, 100 };
			SDL_RenderCopy(renderer, non_tickBar, NULL, &dst);
		}
		for (int i = 0; i < tick; i++) 
		{
			SDL_Rect dst = { 20 + i * width_values, 0, width_values, 100 };
			SDL_RenderCopy(renderer, tickBar, NULL, &dst);
		}
		if(tick != -1) loadUI();
		//
		if (openMenu)
		{
			loadMenuControl();
		}

	}
	if (!isPlaying) 
	{
		//Main background
		SDL_Rect main_screen_rect = { 0, 0, SCREEN_WIDTH, SCREEN_HEIGHT };
		SDL_RenderCopy(renderer, main_screen_background, NULL, &main_screen_rect);
		//Game title
		SDL_RenderCopy(renderer, game_title, NULL, &game_title_rect);
		//Press any key to start
		if((time.getTime()/1000)%2 == 0) SDL_RenderCopy(renderer, main_screen_text, NULL, &main_screen_text_rect);

		if (game_title_rect.y >= (SCREEN_HEIGHT / 4 + 20)) increaseHeight = true;
		if (game_title_rect.y <= SCREEN_HEIGHT / 4) increaseHeight = false;
	
		if (titleOffSet == 0) {
			if (!increaseHeight) game_title_rect.y++;
			if (increaseHeight) game_title_rect.y--;
			titleOffSet = 5;
		}
		else {
			titleOffSet--;
		}
	}

	//Level pass animation
	if (stopUpdate)
	{
		if (size >= 0)
		{
			if (!switchLevel)
			{
				if (size > 50)
				{
					switchLevel = true;
					if (!isPlaying) isPlaying = true;
				}
				size++;
			}
			else
			{
				size--;
			}

			angle += 15;
			int offSet = 100 * size;
			SDL_Rect s_dst = { Level->player->getDst().x - offSet / 2, Level->player->getDst().y - offSet / 2, offSet, offSet };
			SDL_Rect s_src = { 0,0,32,32 };
			Texture::drawTextureExtra(square_animation, s_src, s_dst, (double)angle, NULL, SDL_FLIP_NONE);
		}
		else {
			size = 0;
			stopUpdate = false;
			switchLevel = false;
		}
	}

	SDL_RenderPresent(renderer);
}


void Game::Clean() {
	SDL_DestroyRenderer(renderer);
	SDL_DestroyTexture(game_title);
	SDL_DestroyTexture(main_screen_text);
	SDL_DestroyTexture(main_screen_background);
	//
	//delete jump_sfx;
	//delete cd_sfx;
	//
	SDL_DestroyTexture(background);
	SDL_DestroyTexture(grass);
	SDL_DestroyTexture(spike);
	SDL_DestroyTexture(dirt);
	SDL_DestroyTexture(blue_box);
	SDL_DestroyTexture(green_box);
	SDL_DestroyTexture(key_box);
	//Entity
	SDL_DestroyTexture(clock);
	SDL_DestroyTexture(toaster);
	SDL_DestroyTexture(key);
	//UI
	SDL_DestroyTexture(staminaBar);
	SDL_DestroyTexture(staminaBar_bg);
	SDL_DestroyTexture(tickBar);
	SDL_DestroyTexture(non_tickBar);
	SDL_DestroyTexture(menu_control);
	SDL_DestroyTexture(menu_button);
	SDL_DestroyTexture(level_indicator);
	//
	SDL_DestroyTexture(square_animation);
	//
	SDL_DestroyWindow(window);
	TTF_CloseFont(title_font);
	SDL_Quit();

	std::cout << "Cleared!" << std::endl;
}

void Game::loadMenuControl()
{
	SDL_Rect menu_control_dst = { SCREEN_WIDTH / 3, 100, SCREEN_WIDTH / 3, SCREEN_HEIGHT - 200 };
	SDL_SetTextureBlendMode(menu_control, SDL_BLENDMODE_ADD);
	SDL_RenderCopy(renderer, menu_control, NULL, &menu_control_dst);
}

void Game::loadUI()
{
	//"Press C to show/hide control"
	SDL_Rect textRect = { SCREEN_WIDTH * 2 / 5, 0, 400, 50 };
	SDL_RenderCopy(renderer, menu_button, NULL, &textRect);
	//Level xx text
	SDL_Rect level_indicator_rect = { SCREEN_WIDTH - 200, 0, 100, 50 };
	SDL_RenderCopy(renderer, level_indicator, NULL, &level_indicator_rect);
	//Flap metter text
	SDL_Rect flap_ = { 30, 60, 200, 50 };
	SDL_RenderCopy(renderer, flap_metter, NULL, &flap_);
}