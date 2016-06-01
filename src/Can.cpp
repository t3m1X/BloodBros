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
	flying.PushBack({ 1680, 0, 48, 48 });
	flying.speed = 0.2f; 


	animation = &still;

	y_pos = position.y; //SCREEN_HEIGHT - 275 + 96


	collider = App->collision->AddCollider({ x, y, 48, 48 }, COLLIDER_TYPE::COLLIDER_ENEMY, (Module*)App->enemies);

}
void Can::Collision()
{
		animation = &flying;
		fly = true;
}

void Can::Move()
{ 
	if (fly)
	{
		if (right_move)
		{
			if (mid_fly != true)
			{
				position.y -= 3;
				--position.x;
			}
			if (position.y < y_pos - 144)
			{
				mid_fly = true;
			}
			if (mid_fly)
			{
				position.y += 3;
				--position.x;
			}
			if (position.y == y_pos)
			{
				fly = false;
				mid_fly = false;
				right_move = false;
			}
		}
		else
		{
			if (mid_fly != true)
			{
				position.y -= 3;
				++position.x;
			}
			if (position.y < y_pos - 144)
			{
				mid_fly = true;
			}
			if (mid_fly)
			{
				position.y += 3;
				++position.x;
			}
			if (position.y == y_pos)
			{
				fly = false;
				mid_fly = false;
				right_move = true;
			}
		}
	}
	
	
	else
	{
		animation = &still;
	}

}