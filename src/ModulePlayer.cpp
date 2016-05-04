#include "Globals.h"
#include "Application.h"
#include "ModuleTextures.h"
#include "ModuleInput.h"
#include "ModuleParticles.h"
#include "ModuleRender.h"
#include "ModulePlayer.h"
#include "ModuleAudio.h"
#include "ModuleCollision.h"
#include "ModuleUserI.h"

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

	fcross.PushBack({ 11, 105, 69, 63 });
	fcross.PushBack({ 107, 105, 69, 63 });
	fcross.PushBack({ 11, 201, 69, 63 });
	fcross.PushBack({ 107,201, 69, 63 });
	fcross.PushBack({ 11, 17, 69, 63 });
	fcross.PushBack({ 107, 105, 69, 63 });
	fcross.loop = true;
	fcross.speed = 0.2f;
	
	idle[FAR_LEFT].PushBack({ 0, 0, 144, 192 });
	idle[LEFT].PushBack({ 144, 0, 144, 192 });
	idle[LEFT_MIDDLE].PushBack({ 288, 0, 144, 192 });
	idle[MIDDLE].PushBack({ 432, 0, 144, 192 });
	idle[RIGHT_MIDDLE].PushBack({ 576, 0, 144, 192 });
	idle[RIGHT].PushBack({ 720, 0, 144, 192 });
	idle[FAR_RIGHT].PushBack({ 864, 0, 144, 192 });

	idle[FAR_LEFT_F].PushBack({ 0, 192, 144, 192 }); 
	idle[FAR_LEFT_F].PushBack({ 0, 384, 144, 192 });
	idle[FAR_LEFT_F].speed = 0.25f;
	idle[LEFT_F].PushBack({ 144, 192, 144, 192 });
	idle[LEFT_F].PushBack({ 144, 384, 144, 192 });
	idle[LEFT_F].speed = 0.25f;
	idle[LEFT_MIDDLE_F].PushBack({ 288, 192, 144, 192 });
	idle[LEFT_MIDDLE_F].PushBack({ 288, 384, 144, 192 });
	idle[LEFT_MIDDLE_F].speed = 0.25f;
	idle[MIDDLE_F].PushBack({ 432, 192, 144, 192 });
	idle[MIDDLE_F].PushBack({ 432, 384, 144, 192 });
	idle[MIDDLE_F].speed = 0.25f;
	idle[RIGHT_MIDDLE_F].PushBack({ 576, 192, 144, 192 });
	idle[RIGHT_MIDDLE_F].PushBack({ 576, 384, 144, 192 });
	idle[RIGHT_MIDDLE_F].speed = 0.25f;
	idle[RIGHT_F].PushBack({ 720, 192, 144, 192 });
	idle[RIGHT_F].PushBack({ 720, 384, 144, 192 });
	idle[RIGHT_F].speed = 0.25f;
	idle[FAR_RIGHT_F].PushBack({ 864, 192, 144, 192 });
	idle[FAR_RIGHT_F].PushBack({ 864, 384, 144, 192 });
	idle[FAR_RIGHT_F].speed = 0.25f;
	

	down[FAR_LEFT].PushBack({ 0, 576, 144, 192 });
	down[LEFT].PushBack({ 144, 576, 144, 192 });
	down[LEFT_MIDDLE].PushBack({ 288, 576, 144, 192 });
	down[MIDDLE].PushBack({ 432, 576, 144, 192 });
	down[RIGHT_MIDDLE].PushBack({ 576, 576, 144, 192 });
	down[RIGHT].PushBack({ 720, 576, 144, 192 });
	down[FAR_RIGHT].PushBack({ 864, 576, 144, 192 });

	down[FAR_LEFT_F].PushBack({ 0, 768, 144, 192 });
	down[FAR_LEFT_F].PushBack({ 0, 960, 144, 192 });
	down[FAR_LEFT_F].speed = 0.25f;
	//down[LEFT_F].PushBack({ 1034, 20, 84, 135 });
	down[LEFT_F].PushBack({ 144, 768, 144, 192 });//98
	down[LEFT_F].PushBack({ 144, 960, 144, 192 });
	down[LEFT_F].speed = 0.25f;
	//down[LEFT_MIDDLE_F].PushBack({ 1136, 20, 84, 135 });
	down[LEFT_MIDDLE_F].PushBack({ 288, 768, 144, 192 });
	down[LEFT_MIDDLE_F].PushBack({ 288, 960, 144, 192 });
	down[LEFT_MIDDLE_F].speed = 0.25f;
	//down[MIDDLE_F].PushBack({ 1229, 20, 81, 135 });
	down[MIDDLE_F].PushBack({ 432, 768, 144, 192 });
	down[MIDDLE_F].PushBack({ 432, 960, 144, 192 });
	down[MIDDLE_F].speed = 0.25f;
    //down[RIGHT_MIDDLE_F].PushBack({ 1331, 20, 81, 135 });
	down[RIGHT_MIDDLE_F].PushBack({ 576, 768, 144, 192 });
	down[RIGHT_MIDDLE_F].PushBack({ 576, 960, 144, 192 });
	down[RIGHT_MIDDLE_F].speed = 0.25f;
	//down[RIGHT_F].PushBack({ 1421, 20, 90, 135 });
	down[RIGHT_F].PushBack({ 720, 768, 144, 192 });
	down[RIGHT_F].PushBack({ 720, 960, 144, 192 });
	down[RIGHT_F].speed = 0.25f;
	//down[FAR_RIGHT_F].PushBack({ 1511, 20, 96, 135 });
	down[FAR_RIGHT_F].PushBack({ 864, 768, 144, 192 });
	down[FAR_RIGHT_F].PushBack({ 864, 960, 144, 192 });
	down[FAR_RIGHT_F].speed = 0.25f;

	walk_right.PushBack({ 0, 1152, 144, 192 });
	walk_right.PushBack({ 144, 1152, 144, 192 });
	walk_right.PushBack({ 288, 1152, 144, 192 });
	walk_right.speed = 0.2f;

	walk_left.PushBack({ 864, 1152, 144, 192 });
	walk_left.PushBack({ 720, 1152, 144, 192 });
	walk_left.PushBack({ 576, 1152, 144, 192 });
	walk_left.speed = 0.2f;

	roll_right.PushBack({ 937, 509, 96, 159 });
	roll_right.PushBack({ 1035, 482, 114, 186 });
	roll_right.PushBack({ 1070, 572, 192, 96 });
	roll_right.PushBack({ 1362, 512, 96, 156 });
	roll_right.PushBack({ 939, 740, 129, 81 });
	roll_right.PushBack({ 1072, 725, 129, 81 });
	roll_right.PushBack({ 1218, 728, 144, 96 });
	roll_right.PushBack({ 1362, 677, 96, 144 });
	roll_right.speed = 0.2f;

	dead.PushBack({ 0, 2112, 192, 192 });
	dead.PushBack({ 192, 2112, 192, 192 });
	dead.PushBack({ 384, 2112, 192, 192 });
	dead.PushBack({ 576, 2112, 192, 192 });
	dead.loop = true;
	dead.speed = 0.1;
}

