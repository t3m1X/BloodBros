#include "Globals.h"
#include "Application.h"
#include "ModuleTextures.h"
#include "ModuleAudio.h"
#include "ModuleInput.h"
#include "ModuleRender.h"
#include "ModuleIntro.h"
#include "ModuleScene.h"
#include "ModuleFadeToBlack.h"
#include "ModulePlayer.h"

ModuleScene::ModuleScene()
{
	// Back
	back.x = 20;
	back.y = 20;
	back.w = SCREEN_WIDTH; //768
	back.h = SCREEN_HEIGHT; //671

	// Right house
	right_house.x = 788;
	right_house.y = 20;
	right_house.w = 336;
	right_house.h = 430;
}

ModuleScene::~ModuleScene()
{}

// Load assets
bool ModuleScene::Start()
{
	LOG("Loading background");
	
	background = App->textures->Load("sprites/Stage_1_Background.png");
	App->audio->PlayMusic("sound/music/stage1_bg.wav");

	App->player->Enable();
	
	return true;
}

// UnLoad assets
bool ModuleScene::CleanUp()
{
	LOG("Unloading space scene");

	App->textures->Unload(background);
	App->player->Disable();
	App->audio->StopMusic();
	
	return true;
}

// Update: draw background
update_status ModuleScene::Update()
{
	// Draw everything --------------------------------------

	App->render->Blit(background, 0, 0 , &back, 1.0f);
	App->render->Blit(background, 421, 0, &right_house, 1.0f);

	if (App->input->keyboard[SDL_SCANCODE_SPACE] == KEY_DOWN)
	{
		App->fade->FadeToBlack(this, App->intro, 1.0f);

	}
	
	return UPDATE_CONTINUE;
}
