#ifndef __APPLICATION_H__
#define __APPLICATION_H__

#include "Globals.h"

#define NUM_MODULES 9

class ModuleIntro;
class ModuleWindow;
class ModuleInput;
class ModuleTextures;
class ModuleRender;
class ModuleParticles;
class ModuleScene;
class ModulePlayer;
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
	ModuleScene* scene;
	ModulePlayer* player;
	ModuleFadeToBlack* fade;
	ModuleParticles* particles;
	ModuleIntro* intro;

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