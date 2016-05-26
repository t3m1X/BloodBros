#include "Application.h"
#include "Can.h"
#include "Path.h"
#include "ModuleCollision.h"
#include "p2Point.h"
#include "ModuleParticles.h"
#include "ModuleRender.h"

#include "SDL/include/SDL.h"
#pragma comment( lib, "SDL_mixer/libx86/SDL2_mixer.lib" )

Can::Can(int x, int y) : Enemy(x, y)
{
	still.PushBack({ 1680, 0, 48, 48 });
	still.speed = 1.0f;

	flying.PushBack({ 1728, 0, 48, 48 });
	flying.PushBack({ 1776, 0, 48, 48 });
	flying.PushBack({ 1824, 0, 48, 48 });
	flying.PushBack({ 1872, 0, 48, 48 });
	flying.PushBack({ 1920, 0, 48, 48 });
	flying.PushBack({ 1968, 0, 48, 48 });
	flying.PushBack({ 2016, 0, 48, 48 });
	still.PushBack({ 1680, 0, 48, 48 });
	still.speed = 0.1f; 


	animation = &still;


	collider = App->collision->AddCollider({ x, y, 48, 48 }, COLLIDER_TYPE::COLLIDER_ENEMY, (Module*)App->enemies);

}
void Can::Collision()
{
	animation = &flying;
	fly = true;
}

void Can::Move()
{ 
	if (fly == true)
	{
		--position.y;
		++position.x;
	}



}