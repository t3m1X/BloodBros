#include "Globals.h"
#include "Application.h"
#include "ModuleTextures.h"
#include "ModuleAudio.h"
#include "ModuleInput.h"
#include "ModuleRender.h"
#include "ModuleIntro.h"
#include "ModuleScene.h"
#include "ModuleFadeToBlack.h"
#include "ModuleText.h"
#include "ModuleUserI.h"

ModuleUserI::ModuleUserI()
{
	insert_coins.PushBack({ 137, 3, 200, 25 });
	insert_coins.PushBack({ 137, 230, 200, 25 });
	insert_coins.loop = true;
	insert_coins.speed = 0.1f;

	life_ball.PushBack({ 0, 288, 48, 48 });
	
}
ModuleUserI::~ModuleUserI()
{
}
bool ModuleUserI::Start()
{
	LOG("Loading intro");

	UserInterface = App->textures->Load("sprites/ui-rearranged.png");
	credit = App->text->AddText(SCREEN_WIDTH/2 - 2*TILE,SCREEN_HEIGHT-TILE/2,"CREDIT");
	credit_counter = App->text->AddNumber(SCREEN_WIDTH / 2 + TILE/2 + 10, SCREEN_HEIGHT - TILE / 2, credits, 2);

	return true;
}
bool ModuleUserI::CleanUp()
{
	LOG("Unloading intro");

	App->textures->Unload(UserInterface);
	App->text->EraseText(credit);
	App->text->EraseText(credit_counter);

	return true;
}
update_status ModuleUserI::Update()
{
	if (hitpoints >= 2)
	{
		App->render->Blit(UserInterface, 0, SCREEN_HEIGHT - 72, &(life_ball.GetCurrentFrame()));
		if (hitpoints == 3)
			App->render->Blit(UserInterface, 40, SCREEN_HEIGHT - 72, &(life_ball.GetCurrentFrame()));
	}

	if (App->input->keyboard[SDL_SCANCODE_1] == KEY_STATE::KEY_DOWN)
	{
		++credits;
		credit_counter->SetNumber(credits, 2);
	}


	/*
	App->render->Blit(UserInterface, SCREEN_WIDTH - SCREEN_WIDTH/3, SCREEN_HEIGHT - 25, &(insert_coins.GetCurrentFrame()));
	App->render->Blit(UserInterface, (SCREEN_WIDTH / 2) - 50, SCREEN_HEIGHT - 25, &credits, 1.0f);*/

	return UPDATE_CONTINUE;
}