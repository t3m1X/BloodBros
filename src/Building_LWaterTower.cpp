#include "Application.h"
#include "Building_LWaterTower.h"
#include "Path.h"
#include "ModuleCollision.h"
#include "p2Point.h"
#include "ModuleParticles.h"
#include "ModuleRender.h"

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


	collider = App->collision->AddCollider({ x, y, 200, 448 }, COLLIDER_TYPE::COLLIDER_ENEMY, (Module*)App->enemies);

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
			xcorrection -= 5;
			next_call = this_call + 50;
		}
		position.y += 1;
		last_anim.h -= 1;
		App->render->Blit(sprites, position.x + xcorrection, position.y, &last_anim);
		if (last_anim.h <= 10)
			isDead = true;
		break;
	}
}


void LWaterTower::Collision()
{
	this_call = SDL_GetTicks();

	if (this_call > next_call)
	{
		next_call = this_call + 500;
		if (building.Finished())
		{
			App->particles->AddParticle(App->particles->dust, position.x+240-336 , position.y+448-60 );
			state = ST_DYING;
			next_call = 0;
		}
		
		else
			building.GetCurrentFrame();
	}
}