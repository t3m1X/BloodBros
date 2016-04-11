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
	insert_coins.PushBack({ 203, 5, 293, 37 });
	insert_coins.PushBack({ 203, 323, 293, 37 });
	insert_coins.loop = true;
	insert_coins.speed = 5.0f;
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

	App->render->Blit(UserInterface, SCREEN_WIDTH - 400, SCREEN_HEIGHT- 55, &(insert_coins.GetCurrentFrame()));



	return UPDATE_CONTINUE;
}