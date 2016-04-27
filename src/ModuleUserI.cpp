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

	life_ball.PushBack({ 60, 195, 18, 18 });

	credits.x = 5;
	credits.y = 3;
	credits.w = 113;
	credits.h = 25;
	
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
	if (hitpoints >= 2)
	{
		App->render->Blit(UserInterface, 0, SCREEN_HEIGHT - 50, &(life_ball.GetCurrentFrame()));
		if (hitpoints == 3)
			App->render->Blit(UserInterface, 18, SCREEN_HEIGHT - 50, &(life_ball.GetCurrentFrame()));
	}
	/*
	App->render->Blit(UserInterface, SCREEN_WIDTH - SCREEN_WIDTH/3, SCREEN_HEIGHT - 25, &(insert_coins.GetCurrentFrame()));
	App->render->Blit(UserInterface, (SCREEN_WIDTH / 2) - 50, SCREEN_HEIGHT - 25, &credits, 1.0f);*/

	return UPDATE_CONTINUE;
}