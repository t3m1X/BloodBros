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
#include "ModuleCollision.h"
#include "ModuleEnd.h"
#include "ModuleEnemies.h"
#include "ModuleUserI.h"

#include <stdlib.h> 
#include <time.h>  

#include "SDL/include/SDL.h"
#pragma comment( lib, "SDL_mixer/libx86/SDL2_mixer.lib" )

ModuleScene::ModuleScene()
{
	// Back
	back.x = 0;
	back.y = 0;
	back.w = SCREEN_WIDTH; //768
	back.h = SCREEN_HEIGHT; //671

	
	cactus2.x = 1817;
	cactus2.y = 260;
	cactus2.w = 28;
	cactus2.h = 60;
}

ModuleScene::~ModuleScene()
{}

// Load assets
bool ModuleScene::Start()
{
	LOG("Loading background");
	
	background = App->textures->Load("sprites/stage_4_3_Background.png");
	App->audio->PlayMusic("sound/music/stage1_bg.wav");

	/*
	c_cactus2 = App->collision->AddCollider({ SCREEN_WIDTH / 2 - SCREEN_WIDTH / 4, SCREEN_HEIGHT / 2 - cactus2.h - 10, cactus2.w, cactus2.h }, COLLIDER_ENEMY);
	c_cactus3 = App->collision->AddCollider({ SCREEN_WIDTH - SCREEN_WIDTH / 3 - 35, SCREEN_HEIGHT / 2 - cactus2.h - 10, cactus2.w, cactus2.h }, COLLIDER_ENEMY);
	*/
	//App->enemies->AddEnemy(ENEMY_TYPES::TOP_PIPES, 100, 12, true, true);
	App->enemies->AddEnemy(ENEMY_TYPES::LPIPE, 0, SCREEN_HEIGHT - 275, true, true);
	App->enemies->AddEnemy(ENEMY_TYPES::RPIPE, SCREEN_WIDTH-336, SCREEN_HEIGHT - 275, true, true);
	App->enemies->AddEnemy(ENEMY_TYPES::L_WATERTOWER, 0, 0, false, true);
	App->enemies->AddEnemy(ENEMY_TYPES::R_WATERTOWER, SCREEN_WIDTH - 200, 0, false, true);
	
	App->enemies->AddEnemy(ENEMY_TYPES::DANCER, 0, 400, true);
	App->enemies->AddEnemy(ENEMY_TYPES::CACTUS, SCREEN_WIDTH / 2 - 50 , SCREEN_HEIGHT / 2 - SCREEN_HEIGHT / 4 + 130, true);

	//test wave
	
	App->enemies->AddEnemy(ENEMY_TYPES::V_FORMATION_R3, SCREEN_WIDTH / 2 - 20, 248, false);
	App->enemies->AddEnemy(ENEMY_TYPES::V_FORMATION_L3, SCREEN_WIDTH / 2 - 80, 248, false);

	App->enemies->AddEnemy(ENEMY_TYPES::V_FORMATION_R2, SCREEN_WIDTH / 2 + 10, 250, false);
	App->enemies->AddEnemy(ENEMY_TYPES::V_FORMATION_L2, SCREEN_WIDTH / 2 - 110, 250, false);

	App->enemies->AddEnemy(ENEMY_TYPES::V_FORMATION_R1, SCREEN_WIDTH / 2 + 60, 300, false);
	App->enemies->AddEnemy(ENEMY_TYPES::V_FORMATION_L1, SCREEN_WIDTH / 2 - 160, 300, false);
	
	//testing wagon & horse
	App->enemies->AddEnemy(ENEMY_TYPES::WAGON, SCREEN_WIDTH / 2 + 60, 300, false);

	App->enemies->AddEnemy(ENEMY_TYPES::HORSE, SCREEN_WIDTH / 2 - 60, 300, false);

	App->enemies->AddEnemy(ENEMY_TYPES::PLANE, 30, 80, true);

		
	App->player->Enable();
	App->useri->Enable();
	App->enemies->Enable();
	App->input->Enable();

	start_time = SDL_GetTicks();
	first_wave_time = start_time + 3000;
	second_wave_time = start_time + 10000;
	third_wave_time = start_time+ 14252;
	fourth_wave_time = start_time + 10000;
	
	return true;
}

