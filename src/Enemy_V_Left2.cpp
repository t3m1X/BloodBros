#include "Application.h"
#include "Enemy_V_Left2.h"
#include "Path.h"
#include "ModuleCollision.h"
#include "p2Point.h"
#include "ModuleParticles.h"

#include <stdlib.h> 
#include <time.h>  
#include "SDL/include/SDL.h"
#pragma comment( lib, "SDL_mixer/libx86/SDL2_mixer.lib" )


Enemy_V_Left2::Enemy_V_Left2(int x, int y) : Enemy(x, y)
{
	appear.PushBack({ 1680, 3000, 48, 96 });
	appear.PushBack({ 1680, 3000, 48, 96 });		//Empty

	appear.PushBack({ 1344, 2400, 48, 96 });
	appear.PushBack({ 1104, 2256, 48, 96 });
	appear.PushBack({ 1152, 2256, 48, 96 });
	appear.PushBack({ 1200, 2256, 48, 96 });
	appear.PushBack({ 1200, 2256, 48, 96 });
	appear.PushBack({ 1200, 2256, 48, 96 });
	appear.PushBack({ 1200, 2256, 48, 96 });

	appear.loop = false;
	appear.speed = 0.2f;

	walk.PushBack({ 864, 2396, 48, 96 });
	walk.PushBack({ 912, 2396, 48, 96 });
	walk.PushBack({ 960, 2396, 48, 96 });
	walk.PushBack({ 1008, 2396, 48, 96 });
	walk.PushBack({ 1056, 2396, 48, 96 });
	walk.speed = 0.2f;

	dead.PushBack({ 1344, 2396, 48, 96 });
	dead.PushBack({ 1296, 2396, 48, 96 });
	dead.PushBack({ 1248, 2396, 48, 96 });
	dead.PushBack({ 1200, 2396, 48, 96 });
	dead.speed = 0.1f;

	animation = &appear;

	collider = App->collision->AddCollider({ 0, 48, 20, 20 }, COLLIDER_TYPE::COLLIDER_ENEMY, (Module*)App->enemies);

}

void Enemy_V_Left2::Move()
{
	switch (state)
	{
	case ST_REGULAR:
		if (appear.Finished())
		{
			animation = &walk;
			position.x -= 3;
		}
		break;

	case ST_DYING:
		animation = &dead;
		if (dead.Finished())
			isDead = true;
		break;
	}
}