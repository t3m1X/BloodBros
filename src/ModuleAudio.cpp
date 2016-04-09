#include "Globals.h"
#include "Application.h"
#include "ModuleAudio.h"

#include "SDL/include/SDL.h"
#pragma comment( lib, "SDL_mixer/libx86/SDL2_mixer.lib" )

ModuleAudio::ModuleAudio() : Module()
{
	for (uint i = 0; i < MAX_SFX; ++i)
		soundfx[i] = nullptr;
}

// Destructor
ModuleAudio::~ModuleAudio()
{}


bool ModuleAudio::Init()
{
	LOG("Init Audio library");
	bool ret = true;

	//Loading Audio Library and support for MP3 and OGG
	int flags = MIX_INIT_OGG;
	int init = Mix_Init(flags);

	if ((init & flags) != flags)
	{
		LOG("Could not initialize Audio lib. Mix_Init: %s", Mix_GetError());
		ret = false;
	}

	if (Mix_OpenAudio(44100, MIX_DEFAULT_FORMAT, 2, 1024) == -1)
	{
		LOG("Could not open audio channels. Mix_OpenAudio: %s", Mix_GetError());
		ret = false;
	}


	return ret;
}

// Called before quitting
bool ModuleAudio::CleanUp()
{
	LOG("Freeing Mix_Chunks and Sound library");

	for (uint i = 0; i < MAX_SFX; ++i)
		if (soundfx[i] != nullptr)
			Mix_FreeChunk(soundfx[i]);

	Mix_FreeMusic(music);

	Mix_CloseAudio();
	Mix_Quit();

	return true;
}

bool ModuleAudio::PlayMusic(const char* path)
{
	bool ret = false;
	music = Mix_LoadMUS(path);

	if (music == nullptr)
	{
		LOG("Could not load music with path: %s. Mix_LoadMUS: %s", path, Mix_GetError());
	}
	else
	{
		if (Mix_FadeInMusic(music, -1, FADE) == -1)
		{
			LOG("Could not play music with path: %s. Mix_FadeInMusic: %s", path, Mix_GetError());
		}
		else
			ret = true;
	}

	return ret;
}

bool ModuleAudio::StopMusic()
{
	bool ret = false;
	while (!Mix_FadeOutMusic(FADE) && Mix_PlayingMusic())
	{
		//waiting for the fade-out to complete
		//SDL_Delay(100);
	}

	Mix_FreeMusic(music);
	if (music = NULL)
		ret = true;

	return ret;
}

// Load new sound effect from file path
Mix_Chunk* const ModuleAudio::Load(const char* path)
{
	Mix_Chunk* sfx = NULL;
	sfx = Mix_LoadWAV(path);

	if (sfx == NULL)
	{
		LOG("Could not load sound effect with path: %s. Mix_LoadWAV: %s", path, Mix_GetError());
	}
	else
	{
		soundfx[last_sfx++] = sfx;
	}

	return sfx;
}

// Unload sound effect
bool ModuleAudio::Unload(Mix_Chunk* sfx)
{
	bool ret = false;

	for (uint i = 0; i < MAX_SFX; ++i)
	{
		if (sfx == soundfx[i])
		{
			Mix_FreeChunk(soundfx[i]);
			soundfx[i] = nullptr;
			ret = true;
			break;
		}
	}

	return ret;
}
