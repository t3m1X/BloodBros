#include "Globals.h"
#include "Application.h"
#include "ModuleTextures.h"
#include "ModuleAudio.h"
#include "ModuleInput.h"
#include "ModuleRender.h"
#include "ModuleEnd.h"
#include "ModuleScene.h"
#include "ModuleFadeToBlack.h"
#include "ModulePlayer.h"
#include "ModuleIntro.h"
#include "ModuleUserI.h"


ModuleEnd::ModuleEnd()
{
	// Back
	back.x = 20;
	back.y = 20;
	back.w = SCREEN_WIDTH;
	back.h = SCREEN_HEIGHT;
}
ModuleEnd::~ModuleEnd()
{
}
bool ModuleEnd::Start()
{
	LOG("Loading intro");

	EndScreen = App->textures->Load("sprites/temporary_end_game.png");
	//App->audio->PlayMusic("sound/music/startscreen.wav");
	App->input->Enable();
	App->useri->Disable();

	return true;
}
bool ModuleEnd::CleanUp()
{
	LOG("Unloading endscreen");

	App->textures->Unload(EndScreen);
	App->end->Disable();
	App->input->Disable();
	App->textures->Disable();


	return true;
}
update_status ModuleEnd::Update()
{

	App->render->Blit(EndScreen, 0, 0, &back, 1.0f);

	if (App->input->keyboard[SDL_SCANCODE_SPACE] == KEY_DOWN)
	{
		App->fade->FadeToBlack(this, App->intro, 1.0f);
	}

	return UPDATE_CONTINUE;
}