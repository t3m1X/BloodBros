#ifndef __ModulePlayer_H__
#define __ModulePlayer_H__

#include "Module.h"
#include "Animation.h"
#include "p2Point.h"

struct SDL_Texture;
struct Mix_Chunk;

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
		FAR_RIGHT,
		FAR_LEFT_F,
		LEFT_F,
		LEFT_MIDDLE_F,
		MIDDLE_F,
		RIGHT_MIDDLE_F,
		RIGHT_F,
		FAR_RIGHT_F
	};

	int const portion_calculate();
	int tempx; 

public:
	ModulePlayer();
	~ModulePlayer();

	bool Start();
	update_status Update();
	bool CleanUp();

public:

	SDL_Texture* player = nullptr;
	SDL_Texture* crosstexture = nullptr;
	Mix_Chunk* shoot = nullptr;
	Animation cross;
	Animation fcross;
	Animation* current_animation = nullptr;
	Animation idle[14];
	Animation down[14];
	Animation walk_right;
	Animation walk_left;
	Animation roll_right;
	Animation roll_left;
	Animation dead;
	iPoint position;
	iPoint cposition; //cross position 
	Collider* cross_collider;
	Collider* player_collider;
	Collider* ground_collider;

	bool hit = false;
};

#endif