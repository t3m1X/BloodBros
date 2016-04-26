#ifndef __APPLICATION_H__
#define __APPLICATION_H__

#include "Globals.h"

#define NUM_MODULES 14

class ModuleUserI;
class ModuleEnd;
class ModuleIntro;
class ModuleWindow;
class ModuleInput;
class ModuleTextures;
class ModuleRender;
class ModuleAudio;
class ModuleParticles;
class ModuleScene;
class ModuleCollision;
class ModulePlayer;
class ModuleEnemies;
class ModuleFadeToBlack;
class ModuleEnemies;
class Module;

class Application
{
public:

	Module* modules[NUM_MODULES];
	ModuleWindow* window;
	ModuleRender* render;
	ModuleInput* input;
	ModuleTextures* textures;
	ModuleAudio* audio;
	ModuleScene* scene;
	ModuleCollision* collision;
	ModulePlayer* player;
	ModuleEnemies* enemies;
	ModuleFadeToBlack* fade;
	ModuleParticles* particles;
	ModuleIntro* intro;
	ModuleEnd* end;
	ModuleUserI* useri;
	ModuleEnemies* enemy;

public:

	Application();
	~Application();

	bool Init();
	update_status Update();
	bool CleanUp();

};

// Global var made extern for Application ---
extern Application* App;

#endif // __APPLICATION_H__