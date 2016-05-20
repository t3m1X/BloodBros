#include "Application.h"
#include "Enemy_Horse.h"
#include "Path.h"
#include "ModuleCollision.h"
#include "p2Point.h"
#include "ModuleParticles.h"
#include "ModuleAudio.h"
#include "ModuleRender.h"

#include <stdlib.h> 
#include <time.h>  
#include "SDL/include/SDL.h"
#pragma comment( lib, "SDL_mixer/libx86/SDL2_mixer.lib" )


Horse::Horse(int x, int y) : Enemy(x, y)
{
	//horse walking here

	walk.PushBack({ 0, 2976, 144, 144});
	walk.PushBack({ 144, 2976, 144, 144 });
	walk.PushBack({ 288, 2976, 144, 144 });
	walk.PushBack({ 432, 2976, 144, 144 });
	walk.PushBack({ 576, 2976, 144, 144 }); 
	walk.PushBack({ 720, 2976, 144, 144 });
	walk.PushBack({ 864, 2976, 144, 144 });
	walk.PushBack({ 1008, 2976, 144, 144 });
	walk.speed = 0.2f;

	//--------------------


	//indian shooting here
	shoot.PushBack({ 1152, 2928, 48, 96});
	shoot.PushBack({ 1200, 2928, 48, 96});
	shoot.PushBack({ 1244, 2928, 48, 96});
	shoot.speed = 0.2f;
	shoot.loop = false;
	
	//--------------------------

	//horse dying here
	dead.PushBack({ 0, 2976, 144, 144 });
	dead.PushBack({ 144, 2976, 144, 144 });
	dead.PushBack({ 288, 2976, 144, 144 });
	dead.PushBack({ 432, 2976, 144, 144 });
	dead.PushBack({ 576, 2976, 144, 144 });
	dead.PushBack({ 720, 2976, 144, 144 });
	dead.PushBack({ 864, 2976, 144, 144 });
	dead.PushBack({ 1008, 2976, 144, 144 });
	dead.speed = 0.4f;
	dead.loop = false;


	//---------------------------

	//dead of indian here

	dead.PushBack({ 576, 1248, 48, 96});
	dead.speed = 0.1f;
	dead.loop = false;
	//------------------------------
	
	animation = &walk;

	collider = App->collision->AddCollider({48, 0, 48, 48 }, COLLIDER_TYPE::COLLIDER_ENEMY, (Module*)App->enemies);
	//sfx = App->audio->LoadSFX("sound/soundfx/horse.wav");

	position.x = 0;
	i_pos.y = position.y;

	srand(time(NULL));

}

void Horse::Move()
{
	current_time = SDL_GetTicks();
	position.x += 4;
	switch (state)
	{
	case ST_REGULAR:

		if (current_time >= shoot_end)
		{
			if (has_shot)
			{
				position.y = i_pos.y;
				animation = &walk;
			}
		}
		if (position.x >= SCREEN_WIDTH / 3 - shoot.frames[1].w / 2 && !has_shot)
		{
			shoot_end = current_time + 1000;
			animation = &walk;
			App->particles->AddParticle(App->particles->firearrow, position.x + shoot.frames[1].w / 2, position.y + shoot.frames[1].h / 2, COLLIDER_ENEMY_SHOT);
			has_shot = true;
		}
		break;
	case ST_DYING:
		position.x += 4;
		if (!dead.Finished())
			animation = &dead;
		else
			animation = &walk;
		break;
	}

}

void Horse::Draw(SDL_Texture* sprites)
{
	switch (state)
	{
	case ST_REGULAR:
		animation->GetCurrentFrame();
		if (collider != nullptr)
		{
			collider->SetPos(position.x, position.y);
			collider->SetSize(animation->ConsultCurrentFrame().w, animation->ConsultCurrentFrame().h);
		}

		App->render->Blit(sprites, position.x, position.y, &(animation->ConsultCurrentFrame()));
		break;
	case ST_DYING:
		animation->GetCurrentFrame();
		if (collider != nullptr)
		{
			collider->SetPos(position.x, position.y);
			collider->SetSize(animation->ConsultCurrentFrame().w, animation->ConsultCurrentFrame().h);
		}

		App->render->Blit(sprites, position.x, position.y, &(animation->ConsultCurrentFrame()));
	}

}