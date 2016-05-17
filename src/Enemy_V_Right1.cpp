#include "Application.h"
#include "Enemy_V_Right1.h"
#include "Path.h"
#include "ModuleCollision.h"
#include "p2Point.h"
#include "ModuleParticles.h"

#include <stdlib.h> 
#include <time.h>  
#include "SDL/include/SDL.h"
#pragma comment( lib, "SDL_mixer/libx86/SDL2_mixer.lib" )


Enemy_V_Right1::Enemy_V_Right1(int x, int y) : Enemy(x, y)
{

	appear.PushBack({ 1248, 2256, 48, 96 });
	appear.PushBack({ 1296, 2256, 48, 96 });
	appear.PushBack({ 1344, 2256, 48, 96 });
	appear.PushBack({ 1392, 2256, 48, 96 });
	appear.PushBack({ 1392, 2256, 48, 96 });
	appear.PushBack({ 1392, 2256, 48, 96 });
	appear.PushBack({ 1392, 2256, 48, 96 });
	appear.loop = false;
	appear.speed = 0.2f;

	walk.PushBack({ 864, 2592, 96, 96 });
	walk.PushBack({ 960, 2592, 96, 96 });
	walk.PushBack({ 1056, 2592, 96, 96 });
	walk.PushBack({ 1152, 2592, 96, 96 });
	walk.PushBack({ 1248, 2592, 96, 96 });
	walk.PushBack({ 1344, 2592, 96, 96 });
	walk.speed = 0.2f;

	dead.PushBack({ 1344, 2496, 96, 96 });
	dead.PushBack({ 1440, 2496, 96, 96 });
	dead.PushBack({ 1536, 2496, 96, 96 });
	dead.PushBack({ 1632, 2496, 96, 96 });
	dead.PushBack({ 1632, 2496, 96, 96 });
	dead.PushBack({ 1632, 2496, 96, 96 });
	dead.speed = 0.1f;

	animation = &appear;

	collider = App->collision->AddCollider({ 0, 48, 48, 48 }, COLLIDER_TYPE::COLLIDER_ENEMY, (Module*)App->enemies);

}

void Enemy_V_Right1::Move()
{
	if (appear.Finished())
	{
		animation = &walk;
		position.x += 3;
	}
}