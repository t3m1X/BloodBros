#include "Globals.h"
#include "Application.h"
#include "ModuleTextures.h"
#include "ModuleInput.h"
#include "ModuleParticles.h"
#include "ModuleRender.h"
#include "ModulePlayer.h"

// Reference at https://www.youtube.com/watch?v=OEhmUuehGOA

int const ModulePlayer::portion_calculate()
{
	int distance = cposition.x - position.x;
	int portion = SCREEN_WIDTH / 7;
	if (distance >= portion/2)
	{
		if (distance >= (2 * portion + portion / 2))
			return FAR_RIGHT;
		else if (distance >= (portion + portion / 2))
			return RIGHT;
		else
			return RIGHT_MIDDLE;
	}
	else if (distance <= -portion/2)
	{
		if (distance <= -(2 * portion + portion / 2))
			return FAR_LEFT;
		else if (distance <= -(portion + portion / 2))
			return LEFT;
		else
			return LEFT_MIDDLE;
	}
	else
		return MIDDLE;
}

ModulePlayer::ModulePlayer()
{
	player = NULL;
	current_animation = NULL;

	
	position.x = (SCREEN_WIDTH - 87) / 2 ;    //Initial x position of the player and crossbow, 87 is sprite width
	position.y = SCREEN_HEIGHT/2 + 117;	//I dunno the correct initial y position yet, but let's work with this one for now
	cposition.x = (SCREEN_WIDTH - 60) / 2;
	cposition.y = position.y - 150;

	cross.x = 0;
	cross.y = 0;
	cross.w = 60;
	cross.h = 60;

	idle[FAR_LEFT].PushBack({ 50, 22, 87, 180 });
	idle[LEFT].PushBack({ 146, 20, 87, 180 });
	idle[LEFT_MIDDLE].PushBack({ 248, 20, 87, 180 });
	idle[MIDDLE].PushBack({ 359, 20, 87, 180 });
	idle[RIGHT_MIDDLE].PushBack({ 455, 20, 87, 180 });
	idle[RIGHT].PushBack({ 542, 20, 87, 180 });
	idle[FAR_RIGHT].PushBack({ 629, 20, 87, 180 });



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

	player = App->textures->Load("sprites/p1_sprites.png");
	crosstexture = App->textures->Load("sprites/stage_1.png"); //placeholder

	return true;
}

// Unload assets
bool ModulePlayer::CleanUp()
{
	LOG("Unloading player");

	App->textures->Unload(player);

	return true;
}

// Update: draw background
update_status ModulePlayer::Update()
{
	int speed = 2;
	current_animation = &idle[portion_calculate()];


	if(App->input->keyboard[SDL_SCANCODE_A] == KEY_STATE::KEY_REPEAT)
	{
		position.x -= speed;
		cposition.x -= speed * 3;
	}

	if(App->input->keyboard[SDL_SCANCODE_D] == KEY_STATE::KEY_REPEAT)
	{
		position.x += speed;
		cposition.x += speed * 3;
	}

	if(App->input->keyboard[SDL_SCANCODE_S] == KEY_STATE::KEY_REPEAT)
	{
		cposition.y += speed * 3;
		//if(current_animation != &down)
		//{
		//	down.Reset();
		//	current_animation = &down;
		//}
	}

	if(App->input->keyboard[SDL_SCANCODE_W] == KEY_STATE::KEY_REPEAT)
	{
		cposition.y -= speed * 3;
		//if(current_animation != &up)
		//{
		//	up.Reset();
		//	current_animation = &up;
		//}
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

	//if(App->input->keyboard[SDL_SCANCODE_S] == KEY_STATE::KEY_IDLE
	//   && App->input->keyboard[SDL_SCANCODE_W] == KEY_STATE::KEY_IDLE)
	//	current_animation = &idle[0];

	// Draw everything --------------------------------------

	App->render->Blit(crosstexture, cposition.x, cposition.y, &cross, 1.0f);
	App->render->Blit(player, position.x, position.y, &(current_animation->GetCurrentFrame()));
	

	return UPDATE_CONTINUE;
}