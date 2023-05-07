#ifndef SoundManager_HPP
#define SoundManager_HPP

#if _WIN32 or __LINUX__
	#include "SDL_mixer.h"
#elif __APPLE__
	#inlude "SDL2/SDL_mixer.h"
#endif //!define

#include <iostream>

class Music
{
public:
	Music(const char* filepath) 
	{
		if (Mix_OpenAudio(44100, MIX_DEFAULT_FORMAT, MIX_DEFAULT_CHANNELS, 1024 == -1)) 
		{
			std::cout << "Audio library not working: " << Mix_GetError() << std::endl;
		}
		music = Mix_LoadMUS(filepath);
	};
	~Music() 
	{
		Mix_FreeMusic(music);
	};

	void PlaySound(int loops) 
	{
		if (music != nullptr) 
		{
			Mix_PlayMusic(music, loops);
		}
	}

	void PauseMusic() 
	{
		Mix_PauseMusic();
	}

	void SetVolume(int volume) 
	{
		Mix_VolumeMusic(volume);
	}

	int GetVolume() { return Mix_GetMusicVolume(music); };

private:
	Mix_Music* music;
};



class Sound
{
public:
	Sound(const char* filepath) 
	{
		if (Mix_OpenAudio(44100, MIX_DEFAULT_FORMAT, MIX_DEFAULT_CHANNELS, 1024 == -1)) 
		{
			std::cout << "Sound library not working: " << Mix_GetError() << std::endl;
		}
		sfx = Mix_LoadWAV(filepath);
	};
	~Sound() 
	{
		Mix_FreeChunk(sfx);
	};

	void PlaySound(int channel, int loop)
	{
		if (sfx != nullptr)
		{
			this->channel = channel;
			Mix_PlayChannel(channel, sfx, loop);
		}
	}

	void PauseSound()
	{
		if (!Mix_Paused(channel)) Mix_Pause(channel);
	}

private:
	Mix_Chunk* sfx;
	int channel = -1;
};

#endif // !SoundManager_HPP