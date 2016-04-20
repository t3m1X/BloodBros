#include "Globals.h"
#include "Application.h"
#include "ModuleTextures.h"
#include "ModuleInput.h"
#include "ModuleParticles.h"
#include "ModuleRender.h"
#include "ModulePlayer.h"
#include "ModuleAudio.h"

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

	idle[FAR_LEFT].PushBack({ 50, 21, 87, 180 });
	idle[LEFT].PushBack({ 146, 20, 87, 180 });
	idle[LEFT_MIDDLE].PushBack({ 248, 20, 87, 180 });
	idle[MIDDLE].PushBack({ 359, 20, 87, 183 });
	idle[RIGHT_MIDDLE].PushBack({ 455, 20, 87, 183 });
	idle[RIGHT].PushBack({ 542, 20, 87, 183 });
	idle[FAR_RIGHT].PushBack({ 629, 20, 87, 183 });

	idle[FAR_LEFT_F].PushBack({ 6, 216, 129, 180 }); 
	idle[FAR_LEFT_F].PushBack({ 6, 411, 129, 180 });
	idle[FAR_LEFT_F].speed = 0.25f;
	idle[LEFT_F].PushBack({ 138, 215, 114, 181 });
	idle[LEFT_F].PushBack({ 138, 410, 114, 181 });
	idle[LEFT_F].speed = 0.25f;
	idle[LEFT_MIDDLE_F].PushBack({ 246, 203, 87, 192 });
	idle[LEFT_MIDDLE_F].PushBack({ 250, 398, 87, 192 });
	idle[LEFT_MIDDLE_F].speed = 0.3f;
	idle[MIDDLE_F].PushBack({ 357, 203, 87, 195 });
	idle[MIDDLE_F].PushBack({ 361, 398, 87, 195 });
	idle[MIDDLE_F].speed = 0.3f;
	idle[RIGHT_MIDDLE_F].PushBack({ 453, 203, 87, 195 });
	idle[RIGHT_MIDDLE_F].PushBack({ 457, 398, 87, 195 });
	idle[RIGHT_MIDDLE_F].speed = 0.3f;
	idle[RIGHT_F].PushBack({ 540, 215, 102, 183 });
	idle[RIGHT_F].PushBack({ 544, 410, 102, 183 });
	idle[RIGHT_F].speed = 0.3f;
	idle[FAR_RIGHT_F].PushBack({ 651, 215, 135, 183 });
	idle[FAR_RIGHT_F].PushBack({ 655, 410, 135, 183 });
	idle[FAR_RIGHT_F].speed = 0.3f;
	

	down[FAR_LEFT].PushBack({ 935, 20, 96, 135 });
	down[LEFT].PushBack({ 1034, 20, 84, 135 });
	down[LEFT_MIDDLE].PushBack({ 1136, 20, 84, 135 });
	down[MIDDLE].PushBack({ 1229, 20, 81, 135 });
	down[RIGHT_MIDDLE].PushBack({ 1331, 20, 81, 135 });
	down[RIGHT].PushBack({ 1421, 20, 90, 135 });
	down[FAR_RIGHT].PushBack({ 1511, 20, 96, 135 });

	down[FAR_LEFT_F].PushBack({ 935, 20, 96, 135 });
	down[LEFT_F].PushBack({ 1034, 20, 84, 135 });
	down[LEFT_MIDDLE_F].PushBack({ 1136, 20, 84, 135 });
	down[MIDDLE_F].PushBack({ 1229, 20, 81, 135 });
	down[RIGHT_MIDDLE_F].PushBack({ 1331, 20, 81, 135 });
	down[RIGHT_F].PushBack({ 1421, 20, 90, 135 });
	down[FAR_RIGHT_F].PushBack({ 1511, 20, 96, 135 });

	walk_right.PushBack({ 24, 602, 102, 180 });
	walk_right.PushBack({ 128, 602, 96, 177 });
	walk_right.PushBack({ 233, 600, 120, 180 });
	walk_right.speed = 0.2f;

	walk_left.PushBack({ 612, 600, 102, 180 });
	walk_left.PushBack({ 514, 602, 96, 177 });
	walk_left.PushBack({ 385, 600, 120, 180 });
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
}

ModulePlayer::~ModulePlayer()
{}

// Load assets
bool ModulePlayer::Start()
{
	LOG("Loading player");

	player = App->textures->Load("sprites/p1_sprites.png");
	crosstexture = App->textures->Load("sprites/aims.png"); 
	shoot = App->audio->LoadSFX("sound/soundfx/shoot.wav");
	

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
	int xcorrection = 0;
	int ycorrection = 0; // x and y correction for temporary sprite changes
	bool firing = false;
	position.y = SCREEN_HEIGHT / 2 + 117;
	int screen_portion = portion_calculate();

	if (App->input->keyboard[SDL_SCANCODE_LCTRL] == KEY_STATE::KEY_REPEAT)
	{
		screen_portion += 7;
		App->audio->PlaySFX(shoot);
		firing = true;
		if (screen_portion <= LEFT_F)
			xcorrection += 87 - idle[screen_portion].frames[0].w;
		else if (screen_portion < RIGHT_F)
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
			if (App->input->keyboard[SDL_SCANCODE_A] != KEY_STATE::KEY_REPEAT && 
				App->input->keyboard[SDL_SCANCODE_D] != KEY_STATE::KEY_REPEAT)
				ycorrection += 25;
		}

	}

	if (App->input->keyboard[SDL_SCANCODE_W] == KEY_STATE::KEY_REPEAT)
	{
		if (cposition.y > -35)
			cposition.y -= speed * 2;

	}

	if(App->input->keyboard[SDL_SCANCODE_A] == KEY_STATE::KEY_REPEAT)
	{
		if (position.x > 0 && !firing)
			position.x -= speed;
		if (cposition.x > -35) //middle of the cross
			cposition.x -= speed * 2;

		if (App->input->keyboard[SDL_SCANCODE_D] != KEY_STATE::KEY_REPEAT && !firing)
			current_animation = &walk_left;
	}

	if(App->input->keyboard[SDL_SCANCODE_D] == KEY_STATE::KEY_REPEAT)
	{
		if (position.x < SCREEN_WIDTH - 87 && !firing)
			position.x += speed;
		if (cposition.x < SCREEN_WIDTH - 35) //the middle of the cross
			cposition.x += speed * 2;

		if (App->input->keyboard[SDL_SCANCODE_A] != KEY_STATE::KEY_REPEAT && !firing)
			current_animation = &walk_right;
	}

	// The rolling animation needs to be done inside a separate function, thus avoiding the player from moving and receiving damage

	if(App->input->keyboard[SDL_SCANCODE_B] == KEY_STATE::KEY_DOWN)
	{
		App->particles->AddParticle(App->particles->explosion, position.x, position.y + 25);
		App->particles->AddParticle(App->particles->explosion, position.x - 25, position.y, 500);
		App->particles->AddParticle(App->particles->explosion, position.x, position.y - 25, 1000);
		App->particles->AddParticle(App->particles->explosion, position.x + 25, position.y, 1500);
	}

	// Draw everything --------------------------------------
	
	App->render->Blit(crosstexture, cposition.x, cposition.y, &(cross.GetCurrentFrame()));
	App->render->Blit(player, position.x + xcorrection, position.y + ycorrection, &(current_animation->GetCurrentFrame()));

	return UPDATE_CONTINUE;
}