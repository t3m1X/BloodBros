#ifndef __ModuleAudio_H__
#define __ModuleAudio_H__

#include "Module.h"
#include "Globals.h"
#include "SDL_mixer/include/SDL_mixer.h"

#define MAX_SFX 50
#define FADE 2000 //ms

class ModuleAudio : public Module
{
public:
	ModuleAudio();
	~ModuleAudio();

	bool Init();
	bool CleanUp();

	bool PlayMusic(const char* path);
	bool StopMusic();

	Mix_Chunk* const LoadSFX(const char* path);
	bool PlaySFX(Mix_Chunk* sfx);
	bool UnloadSFX(Mix_Chunk* sfx);



public:
	Mix_Chunk* soundfx[MAX_SFX];
	Mix_Music* music = nullptr;
	uint last_sfx = 0;
	Uint32 this_call = 0;
	Uint32 next_call = 0;
};

#endif // __ModuleAudio_H__