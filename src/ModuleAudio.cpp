#include "Globals.h"
#include "Application.h"
#include "ModuleAudio.h"

#include "SDL/include/SDL.h"
#include "SDL_mixer/include/SDL_mixer.h"
#pragma comment( lib, "SDL_mixer/libx86/SDL2_mixer.lib" )


ModuleAudio::ModuleAudio() : Module()
{
	for (uint i = 0; i < MAX_SFX; ++i)
		soundfx[i] = nullptr;
	for (uint i = 0; i < MAX_MUSIC; ++i)
		musics[i] = nullptr;

	this_call = 0;
	next_call = 0;
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

	if (Mix_OpenAudio(48000, MIX_DEFAULT_FORMAT, 2, 1024) == -1)
	{
		LOG("Could not open audio channels. Mix_OpenAudio: %s", Mix_GetError());
		ret = false;
	}

	Mix_AllocateChannels(100); //100 is a good quantity to avoid sounds running out of channels

	return ret;
}

// Called before quitting
bool ModuleAudio::CleanUp()
{
	LOG("Freeing Mix_Chunks and Sound library");

	for (uint i = 0; i < MAX_SFX; ++i)
		if (soundfx[i] != nullptr)
			Mix_FreeChunk(soundfx[i]);

	for (uint i = 0; i < MAX_MUSIC; ++i)
		if (musics[i] != nullptr)
			Mix_FreeMusic(musics[i]);

	Mix_CloseAudio();
	Mix_Quit();

	return true;
}

Mix_Music* ModuleAudio::LoadMusic(const char* path)
{
	Mix_Music* ret = NULL;
	ret = Mix_LoadMUS(path);
	for (uint i = 0; i < MAX_MUSIC; ++i)
	{
		if (musics[i] == nullptr)
		{
			musics[i] = ret;
			break;
		}
	}

	return ret;
}

bool ModuleAudio::PlayMusic(Mix_Music* music, int loops)
{
	bool ret = false;
	if (music == nullptr)
	{
		LOG("Could not load music. Mix_LoadMUS: %s", Mix_GetError());
	}
	else
	{
		if (Mix_FadeInMusic(music, loops, FADE) == -1)
		{
			LOG("Could not play music . Mix_FadeInMusic: %s", Mix_GetError());
		}
		else
			ret = true;
	}

	return ret;
}

bool ModuleAudio::StopMusic()
{
	Mix_FadeOutMusic(FADE);
	return true;
}

void ModuleAudio::UnloadMusic(Mix_Music* music)
{
	for (uint i = 0; i < MAX_MUSIC; ++i)
	{
		if (musics[i] == music)
		{
			Mix_FreeMusic(musics[i]);
			musics[i] = nullptr;
			break;
		}
	}
}

// Load new sound effect from file path
Mix_Chunk* const ModuleAudio::LoadSFX(const char* path)
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

bool ModuleAudio::PlaySFX(Mix_Chunk* sfx)
{
	bool ret = false;
	/*this_call = SDL_GetTicks();
	if (this_call >= next_call)
	{*/
		if (Mix_PlayChannel(-1, sfx, 0) == -1)
		{
			LOG("Mix_PlayChannel: %s\n", Mix_GetError());
		}
		else
			ret = true;
	//}
	return ret;
}

// Unload sound effect
bool ModuleAudio::UnloadSFX(Mix_Chunk* sfx)
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
