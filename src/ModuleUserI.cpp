#include "Globals.h"
#include "Application.h"
#include "ModuleTextures.h"
#include "ModuleAudio.h"
#include "ModuleInput.h"
#include "ModuleRender.h"
#include "ModuleIntro.h"
#include "ModuleScene.h"
#include "ModuleFadeToBlack.h"
#include "ModuleUserI.h"

ModuleUserI::ModuleUserI()
{
	insert_coins.PushBack({ 137, 3, 200, 25 });
	insert_coins.PushBack({ 137, 230, 200, 25 });
	insert_coins.loop = true;
	insert_coins.speed = 0.1f;
}
ModuleUserI::~ModuleUserI()
{
}
bool ModuleUserI::Start()
{
	LOG("Loading intro");

	UserInterface = App->textures->Load("sprites/UI_player.png");

	return true;
}
bool ModuleUserI::CleanUp()
{
	LOG("Unloading intro");

	App->textures->Unload(UserInterface);
	

	return true;
}
update_status ModuleUserI::Update()
{

	App->render->Blit(UserInterface, SCREEN_WIDTH - SCREEN_WIDTH/3, SCREEN_HEIGHT- 30, &(insert_coins.GetCurrentFrame()));

	return UPDATE_CONTINUE;
}