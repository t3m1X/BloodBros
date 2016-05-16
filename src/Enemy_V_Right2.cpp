#include "Application.h"
#include "Enemy_V_Right2.h"
#include "Path.h"
#include "ModuleCollision.h"
#include "p2Point.h"
#include "ModuleParticles.h"

#include <stdlib.h> 
#include <time.h>  
#include "SDL/include/SDL.h"
#pragma comment( lib, "SDL_mixer/libx86/SDL2_mixer.lib" )


Enemy_V_Right2::Enemy_V_Right2(int x, int y) : Enemy(x, y)
{

	appear.PushBack({ 1026, 2256, 48, 96 });
	appear.PushBack({ 1074, 2256, 48, 96 });
	appear.PushBack({ 1122, 2256, 48, 96 });
	appear.PushBack({ 1170, 2256, 48, 96 });
	appear.loop = false;
	appear.speed = 2.0f;

	walk.PushBack({ 1392, 2396, 48, 96 });
	walk.PushBack({ 1440, 2396, 48, 96 });
	walk.PushBack({ 1448, 2396, 48, 96 });
	walk.PushBack({ 1536, 2396, 48, 96 });
	walk.PushBack({ 1584, 2396, 48, 96 });
	walk.speed = 0.2f;

	dead.PushBack({ 1344, 2396, 48, 96 });
	dead.PushBack({ 1296, 2396, 48, 96 });
	dead.PushBack({ 1248, 2396, 48, 96 });
	dead.PushBack({ 1200, 2396, 48, 96 });
	dead.speed = 0.1f;

	animation = &appear;

	collider = App->collision->AddCollider({ 0, 0, 96, 96 }, COLLIDER_TYPE::COLLIDER_ENEMY, (Module*)App->enemies);

}

void Enemy_V_Right2::Move()
{
	if (appear.Finished())
	{
		animation = &walk;
		position.x += 3;
	}
}