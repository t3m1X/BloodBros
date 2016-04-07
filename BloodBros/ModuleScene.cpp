#include "Globals.h"
#include "Application.h"
#include "ModuleTextures.h"
#include "ModuleRender.h"
#include "ModulePlayer.h"
#include "ModuleScene.h"

ModuleScene::ModuleScene()
{
	// Back
	back.x = 20;
	back.y = 20;
	back.w = 768;
	back.h = 671;

	// Right house
	right_house.x = 788;
	right_house.y = 20;
	right_house.w = 336;
	right_house.h = 432;
}

ModuleScene::~ModuleScene()
{}

// Load assets
bool ModuleScene::Start()
{
	LOG("Loading background");
	
	background = App->textures->Load("Stage_1_Background.png");

	//App->player->Enable();
	
	return true;
}

// UnLoad assets
bool ModuleScene::CleanUp()
{
	LOG("Unloading space scene");

	App->textures->Unload(background);
	App->player->Disable();
	
	return true;
}

// Update: draw background
update_status ModuleScene::Update()
{
	// Move camera forward -----------------------------
	/*int scroll_speed = 1;

	App->player->position.x += 1;
	App->render->camera.x -= 3;
	*/

	// Draw everything --------------------------------------

	App->render->Blit(background, 0, 0 , &back, 1.0f);

	
	return UPDATE_CONTINUE;
}