#ifndef __ModuleAudio_H__
#define __ModuleAudio_H__

#include "Module.h"
#include "Globals.h"
#include "SDL_mixer/include/SDL_mixer.h"

#define MAX_SFX 50
#define MAX_MUSIC 10
#define FADE 2000 //ms

class ModuleAudio : public Module
{
public:
	ModuleAudio();
	~ModuleAudio();

	bool Init();
	bool CleanUp();

	bool PlayMusic(Mix_Music* music, int loops = -1);
	bool StopMusic();
	Mix_Music* LoadMusic(const char* path);
	void UnloadMusic(Mix_Music* music);

	Mix_Chunk* const LoadSFX(const char* path);
	bool PlaySFX(Mix_Chunk* sfx);
	bool UnloadSFX(Mix_Chunk* sfx);



public:
	Mix_Chunk* soundfx[MAX_SFX];
	Mix_Music* musics[MAX_MUSIC];
	uint last_sfx = 0;
	uint this_call;
	uint next_call;
};

#endif // __ModuleAudio_H__