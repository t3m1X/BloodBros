#include "Application.h"
#include "Enemy_V_Left3.h"
#include "Path.h"
#include "ModuleCollision.h"
#include "p2Point.h"
#include "ModuleParticles.h"
#include "ModuleUserI.h"

#include <stdlib.h> 
#include <time.h>  
#include "SDL/include/SDL.h"
#pragma comment( lib, "SDL_mixer/libx86/SDL2_mixer.lib" )


Enemy_V_Left3::Enemy_V_Left3(int x, int y) : Enemy(x, y)
{


	appear.PushBack({ 1200, 2352, 48, 48 });
	appear.PushBack({ 864, 2304, 48, 48 });
	appear.PushBack({ 912, 2304, 48, 48 });
	appear.PushBack({ 960, 2304, 48, 48 });
	appear.PushBack({ 1008, 2304, 48, 48 });
	appear.PushBack({ 1008, 2304, 48, 48 });
	appear.PushBack({ 1008, 2304, 48, 48 });
	appear.PushBack({ 1008, 2304, 48, 48 });
	appear.loop = false;
	appear.speed = 0.2f;



	walk.PushBack({ 864 + 768, 2352 , 48, 48 });
	walk.PushBack({ 912 + 768, 2352, 48, 48 });
	walk.PushBack({ 960 + 768, 2352, 48, 48 });
	walk.speed = 0.2f;

	dead.PushBack({ 1776, 2352, 48, 48 });
	dead.PushBack({ 1824, 2352, 48, 48 });
	dead.PushBack({ 1872, 2352, 48, 48 });
	dead.PushBack({ 1920, 2352, 48, 48 });
	dead.speed = 0.1f;
	dead.loop = false;

	animation = &appear;

	collider = App->collision->AddCollider({ 0, 0, 48, 48 }, COLLIDER_TYPE::COLLIDER_ENEMY, (Module*)App->enemies);

}

void Enemy_V_Left3::Move()
{
	switch (state)
	{
	case ST_REGULAR:
		if (appear.Finished())
		{
			animation = &walk;
			position.x -= 4;
		}
		break;

	case ST_DYING:
		animation = &dead;
		if (dead.Finished())
		{
			isDead = true;
			App->useri->killcount += 1;
			App->useri->score += 100;
		}
		break;
	}
}