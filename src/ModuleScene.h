#ifndef __MODULESCENE_H__
#define __MODULESCENE_H__

#include "Module.h"

struct SDL_Texture;
#include "SDL_mixer/include/SDL_mixer.h"

class ModuleScene : public Module
{
private:
	bool beaten;

public:
	ModuleScene();
	~ModuleScene();

	bool Start();
	update_status Update();
	bool CleanUp();
	void OnCollision(Collider* c1, Collider* c2);
	bool toppipe;
	bool toppipe2;

	void beatStage();

public:

	SDL_Texture* background = nullptr;
	SDL_Rect back;
	SDL_Rect right_pipe;
	SDL_Rect left_pipe;
	SDL_Rect cactus1;
	SDL_Rect cactus2;
	Collider* c_cactus1;
	Collider* c_cactus2;
	Collider* c_cactus3;

	Uint32 start_time;
	Uint32 current_time;
	Uint32 first_wave_time;
	Uint32 second_wave_time;
	Uint32 third_wave_time;
	Uint32 fourth_wave_time;
	Uint32 fifth_wave_time;

	Mix_Music* victory_dance;
	Mix_Music* regular_music;

};

#endif // __MODULESCENE_H__