ModulePlayer::~ModulePlayer()
{}

// Load assets
bool ModulePlayer::Start()
{
	LOG("Loading player");

	player = App->textures->Load("sprites/p1_sprites-rearranged.png");
	crosstexture = App->textures->Load("sprites/aims.png"); 
	shoot = App->audio->LoadSFX("sound/soundfx/shoot.wav");
	cross_collider = App->collision->AddCollider({ SCREEN_WIDTH/2, SCREEN_HEIGHT, 69, 63 }, COLLIDER_PLAYER_SHOT);
	player_collider = App->collision->AddCollider({ (SCREEN_WIDTH - 87) / 2, SCREEN_HEIGHT / 2 + 117, 80, 175 }, COLLIDER_PLAYER); // temporary resolution; 
	ground_collider = App->collision->AddCollider({ 0, SCREEN_HEIGHT - 50, SCREEN_WIDTH, 50 }, COLLIDER_PLAYER_SHOT);
	

	return true;
}

// Unload assets
bool ModulePlayer::CleanUp()
{
	LOG("Unloading player");

	App->textures->Unload(player);
	App->textures->Unload(crosstexture);

	App->audio->UnloadSFX(shoot);

	App->collision->EraseCollider(cross_collider);
	App->collision->EraseCollider(player_collider);


	return true;
}

