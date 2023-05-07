#pragma once

#ifndef Game_h
#define Game_h

#include <iostream>
#include <cmath>
#include <string>
#include "Time.h"
#include "GameConfig.h"
#include "SoundManager.h"

#if _WIN32
	#include "SDL.h"
	#include "SDL_image.h"
	#include "SDL_ttf.h"
#elif __APPLE__
	#include "SDL2/SDL.h"
	#include "SDL2/SDL_image.h"
	#include "SDL2/SDL_ttf.h"
#endif //!define

class Game
{
public:
	Game();
	~Game();

	void createGame(const char* title, int _x, int _y, int width, int height, int flags);
	void loadResources();
	void hanbleInput();
	void Update();
	void Render();
	void Clean();
	void loadMenuControl();
	void loadUI();

	bool Playing() { return isPlaying; };
	bool Running() { return isRunning; };
	
	static SDL_Renderer* renderer;
	static SDL_Rect camera;
	static SDL_Rect randVar;
	static LTimer time;

	static SDL_Texture* background;
	static SDL_Texture* grass;
	static SDL_Texture* dirt;
	static SDL_Texture* spike;
	static SDL_Texture* blue_box;
	static SDL_Texture* green_box;
	static SDL_Texture* key_box;

	static SDL_Texture* clock;
	static SDL_Texture* toaster;
	static SDL_Texture* key;

	static int const_tick;
	static int tick;
	static int pre_tick;
	static int timePerTick;

private:
	SDL_Window* window;

	TTF_Font* title_font;
	TTF_Font* menu_font;

	//Text texture
	SDL_Texture* game_title;
	SDL_Texture* main_screen_text;
	SDL_Texture* menu_button;
	SDL_Texture* level_indicator;
	SDL_Texture* flap_metter;
	SDL_Texture* menu_control;
	bool openMenu;

	SDL_Texture* main_screen_background;
	SDL_Texture* staminaBar;
	SDL_Texture* staminaBar_bg;
	SDL_Texture* tickBar;
	SDL_Texture* non_tickBar;
	SDL_Texture* square_animation;
	

	Sound* cd_sfx;
	Sound* level_complete;
	bool mute_sfx;

	Music* gameOST;

	bool isPlaying;
	bool isRunning;
	bool stopUpdate;

	int curTime;
	int preTime;
	bool jumpTick;

	int titleOffSet = 5;
	int pre_EventTick;

	int levelAnimationTime;
	int size = 1;
	int angle = 0;
	bool switchLevel = false;
};
#endif // !1




