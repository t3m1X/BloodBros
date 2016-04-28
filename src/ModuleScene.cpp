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

#include "SDL/include/SDL.h"
#pragma comment( lib, "SDL_mixer/libx86/SDL2_mixer.lib" )

#define ENEMY_GAUGE 10

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

	
	c_cactus2 = App->collision->AddCollider({ SCREEN_WIDTH / 2 - SCREEN_WIDTH / 4, SCREEN_HEIGHT / 2 - cactus2.h - 10, cactus2.w, cactus2.h }, COLLIDER_ENEMY);
	c_cactus3 = App->collision->AddCollider({ SCREEN_WIDTH - SCREEN_WIDTH / 3 - 35, SCREEN_HEIGHT / 2 - cactus2.h - 10, cactus2.w, cactus2.h }, COLLIDER_ENEMY);
	
	App->enemies->AddEnemy(ENEMY_TYPES::PLANE, 30, 80);

	App->enemies->AddEnemy(ENEMY_TYPES::L_WATERTOWER, 0, 0);
	App->enemies->AddEnemy(ENEMY_TYPES::R_WATERTOWER, SCREEN_WIDTH-255, 0);
	App->enemies->AddEnemy(ENEMY_TYPES::DANCER, 0, 360);
		
	

	App->player->Enable();
	App->useri->Enable();
	App->enemies->Enable();
	App->input->Enable();

	start_time = SDL_GetTicks();
	next_enemy_time = start_time + 3000;
	
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
	App->player->killcount = 0;

	
	return true;
}

// Update: draw background
update_status ModuleScene::Update()
{
	current_time = SDL_GetTicks();

	// Spawn enemies----------------------------------------
	if (current_time >= next_enemy_time)
	{
		next_enemy_time = current_time + 5000;
		App->enemies->AddEnemy(ENEMY_TYPES::G_COWBOY, SCREEN_WIDTH, 300, false);
	}
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

	if (App->player->killcount == ENEMY_GAUGE)
		App->fade->FadeToBlack(this, App->end, 1.0f);
	
	if (App->useri->hitpoints == 0)
		App->fade->FadeToBlack(this, App->intro, 1.0f);


	
	return UPDATE_CONTINUE;
}

void ModuleScene::OnCollision(Collider* c1, Collider* c2)
{
	
}
