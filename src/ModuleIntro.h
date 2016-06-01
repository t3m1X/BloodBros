#ifndef __MODULEINTRO_H__
#define __MODULEINTRO_H__

#include "Module.h"
#include "Animation.h"
#include "p2Point.h"

#include "SDL_mixer/include/SDL_mixer.h"

class ModuleIntro : public Module
{
public:

	ModuleIntro();
	~ModuleIntro();

	bool Start();
	update_status Update();
	bool CleanUp();

public:

	SDL_Texture* IntroScreen = nullptr;
	SDL_Rect back;
	Mix_Music* bg_music;
};


#endif //__MODULEINTRO_H__