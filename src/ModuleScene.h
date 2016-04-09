#ifndef __MODULESCENE_H__
#define __MODULESCENE_H__

#include "Module.h"

struct SDL_Texture;

class ModuleScene : public Module
{
public:
	ModuleScene();
	~ModuleScene();

	bool Start();
	update_status Update();
	bool CleanUp();

public:

	SDL_Texture* background = nullptr;
	SDL_Rect back;
	SDL_Rect right_house;

};

#endif // __MODULESCENE_H__