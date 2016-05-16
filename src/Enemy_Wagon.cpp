#include "Application.h"
#include "Enemy_Wagon.h"
#include "Path.h"
#include "ModuleCollision.h"
#include "p2Point.h"
#include "ModuleParticles.h"

#include <stdlib.h> 
#include <time.h>  
#include "SDL/include/SDL.h"
#pragma comment( lib, "SDL_mixer/libx86/SDL2_mixer.lib" )


Wagon::Wagon(int x, int y) : Enemy(x, y)
{
	/*
	walk.PushBack({ 153, 442, 45, 96 });
	walk.PushBack({ 215, 439, 66, 96 });
	walk.PushBack({ 289, 443, 80, 93 });
	walk.PushBack({ 378, 441, 43, 96 });
	walk.PushBack({ 433, 442, 63, 96 });
	walk.PushBack({ 505, 443, 80, 94 });
	walk.speed = 0.2f;


	shoot.PushBack({ 594, 415, 82, 120 });
	shoot.PushBack({ 684, 413, 68, 120 });
	shoot.PushBack({ 594, 415, 82, 120 });
	shoot.speed = 0.2f;
	shoot.loop = false;

	dead.PushBack({ 1132, 635, 105, 165 });
	dead.PushBack({ 1276, 677, 104, 128 });
	dead.PushBack({ 1411, 689, 128, 100 });
	dead.PushBack({ 23, 910, 128, 28 });
	dead.speed = 0.1f;

	animation = &walk;

	collider = App->collision->AddCollider({ 0, 0, 70, 70 }, COLLIDER_TYPE::COLLIDER_ENEMY, (Module*)App->enemies);


	position.x = SCREEN_WIDTH;
	i_pos.y = position.y;

	srand(time(NULL));
	*/
}

void Wagon::Move()
{
	/*current_time = SDL_GetTicks();

	if (current_time >= shoot_end)
	{
		position.x -= 2;
		if (has_shot)
		{
			position.y = i_pos.y;
			animation = &walk;
		}
	}
	if (position.x <= SCREEN_WIDTH / 2 - shoot.frames[1].w / 2 && !has_shot)
	{
		shoot_end = current_time + 1000;
		position.y -= 10;
		animation = &shoot;
		switch (rand() % 3)
		{
		case 0:
			App->particles->AddParticle(App->particles->shoot_left, position.x + shoot.frames[1].w / 2, position.y + shoot.frames[1].h / 2, COLLIDER_ENEMY_SHOT);
			break;
		case 1:
			App->particles->AddParticle(App->particles->shoot, position.x + shoot.frames[1].w / 2, position.y + shoot.frames[1].h / 2, COLLIDER_ENEMY_SHOT);
			break;
		case 2:
			App->particles->AddParticle(App->particles->shoot_right, position.x + shoot.frames[1].w / 2, position.y + shoot.frames[1].h / 2, COLLIDER_ENEMY_SHOT);
			break;
		}
		has_shot = true;
	}*/

}