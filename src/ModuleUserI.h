#ifndef __MODULEUSERI_H__
#define __MODULEUSERI_H__

#include "Module.h"
#include "Animation.h"
#include "p2Point.h"

struct Text;

class ModuleUserI : public Module
{
public:

	ModuleUserI();
	~ModuleUserI();

	bool Start();
	update_status Update();
	bool CleanUp();

public:

	SDL_Texture* UserInterface = nullptr;
	Animation insert_coins;
	Animation life_ball;
	SDL_Rect credits;
	Uint32 hitpoints = 3;
	Text* test;

};


#endif //__MODULEUSERI_H__