// UnLoad assets
bool ModuleScene::CleanUp()
{
	LOG("Unloading space scene");

	App->textures->Unload(background);
	App->player->Disable();
	App->input->Disable();
	App->audio->StopMusic();
	App->useri->Disable();
	App->enemies->Disable();  
	App->useri->killcount = 0;

	
	return true;
}

// Update: draw background
update_status ModuleScene::Update()
{
	current_time = SDL_GetTicks();

	// Enemy waves----------------------------------------
	if (current_time >= first_wave_time)
	{
		first_wave_time = current_time + 6500;
		App->enemies->AddEnemy(ENEMY_TYPES::G_COWBOY, SCREEN_WIDTH, 250, false);

	}
	if (current_time >= second_wave_time)
	{
		second_wave_time = current_time + 20000;
		App->enemies->AddEnemy(ENEMY_TYPES::PLANE, 30, 80, true);
		switch (rand() % 5)
		{
		case 3:
			App->enemies->AddEnemy(ENEMY_TYPES::DANCER, 0, 400, true);
			break;
		}

	}
if (current_time >= third_wave_time)
	{
		third_wave_time = current_time + 14252;

		App->enemies->AddEnemy(ENEMY_TYPES::V_FORMATION_R3, SCREEN_WIDTH / 2 - 20, 248, false);
		App->enemies->AddEnemy(ENEMY_TYPES::V_FORMATION_L3, SCREEN_WIDTH / 2 - 80, 248, false);
		
		App->enemies->AddEnemy(ENEMY_TYPES::V_FORMATION_R2, SCREEN_WIDTH / 2 + 10, 250, false);
		App->enemies->AddEnemy(ENEMY_TYPES::V_FORMATION_L2, SCREEN_WIDTH / 2 - 110, 250, false);
		
		App->enemies->AddEnemy(ENEMY_TYPES::V_FORMATION_R1, SCREEN_WIDTH/2+60, 300, false);
		App->enemies->AddEnemy(ENEMY_TYPES::V_FORMATION_L1, SCREEN_WIDTH/2-160, 300, false);
		
		
	}
	/*if (current_time >= fourth_wave_time)
	{
		first_wave_time = current_time + 8000;
		App->enemies->AddEnemy(ENEMY_TYPES::V_FORMATION_R1, -48, 280, false);
	}*/

	// Draw everything --------------------------------------
	App->render->Blit(background, 0, 0 , &back, 1.0f);
	App->render->Blit(background, 0, 60, &left_pipe, 1.0f);
	App->render->Blit(background, SCREEN_WIDTH-right_pipe.w, 60, &right_pipe, 1.0f);
	App->render->Blit(background, SCREEN_WIDTH / 2 - cactus1.w, SCREEN_HEIGHT/2, &cactus1, 1.0f);
	App->render->Blit(background, SCREEN_WIDTH / 2 - SCREEN_WIDTH /4, SCREEN_HEIGHT / 2 - cactus2.h - 10, &cactus2, 1.0f);   /// CACTUS 2
	App->render->Blit(background, SCREEN_WIDTH - SCREEN_WIDTH / 3 - 35, SCREEN_HEIGHT / 2 - cactus2.h - 10, &cactus2, 1.0f); /// CACTUS 3
	

	if (App->input->keyboard[SDL_SCANCODE_SPACE] == KEY_DOWN)
	{
		App->fade->FadeToBlack(this, App->modules[10], 1.0f);

	}

	if (App->useri->killcount == ENEMY_GAUGE)
		App->fade->FadeToBlack(this, App->end, 1.0f);
	
	if (App->useri->hitpoints == 0)
	{
		App->useri->score = 0;

		if (App->useri->credit == 0)
			App->fade->FadeToBlack(this, App->intro, 1.0f);
		else
		{
			App->useri->credit--;
			App->useri->hitpoints = 3;
		}
	}


	
	return UPDATE_CONTINUE;
}

void ModuleScene::OnCollision(Collider* c1, Collider* c2)
{
	
}
