#include "Globals.h"
#include "Application.h"
#include "ModuleTextures.h"
#include "ModuleRender.h"
#include "ModulePlayer.h"
#include "ModuleScene.h"


ModuleScene::ModuleScene()
{}

ModuleScene::~ModuleScene()
{}

// Load assets
bool ModuleScene::Start()
{
	LOG("Loading space scene");
	
	background = App->textures->Load("sprites/background_first_release.png");

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

	App->render->Blit(background, 0, 0, NULL);

	
	return UPDATE_CONTINUE;
}