#include "Application.h"
#include "ModuleWindow.h"
#include "ModuleRender.h"
#include "ModuleInput.h"
#include "ModuleTextures.h"
#include "ModuleAudio.h"
#include "ModuleScene.h"
#include "ModuleEnemies.h"
#include "ModulePlayer.h"
#include "ModuleFadeToBlack.h"
#include "ModuleParticles.h"
#include "ModuleIntro.h"
#include "ModuleUserI.h"
#include "ModuleCollision.h"
#include "ModuleItems.h"
#include "ModuleEnemies.h"
#include "ModuleEnd.h"
#include "ModuleText.h"



Application::Application()
{
	int i = 0;
	modules[i++] = window = new ModuleWindow();
	/*modules[i++] = render = new ModuleRender();*/
	modules[i++] = input = new ModuleInput();
	modules[i++] = textures = new ModuleTextures();
	modules[i++] = audio = new ModuleAudio();
	modules[i++] = scene = new ModuleScene();
	modules[i++] = enemies = new ModuleEnemies();
	modules[i++] = particles = new ModuleParticles();
	modules[i++] = items = new ModuleItems();
	modules[i++] = player = new ModulePlayer();
	modules[i++] = intro = new ModuleIntro();
	modules[i++] = end = new ModuleEnd();
	modules[i++] = useri = new ModuleUserI();
	modules[i++] = text = new ModuleText();
	modules[i++] = collision = new ModuleCollision();
	modules[i++] = fade = new ModuleFadeToBlack();
	modules[i++] = render = new ModuleRender();

}	

Application::~Application()
{
	for(int i = NUM_MODULES - 1; i >= 0; --i)
		delete modules[i];
}

bool Application::Init()
{
	bool ret = true;

	// Disable all stopped modules here
	player->Disable();
	scene->Disable();
	end->Disable();
	useri->Disable();
	enemies->Disable();
	input->Disable();
	// ---

	for(int i = 0; i < NUM_MODULES && ret == true; ++i)
		ret = modules[i]->Init();

	for(int i = 0; i < NUM_MODULES && ret == true; ++i)
		ret = modules[i]->IsEnabled() ? modules[i]->Start() : true;

	return ret;
}

update_status Application::Update()
{
	update_status ret = UPDATE_CONTINUE;

	for(int i = 0; i < NUM_MODULES && ret == UPDATE_CONTINUE; ++i)
		ret = modules[i]->IsEnabled() ? modules[i]->PreUpdate() : UPDATE_CONTINUE;

	for(int i = 0; i < NUM_MODULES && ret == UPDATE_CONTINUE; ++i)
		ret = modules[i]->IsEnabled() ? modules[i]->Update() : UPDATE_CONTINUE;

	for(int i = 0; i < NUM_MODULES && ret == UPDATE_CONTINUE; ++i)
		ret = modules[i]->IsEnabled() ? modules[i]->PostUpdate() : UPDATE_CONTINUE;

	return ret;
}

bool Application::CleanUp()
{
	bool ret = true;

	for(int i = NUM_MODULES - 1; i >= 0 && ret == true; --i)
		ret = modules[i]->CleanUp();

	return ret;
}