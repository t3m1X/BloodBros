#include "Application.h"
#include "Enemy_V_Right3.h"
#include "Path.h"
#include "ModuleCollision.h"
#include "p2Point.h"
#include "ModuleParticles.h"

#include <stdlib.h> 
#include <time.h>  
#include "SDL/include/SDL.h"
#pragma comment( lib, "SDL_mixer/libx86/SDL2_mixer.lib" )


Enemy_V_Right3::Enemy_V_Right3(int x, int y) : Enemy(x, y)
{

	appear.PushBack({ 864, 2304, 48, 48 });
	appear.PushBack({ 912, 2304, 48, 48 });
	appear.PushBack({ 960, 2304, 48, 48 });
	appear.PushBack({ 1008, 2304, 48, 48 });
	appear.loop = false;
	appear.speed = 2.0f;


	walk.PushBack({ 1218, 2352, 48, 48 });
	walk.PushBack({ 1266, 2352, 48, 48 });
	walk.PushBack({ 1314, 2352, 48, 48 });
	walk.PushBack({ 1362, 2352, 48, 48 });
	walk.speed = 0.2f;

	dead.PushBack({ 1026, 2352, 48, 48 });
	dead.PushBack({ 1074, 2352, 48, 48 });
	dead.PushBack({ 1122, 2352, 48, 48 });
	dead.PushBack({ 1170, 2352, 48, 48 });;
	dead.speed = 0.1f;

	animation = &appear;

	collider = App->collision->AddCollider({ 0, 0, 96, 96 }, COLLIDER_TYPE::COLLIDER_ENEMY, (Module*)App->enemies);

}

void Enemy_V_Right3::Move()
{
	if (appear.Finished())
	{
		animation = &walk;
		position.x += 3;
	}
}