// Update: draw background
update_status ModulePlayer::Update()
{
	int speed = 4;
	int xcorrection = 0;
	int ycorrection = 0; // x and y correction for temporary sprite changes
	bool firing = false;
	position.y = SCREEN_HEIGHT / 2 + 117;
	int screen_portion = portion_calculate();
	cross_collider->SetPos(SCREEN_WIDTH / 2, SCREEN_HEIGHT);
	player_collider->SetPos(position.x, position.y);

	if (!hit)
	{
		if (App->input->keyboard[SDL_SCANCODE_LCTRL] == KEY_STATE::KEY_REPEAT)
		{
			cross_collider->SetPos(cposition.x, cposition.y);
			screen_portion += 7;
			App->audio->PlaySFX(shoot);
			firing = true;
			if (screen_portion <= MIDDLE_F)
				xcorrection += idle[screen_portion - 7].frames[0].w - idle[screen_portion].frames[0].w;
			ycorrection += idle[screen_portion - 7].frames[0].h - idle[screen_portion].frames[0].h;
		}

		current_animation = &idle[screen_portion];

		if (App->input->keyboard[SDL_SCANCODE_S] == KEY_STATE::KEY_REPEAT)
		{
			if (cposition.y < position.y + 15)
				cposition.y += speed * 2;

			if (App->input->keyboard[SDL_SCANCODE_W] != KEY_STATE::KEY_REPEAT)
			{
				current_animation = &down[screen_portion];
				ycorrection += 25;
			}

		}

		if (App->input->keyboard[SDL_SCANCODE_W] == KEY_STATE::KEY_REPEAT)
		{
			if (cposition.y > -35)
				cposition.y -= speed * 2;

		}

		if (App->input->keyboard[SDL_SCANCODE_A] == KEY_STATE::KEY_REPEAT)
		{
			if (position.x > 0 && !firing)
				position.x -= speed;
			if (cposition.x > -35) //middle of the cross
				cposition.x -= speed * 2;

			if (App->input->keyboard[SDL_SCANCODE_D] != KEY_STATE::KEY_REPEAT && !firing)
				current_animation = &walk_left;
		}

		if (App->input->keyboard[SDL_SCANCODE_D] == KEY_STATE::KEY_REPEAT)
		{
			if (position.x < SCREEN_WIDTH - 87 && !firing)
				position.x += speed;
			if (cposition.x < SCREEN_WIDTH - 35) //the middle of the cross
				cposition.x += speed * 2;

			if (App->input->keyboard[SDL_SCANCODE_A] != KEY_STATE::KEY_REPEAT && !firing)
				current_animation = &walk_right;
		}
	}
	else
	{
		current_animation = &dead;
		if (dead.Finished())
		{
			App->useri->hitpoints -= 1;
			hit = false;
			dead.Reset();
		}
	}

	// The rolling animation needs to be done inside a separate function, thus avoiding the player from moving and receiving damage

	// Draw everything --------------------------------------
	
	App->render->Blit(crosstexture, cposition.x, cposition.y, &(cross.GetCurrentFrame()));
	if (firing)
		App->render->Blit(crosstexture, cposition.x, cposition.y, &(fcross.GetCurrentFrame()));
	App->render->Blit(player, position.x + xcorrection, position.y + ycorrection, &(current_animation->GetCurrentFrame()));

	return UPDATE_CONTINUE;
}