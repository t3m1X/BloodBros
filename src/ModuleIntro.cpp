#include "Globals.h"
#include "Application.h"
#include "ModuleTextures.h"
#include "ModuleAudio.h"
#include "ModuleInput.h"
#include "ModuleRender.h"
#include "ModuleIntro.h"
#include "ModuleScene.h"
#include "ModuleFadeToBlack.h"


ModuleIntro::ModuleIntro()
{
}
ModuleIntro::~ModuleIntro()
{
}
bool ModuleIntro::Start()
{
	LOG("Loading intro");

	IntroScreen = App->textures->Load("sprites/intro_screen.png");
	App->audio->PlayMusic("sound/music/startscreen.wav");
	
	return true;
}
bool ModuleIntro::CleanUp()
{
	LOG("Unloading intro");

	App->textures->Unload(IntroScreen);
	App->audio->StopMusic();

	return true;
}
update_status ModuleIntro::Update()
{

	App->render->Blit(IntroScreen, 0, 0, nullptr);

	if (App->input->keyboard[SDL_SCANCODE_SPACE] == KEY_DOWN)
	{
			App->fade->FadeToBlack(this, App->scene, 1.0f);
		
	}

	return UPDATE_CONTINUE;
}