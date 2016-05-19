#include "Application.h"
#include "Building_RWaterTower.h"
#include "Path.h"
#include "ModuleCollision.h"
#include "p2Point.h"
#include "ModuleParticles.h"
#include "ModuleRender.h"
#include "ModuleUserI.h"

#include "SDL/include/SDL.h"
#pragma comment( lib, "SDL_mixer/libx86/SDL2_mixer.lib" )

RWaterTower::RWaterTower(int x, int y) : Enemy(x, y)
{
	building.PushBack({ 1392, 0, 288, 480 });
	building.PushBack({ 1392, 960, 288, 480 });
	building.PushBack({ 1392, 1440, 288, 480 });
	

	building.speed = 1.0f;
	building.loop = false;

	last_anim.x = 1392;
	last_anim.y = 1440;
	last_anim.w = 288;
	last_anim.h = 480;

	smoke.PushBack({ 1680, 1540, 336, 144 });
	smoke.PushBack({ 2016, 1540, 336, 144 });
	smoke.speed = 0.3f;

	smoke_end.PushBack({ 1680, 1680, 336, 144 });
	smoke_end.PushBack({ 2016, 1680, 336, 144 });
	smoke_end.PushBack({ 1680, 1825, 336, 144 });
	smoke_end.speed = 0.3f;

	initialy = y;

	collider = App->collision->AddCollider({ SCREEN_WIDTH-200, y, 200, 420 }, COLLIDER_TYPE::COLLIDER_ENEMY, (Module*)App->enemies);

	position.x = SCREEN_WIDTH-250;
}


void RWaterTower::Draw(SDL_Texture* sprites)
{
	switch (state)
	{
	case ST_REGULAR:
		App->render->Blit(sprites, position.x, position.y, &(building.ConsultCurrentFrame()));
		break;
	case ST_DYING:
		int xcorrection = 0;
		this_call = SDL_GetTicks();
		if (this_call >= next_call)
		{
			xcorrection += 15;
			next_call = this_call + 50;
		}
		position.y += 1;
		last_anim.h -= 1;
		App->render->Blit(sprites, position.x + xcorrection, position.y, &last_anim);
		App->render->Blit(sprites, position.x - 20, initialy + 448 - 70, &(smoke.GetCurrentFrame()));
		if (last_anim.h <= 48)
		{
			last_anim.h = 0;
			App->render->Blit(sprites, position.x - 20, initialy + 448 - 70, &(smoke_end.GetCurrentFrame()));
			if (smoke_end.Finished())
				isDead = true;
		}
		break;
	}
}


void RWaterTower::Collision()
{
	this_call = SDL_GetTicks();

	if (this_call > next_call)
	{
		next_call = this_call + 500;
		if (building.Finished())
		{

			App->collision->EraseCollider(collider);
			collider = nullptr;
			state = ST_DYING;
			App->useri->score += 500;
			App->useri->killcount += 1;
			next_call = 0;
		}

		else
			building.GetCurrentFrame();
	}
}