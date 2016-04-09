#include "Globals.h"
#include "Application.h"
#include "ModuleTextures.h"
#include "ModuleInput.h"
#include "ModuleParticles.h"
#include "ModuleRender.h"
#include "ModulePlayer.h"

// Reference at https://www.youtube.com/watch?v=OEhmUuehGOA

ModulePlayer::ModulePlayer()
{
	graphics = NULL;
	current_animation = NULL;

	/* consider p2_shooting a temporary general name for now

	p2_shooting.PushBack({ 20, 63, 91, 187 })		//left; no shoot
	p2_shooting.PushBack({ 130, 63, 132, 187 });	//left; shoot

	p2_shooting.PushBack({ 282, 60, 96, 189 });
	p2_shooting.PushBack({ 397, 61, 126, 190 });

	p2_shooting.PushBack({ 543, 61, 84, 188 });
	p2_shooting.PushBack({ 647, 36, 91, 213 });

	p2_shooting.PushBack({ 758, 57, 78, 191 });		//top; no shoot
	p2_shooting.PushBack({ 856, 19, 78, 230 });		//top; shoot

	p2_shooting.PushBack({ 954, 61, 88, 187 });
	p2_shooting.PushBack({ 1061, 49, 98, 200 });

	p2_shooting.PushBack({ 1179, 53, 98, 196 });
	p2_shooting.PushBack({ 1297, 58, 128, 191 });

	p2_shooting.PushBack({ 1455, 60, 118, 189 });	//right; no shoot
													//right; shoot ---MISSING
	*/

	position.x = 384;    //Initial x position of the player
	position.y = 552;	//I dunno the correct initial y position yet, but let's work with this one for now


	/*down here is the original code from class, to have it as reference*/
	/* idle animation (just the ship)
	idle.PushBack({66, 1, 32, 14});

	// move upwards
	up.PushBack({100, 1, 32, 14});
	up.PushBack({132, 0, 32, 14});
	up.loop = false;
	up.speed = 0.1f;

	// Move down
	down.PushBack({33, 1, 32, 14});
	down.PushBack({0, 1, 32, 14});
	down.loop = false;
	down.speed = 0.1f;*/
}

ModulePlayer::~ModulePlayer()
{}

// Load assets
bool ModulePlayer::Start()
{
	LOG("Loading player");

	//graphics = App->textures->Load(".png");

	return true;
}

// Unload assets
bool ModulePlayer::CleanUp()
{
	LOG("Unloading player");

	App->textures->Unload(graphics);

	return true;
}

// Update: draw background
update_status ModulePlayer::Update()
{
	int speed = 1;

	if(App->input->keyboard[SDL_SCANCODE_A] == KEY_STATE::KEY_REPEAT)
	{
		position.x -= speed;
	}

	if(App->input->keyboard[SDL_SCANCODE_D] == KEY_STATE::KEY_REPEAT)
	{
		position.x += speed;
	}

	if(App->input->keyboard[SDL_SCANCODE_S] == KEY_STATE::KEY_REPEAT)
	{
		position.y += speed;
		if(current_animation != &down)
		{
			down.Reset();
			current_animation = &down;
		}
	}

	if(App->input->keyboard[SDL_SCANCODE_W] == KEY_STATE::KEY_REPEAT)
	{
		position.y -= speed;
		if(current_animation != &up)
		{
			up.Reset();
			current_animation = &up;
		}
	}



	if (App->input->keyboard[SDL_SCANCODE_SPACE] == KEY_STATE::KEY_REPEAT)
	{
		
		App->particles->AddParticle(App->particles->laser, position.x + (speed*2), position.y, 0);
		
		
	}


	if(App->input->keyboard[SDL_SCANCODE_B] == KEY_STATE::KEY_DOWN)
	{
		App->particles->AddParticle(App->particles->explosion, position.x, position.y + 25);
		App->particles->AddParticle(App->particles->explosion, position.x - 25, position.y, 500);
		App->particles->AddParticle(App->particles->explosion, position.x, position.y - 25, 1000);
		App->particles->AddParticle(App->particles->explosion, position.x + 25, position.y, 1500);
	}

	if(App->input->keyboard[SDL_SCANCODE_S] == KEY_STATE::KEY_IDLE
	   && App->input->keyboard[SDL_SCANCODE_W] == KEY_STATE::KEY_IDLE)
		current_animation = &idle;

	// Draw everything --------------------------------------

	App->render->Blit(graphics, position.x, position.y, &(current_animation->GetCurrentFrame()));

	return UPDATE_CONTINUE;
}