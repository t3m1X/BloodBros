#ifndef __ModulePlayer_H__
#define __ModulePlayer_H__

#include "Module.h"
#include "Animation.h"
#include "p2Point.h"

struct SDL_Texture;

class ModulePlayer : public Module
{
private:
	enum SCREEN_PORTION
	{
		FAR_LEFT = 0,
		LEFT,
		LEFT_MIDDLE,
		MIDDLE,
		RIGHT_MIDDLE,
		RIGHT,
		FAR_RIGHT
	};

	int const portion_calculate();

public:
	ModulePlayer();
	~ModulePlayer();

	bool Start();
	update_status Update();
	bool CleanUp();

public:

	SDL_Texture* player = nullptr;
	SDL_Texture* crosstexture = nullptr;
	Animation cross;
	Animation* current_animation = nullptr;
	Animation idle[7];
	Animation down[7];
	iPoint position;
	iPoint cposition; //cross position 
};

#endif