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
	shoot.PushBack({ 1296, 2976, 96, 144});
	shoot.PushBack({ 1392, 2976, 96, 144});
	shoot.PushBack({ 1488, 2976, 96, 144});
	shoot.speed = 0.2f;
	shoot.loop = false;
	
	//--------------------------

	//indian regular here
	regular.PushBack({ 1488, 2976, 96, 144 });
	regular.PushBack({ 1488, 2986, 96, 144 });
	regular.speed = 0.05f;

	//------------------

	//horse dying here
	dead.PushBack({ 0, 3312, 144, 144 });
	dead.PushBack({ 144, 3312, 144, 144 });
	dead.PushBack({ 288, 3312, 144, 144 });
	dead.PushBack({ 432, 3312, 144, 144 });
	dead.PushBack({ 576, 3312, 144, 144 });
	dead.speed = 0.2f;

	//Horse neigh
	neigh.PushBack({ 960, 3148, 144, 192 });
	neigh.PushBack({ 816, 3148, 144, 192 });
	neigh.PushBack({ 672, 3148, 144, 192 });
	neigh.PushBack({ 960, 3148, 144, 192 });
	neigh.PushBack({ 816, 3148, 144, 192 });
	neigh.PushBack({ 672, 3148, 144, 192 });
	neigh.speed = 0.2f;
	neigh.loop = false;

	//---------------------------

	//dead of indian here

	dead_indian.PushBack({ 384, 624, 96, 144});
	dead_indian.speed = 0.1f;
	dead_indian.loop = false;
	//------------------------------
	
	animation = &walk;
	animation_indian = &regular;

	collider = App->collision->AddCollider({48, 0, 48, 48 }, COLLIDER_TYPE::COLLIDER_ENEMY, (Module*)App->enemies);
	//sfx = App->audio->LoadSFX("sound/soundfx/horse.wav");

	position.x = 0;
	i_pos.y = position.y;

	srand(time(NULL));

}

void Horse::Move()
{
	current_time = SDL_GetTicks();
	
	switch (state)
	{
	case ST_REGULAR:

		if (current_time >= shoot_end)
		{
			if (has_shot)
			{
				position.y = i_pos.y;
				animation = &walk;
				animation_indian = &regular;
			}
		}
		if (position.x >= SCREEN_WIDTH / 3 - shoot.frames[1].w / 2 && !has_shot)
		{
			shoot_end = current_time + 1000;
			animation = &walk;
			animation_indian = &shoot;
			App->particles->AddParticle(App->particles->firearrow, position.x + shoot.frames[1].w / 2, position.y + shoot.frames[1].h / 2, COLLIDER_ENEMY_SHOT);
			has_shot = true;
		}
		position.x += 4;
		break;
	case ST_DYING:
		
		if (!neigh.Finished())
			animation = &neigh;
		else
		{
			animation = &dead;
			position.x += 8;
		}
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
		App->render->Blit(sprites, position.x + TILE, position.y-10, &(animation_indian->GetCurrentFrame()),0.75);
		break;
	case ST_DYING:
		animation->GetCurrentFrame();
		if (collider != nullptr)
		{
			collider->SetPos(position.x, position.y);
			collider->SetSize(animation->ConsultCurrentFrame().w, animation->ConsultCurrentFrame().h);
		}

		App->render->Blit(sprites, position.x, position.y, &(animation->ConsultCurrentFrame()));
		if (!dead_indian.Finished())
			App->render->Blit(sprites, position.x + TILE, position.y-TILE, &(dead_indian.GetCurrentFrame()), 0.75);
	}

}