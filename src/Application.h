#ifndef __APPLICATION_H__
#define __APPLICATION_H__

#include "Globals.h"

#define NUM_MODULES 16

class ModuleText;
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
class ModuleItems;
class ModulePlayer;
class ModuleEnemies;
class ModuleFadeToBlack;
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
	ModuleEnemies* enemies;
	ModuleItems* items;
	ModulePlayer* player;
	ModuleFadeToBlack* fade;
	ModuleParticles* particles;
	ModuleIntro* intro;
	ModuleEnd* end;
	ModuleUserI* useri;
	ModuleText* text;

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