#ifndef __ModulePlayer_H__
#define __ModulePlayer_H__

#include "Module.h"
#include "Animation.h"
#include "p2Point.h"

struct SDL_Texture;
struct Mix_Chunk;

enum player_states
{
	ST_UNKNOWN,

	ST_IDLE,
	ST_WALK_RIGHT,
	ST_WALK_LEFT,
	ST_CROUCH,
	ST_ROLLING_LEFT,
	ST_ROLLING_RIGHT,
	ST_FIRE_STANDING,
	ST_FIRE_CROUCH,
	ST_DEATH,
	ST_DANCE
};

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
	void Collision();

public:

	SDL_Texture* player = nullptr;
	SDL_Texture* crosstexture = nullptr;
	Mix_Chunk* shoot = nullptr;
	Mix_Chunk* hit_sound = nullptr;
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
	Animation godbutt;

	Animation dance1;
	Animation dance2;
	Animation dance3;
	Animation dance4;
	Animation dance5;

	iPoint position;
	iPoint cposition; //cross position 
	Collider* cross_collider;
	Collider* player_collider;
	Collider* ground_collider;
	player_states state;
	Uint32 current_time;
	Uint32 damage_cooldown;
	Uint32 shooting_cooldown;
	Uint32 blink_time;
	Uint32 dance_start;
	bool godmode = false;

	bool hit = false;
	bool blink = true;
};
#endif