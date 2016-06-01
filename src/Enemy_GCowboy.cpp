#include "Application.h"
#include "Enemy_GCowboy.h"
#include "Path.h"
#include "ModuleCollision.h"
#include "p2Point.h"
#include "ModuleParticles.h"
#include "ModuleItems.h"

#include <stdlib.h> 
#include <time.h>  
#include "SDL/include/SDL.h"
#pragma comment( lib, "SDL_mixer/libx86/SDL2_mixer.lib" )


GCowboy::GCowboy(int x, int y) : Enemy(x, y)
{

	walk.PushBack({ 864, 1968, 96, 144 });
	walk.PushBack({ 960, 1968, 96, 144 });
	walk.PushBack({ 1056, 1968, 96, 144 });
	walk.PushBack({ 1152, 1968, 96, 144 });
	walk.PushBack({ 1248, 1968, 96, 144 });
	walk.PushBack({ 1344, 1968, 96, 144 });
	walk.speed = 0.2f;


	shoot.PushBack({ 1440, 1968, 96, 144 });
	shoot.PushBack({ 1536, 1968, 96, 144 });
	shoot.PushBack({ 1440, 1968, 96, 144 });
	shoot.speed = 0.2f;
	shoot.loop = false;

	dead.PushBack({ 1728-96, 1968, 96, 144 });
	dead.PushBack({ 1824-96, 1968, 96, 144 });
	dead.PushBack({ 1920-96, 1968, 96, 144 });
	dead.speed = 0.1f;
	dead.loop = false;

	animation = &walk;

	collider = App->collision->AddCollider({ 0, 0, 70, 70 }, COLLIDER_TYPE::COLLIDER_ENEMY, (Module*)App->enemies);

	position.x = SCREEN_WIDTH;
	i_pos.y = position.y;

	srand(time(NULL));

}

void GCowboy::Move()
{
	switch (state)
	{
	case ST_REGULAR:
		current_time = SDL_GetTicks();

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
			switch (rand() % 4)
			{
			case 0:
				App->particles->AddParticle(App->particles->shoot_player, position.x + shoot.frames[1].w / 2, position.y + shoot.frames[1].h / 2, COLLIDER_ENEMY_SHOT);
				break;
			case 1:
				App->particles->AddParticle(App->particles->shoot, position.x + shoot.frames[1].w / 2, position.y + shoot.frames[1].h / 2, COLLIDER_ENEMY_SHOT);
				break;
			case 2:
				App->particles->AddParticle(App->particles->shoot_player, position.x + shoot.frames[1].w / 2, position.y + shoot.frames[1].h / 2, COLLIDER_ENEMY_SHOT);
				break;
			case 3:
				break;
			}
			has_shot = true;
		}
		break;

	case ST_DYING:
		animation = &dead;
		if (dead.Finished())
		{
			switch (rand() % 5)
			{
			case 1: App->items->SpawnBonus(position.x, position.y, SCORE_5000);
				break;
			}
			isDead = true;
		}
		break;
	}

	
}