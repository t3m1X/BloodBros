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
	left_pipe.w = 210;
	left_pipe.h = 470;
	
	right_pipe.x = 1334;
	right_pipe.y = 60;
	right_pipe.w = 257;
	right_pipe.h = 480;

	cactus1.x = 1933;
	cactus1.y = 196;
	cactus1.w = 48;
	cactus1.h = 124;

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

	c_left_pipe = App->collision->AddCollider({ SCREEN_WIDTH - left_pipe.w, 60, left_pipe.w, left_pipe.h }, COLLIDER_ENEMY);
	c_right_pipe = App->collision->AddCollider({ 0, 60, right_pipe.w-100, right_pipe.h-10 }, COLLIDER_ENEMY);
	c_cactus1 = App->collision->AddCollider({ SCREEN_WIDTH/2-cactus1.w, SCREEN_HEIGHT/2, cactus1.w, cactus1.h-cactus1.h/4}, COLLIDER_ENEMY);
	c_cactus2 = App->collision->AddCollider({ SCREEN_WIDTH / 2 - SCREEN_WIDTH / 4, SCREEN_HEIGHT / 2 - cactus2.h - 10, cactus2.w, cactus2.h }, COLLIDER_ENEMY);
	c_cactus3 = App->collision->AddCollider({ SCREEN_WIDTH - SCREEN_WIDTH / 3 - 35, SCREEN_HEIGHT / 2 - cactus2.h - 10, cactus2.w, cactus2.h }, COLLIDER_ENEMY);


	App->enemies->AddEnemy(ENEMY_TYPES::PLANE, 30, 80);

	App->enemies->AddEnemy(ENEMY_TYPES::G_COWBOY, -90, 120);


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
	App->end->Disable();
	
	return true;
}

// Update: draw background
update_status ModuleScene::Update()
{
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

	
	return UPDATE_CONTINUE;
}

void ModuleScene::OnCollision(Collider* c1, Collider* c2)
{
	
}
