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
	back.x = 0;
	back.y = 0;
	back.w = SCREEN_WIDTH; //768
	back.h = SCREEN_HEIGHT; //671

	// Front
	left_pipe.x = 768;
	left_pipe.y = 63;
	left_pipe.w = 200;
	left_pipe.h = 449;
	
	right_pipe.x = 1334;
	right_pipe.y = 60;
	right_pipe.w = 257;
	right_pipe.h = 453;
	
}

ModuleScene::~ModuleScene()
{}

// Load assets
bool ModuleScene::Start()
{
	LOG("Loading background");
	
	background = App->textures->Load("sprites/stage_4_3_Background.png");
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
	App->render->Blit(background, 0, 60, &left_pipe, 1.0f);
	App->render->Blit(background, SCREEN_WIDTH-right_pipe.w, 60, &right_pipe, 1.0f);
	

	if (App->input->keyboard[SDL_SCANCODE_SPACE] == KEY_DOWN)
	{
		App->fade->FadeToBlack(this, App->intro, 1.0f);

	}
	
	return UPDATE_CONTINUE;
}
