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
	int distance = (cposition.x + 70/2) - (position.x + 87/2);
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
	position.y = SCREEN_HEIGHT/2 + 117;	 
	cposition.x = (SCREEN_WIDTH - 60) / 2;
	cposition.y = position.y - 150;

	cross.PushBack({ 11, 17, 69, 63 });
	cross.PushBack({ 107, 17, 69, 63 });
	cross.loop = true;
	cross.speed = 0.2f;

	idle[FAR_LEFT].PushBack({ 50, 22, 87, 180 });
	idle[LEFT].PushBack({ 146, 20, 87, 180 });
	idle[LEFT_MIDDLE].PushBack({ 248, 20, 87, 180 });
	idle[MIDDLE].PushBack({ 359, 20, 87, 180 });
	idle[RIGHT_MIDDLE].PushBack({ 455, 20, 87, 180 });
	idle[RIGHT].PushBack({ 542, 20, 87, 180 });
	idle[FAR_RIGHT].PushBack({ 629, 20, 87, 180 });

	idle[FAR_LEFT_F].PushBack({ 24, 216, 111, 180 });
	idle[FAR_LEFT_F].PushBack({ 24, 411, 111, 180 });
	idle[LEFT_F].PushBack({ 146, 20, 87, 180 });
	idle[LEFT_F].PushBack({ 146, 20, 87, 180 });
	idle[LEFT_MIDDLE_F].PushBack({ 248, 20, 87, 180 });
	idle[LEFT_MIDDLE_F].PushBack({ 248, 20, 87, 180 });
	idle[MIDDLE_F].PushBack({ 359, 20, 87, 180 });
	idle[MIDDLE_F].PushBack({ 359, 20, 87, 180 });
	idle[RIGHT_MIDDLE_F].PushBack({ 455, 20, 87, 180 });
	idle[RIGHT_MIDDLE_F].PushBack({ 455, 20, 87, 180 });
	idle[RIGHT_F].PushBack({ 542, 20, 87, 180 });
	idle[RIGHT_F].PushBack({ 542, 20, 87, 180 });
	idle[FAR_RIGHT_F].PushBack({ 629, 20, 87, 180 });
	idle[FAR_RIGHT_F].PushBack({ 629, 20, 87, 180 });

	down[FAR_LEFT].PushBack({ 935, 20, 96, 135 });
	down[LEFT].PushBack({ 1034, 20, 84, 135 });
	down[LEFT_MIDDLE].PushBack({ 1136, 20, 84, 135 });
	down[MIDDLE].PushBack({ 1229, 20, 81, 135 });
	down[RIGHT_MIDDLE].PushBack({ 1331, 20, 81, 135 });
	down[RIGHT].PushBack({ 1421, 20, 90, 135 });
	down[FAR_RIGHT].PushBack({ 1511, 20, 96, 135 });

	walk_right.PushBack({ 24, 602, 102, 180 });
	walk_right.PushBack({ 128, 602, 96, 177 });
	walk_right.PushBack({ 233, 600, 120, 180 });
	walk_right.speed = 0.2f;

	walk_left.PushBack({ 612, 600, 102, 180 });
	walk_left.PushBack({ 514, 602, 96, 177 });
	walk_left.PushBack({ 385, 600, 120, 180 });
	walk_left.speed = 0.2f;
}

ModulePlayer::~ModulePlayer()
{}

// Load assets
bool ModulePlayer::Start()
{
	LOG("Loading player");

	player = App->textures->Load("sprites/p1_sprites.png");
	crosstexture = App->textures->Load("sprites/aims.png"); 

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
	int speed = 4;
	bool firing = false;
	position.y = SCREEN_HEIGHT / 2 + 117;
	int screen_portion = portion_calculate();
	current_animation = &idle[screen_portion];


	if (App->input->keyboard[SDL_SCANCODE_S] == KEY_STATE::KEY_REPEAT)
	{
		if (cposition.y < position.y + 15)
			cposition.y += speed * 2;

		if (App->input->keyboard[SDL_SCANCODE_W] != KEY_STATE::KEY_REPEAT)
		{
			current_animation = &down[screen_portion];
			if (App->input->keyboard[SDL_SCANCODE_A] != KEY_STATE::KEY_REPEAT && App->input->keyboard[SDL_SCANCODE_D] != KEY_STATE::KEY_REPEAT)
				position.y = SCREEN_HEIGHT / 2 + 117 + 25;
		}

	}

	if (App->input->keyboard[SDL_SCANCODE_W] == KEY_STATE::KEY_REPEAT)
	{
		if (cposition.y > -35)
			cposition.y -= speed * 2;

	}

	if(App->input->keyboard[SDL_SCANCODE_A] == KEY_STATE::KEY_REPEAT)
	{
		if (position.x > 0)
			position.x -= speed;
		if (cposition.x > -35) //middle of the cross
			cposition.x -= speed * 2;

		if (App->input->keyboard[SDL_SCANCODE_D] != KEY_STATE::KEY_REPEAT)
			current_animation = &walk_left;
	}

	if(App->input->keyboard[SDL_SCANCODE_D] == KEY_STATE::KEY_REPEAT)
	{
		if (position.x < SCREEN_WIDTH - 87)
			position.x += speed;
		if (cposition.x < SCREEN_WIDTH - 35) //the middle of the cross
			cposition.x += speed * 2;

		if (App->input->keyboard[SDL_SCANCODE_A] != KEY_STATE::KEY_REPEAT)
			current_animation = &walk_right;
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

	// Draw everything --------------------------------------
	
	App->render->Blit(crosstexture, cposition.x, cposition.y, &(cross.GetCurrentFrame()));
	App->render->Blit(player, position.x, position.y, &(current_animation->GetCurrentFrame()));
	

	return UPDATE_CONTINUE;
}