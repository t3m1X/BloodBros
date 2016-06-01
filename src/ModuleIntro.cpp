#include "Globals.h"
#include "Application.h"
#include "ModuleTextures.h"
#include "ModuleAudio.h"
#include "ModuleInput.h"
#include "ModuleRender.h"
#include "ModuleIntro.h"
#include "ModuleScene.h"
#include "ModuleFadeToBlack.h"
#include "ModuleEnd.h"
#include "ModulePlayer.h"
#include "ModuleUserI.h"


ModuleIntro::ModuleIntro()
{
	// Back
	back.x = 20;
	back.y = 20;
	back.w = SCREEN_WIDTH;
	back.h = SCREEN_HEIGHT;
}
ModuleIntro::~ModuleIntro()
{
}
bool ModuleIntro::Start()
{
	LOG("Loading intro");

	IntroScreen = App->textures->Load("sprites/intro_screen.png");
	bg_music = App->audio->LoadMusic("sound/music/startscreen.wav");
	App->audio->PlayMusic(bg_music);
	App->input->Enable();
	App->useri->hitpoints = 3;
	
	return true;
}
bool ModuleIntro::CleanUp()
{
	LOG("Unloading intro");

	App->textures->Unload(IntroScreen);
	App->end->Disable();
	App->player->Disable();
	App->scene->Disable();
	App->audio->StopMusic();
	App->audio->UnloadMusic(bg_music);
	App->input->Disable();

	return true;
}
update_status ModuleIntro::Update()
{

	App->render->Blit(IntroScreen, 0, 0, &back, 1.0f);

	if (App->input->keyboard[SDL_SCANCODE_SPACE] == KEY_DOWN)
	{
			App->fade->FadeToBlack(this, App->scene, 1.0f);
		
	}

	return UPDATE_CONTINUE;
}