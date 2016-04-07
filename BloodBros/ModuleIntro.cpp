#include "Globals.h"
#include "Application.h"
#include "ModuleTextures.h"
#include "ModuleInput.h"
#include "ModuleRender.h"
#include "ModuleIntro.h"
#include "ModuleSceneSpace.h"
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

	IntroScreen = App->textures->Load("rtype/intro.png");
	
	return true;
}
bool ModuleIntro::CleanUp()
{
	LOG("Unloading intro");

	App->textures->Unload(IntroScreen);


	return true;
}
update_status ModuleIntro::Update()
{

	App->render->Blit(IntroScreen, 0, 0, nullptr);

	if (App->input->keyboard[SDL_SCANCODE_SPACE] == KEY_DOWN)
	{

		App->fade->FadeToBlack(this, App->scene_space, 1.0f);
		
	}

	return UPDATE_CONTINUE;
}