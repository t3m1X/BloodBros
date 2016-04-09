#include "Globals.h"
#include "Application.h"
#include "ModuleTextures.h"
#include "ModuleInput.h"
#include "ModuleRender.h"
#include "ModuleIntro.h"
#include "ModuleStage.h"
#include "ModuleScene.h"
#include "ModuleFadeToBlack.h"

 // This module is temporary, I imagine that we can use the intro module for doing what this module is made for
 // But I don't know how to implement it in the intro module :(

ModuleStage::ModuleStage()
{
}
ModuleStage::~ModuleStage()
{
}
bool ModuleStage::Start()
{
	LOG("Loading intro");

	StageScreen = App->textures->Load("sprites/stage_1(notdefinitive).png");

	return true;
}
bool ModuleStage::CleanUp()
{
	LOG("Unloading intro");

	App->textures->Unload(StageScreen);

	return true;
}
update_status ModuleStage::Update()
{

	App->render->Blit(StageScreen, 0, 0, nullptr);

	if (App->input->keyboard[SDL_SCANCODE_SPACE] == KEY_DOWN)
	{
		App->fade->FadeToBlack(this, App->scene, 1.0f);
	}

	return UPDATE_CONTINUE;
}