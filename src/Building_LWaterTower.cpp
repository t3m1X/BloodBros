#include "Application.h"
#include "Building_LWaterTower.h"
#include "Path.h"
#include "ModuleCollision.h"
#include "p2Point.h"
#include "ModuleParticles.h"
#include "ModuleRender.h"
#include "ModuleUserI.h"
#include "ModuleScene.h"

#include "SDL/include/SDL.h"
#pragma comment( lib, "SDL_mixer/libx86/SDL2_mixer.lib" )

LWaterTower::LWaterTower(int x, int y) : Enemy(x, y)
{
	building.PushBack({ 1152, 0, 240, 480 });
	building.PushBack({ 1152, 960, 240, 480 });
	building.PushBack({ 1152, 1440, 240, 480 });
	building.speed = 1.0f;
	building.loop = false;
	last_anim.x = 1152;
	last_anim.y = 1440;
	last_anim.w = 240;
	last_anim.h = 480;

	smoke.PushBack({ 1680, 1540, 336, 144 });
	smoke.PushBack({ 2016, 1540, 336, 144 });
	smoke.speed = 0.3f;

	smoke_end.PushBack({ 1680, 1680, 336, 144 });
	smoke_end.PushBack({ 2016, 1680, 336, 144 });
	smoke_end.PushBack({ 1680, 1825, 336, 144 });
	smoke_end.speed = 0.3f;

	initialy = y;


	collider = App->collision->AddCollider({ x, y, 150, 420 }, COLLIDER_TYPE::COLLIDER_ENEMY, (Module*)App->enemies);

}


void LWaterTower::Draw(SDL_Texture* sprites)
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
			xcorrection -= 15;
			next_call = this_call + 50;
		}
		
		if (last_anim.h > 0)
		{
			position.y += 1;
			last_anim.h -= 1;
			App->render->Blit(sprites, position.x + xcorrection, position.y, &last_anim);
			App->render->Blit(sprites, position.x + 240 + 20 - 336, initialy + 480 - 95, &(smoke.GetCurrentFrame()));
		}
		if (last_anim.h <= 48)
		{
			last_anim.h = 0;
			App->render->Blit(sprites, position.x + 240 + 20 - 336, initialy + 480 - 95, &(smoke_end.GetCurrentFrame()));
			if (smoke_end.Finished())
				isDead = true;
		}
		break;
	}
}


void LWaterTower::Collision()
{
	if (!App->scene->toppipe && !App->scene->toppipe2)
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
}