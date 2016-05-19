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
	//wagon passing 
	walk.PushBack({ 0, 3456, 144, 144 });
	walk.PushBack({ 144, 3456, 144, 144 });
	walk.PushBack({ 288, 3456, 144, 144 });
	walk.PushBack({ 432, 3456, 144, 144 });
	walk.speed = 0.2f;

	
	//cowboy up the wagon
	shoot.PushBack({ 567, 3456, 144, 144 });
	shoot.speed = 0.2f;
	shoot.loop = false;
	//----

	//dying cowboy wagon animation
	death.PushBack({ 711, 3456, 144, 144 });
	death.PushBack({ 855, 3456, 144, 144 });
	death.PushBack({ 999, 3456, 144, 144 });
	death.speed = 0.2f;
	death.loop = false;

	dead.PushBack({ 0, 3600, 144, 144 });
	dead.PushBack({ 144, 3600, 144, 144 });
	dead.PushBack({ 288, 3600, 144, 144 });
	dead.PushBack({ 432, 3600, 144, 144 });
	dead.speed = 0.2f;

	
	
	
	animation = &walk;

	collider = App->collision->AddCollider({ 0, 0, 70, 70 }, COLLIDER_TYPE::COLLIDER_ENEMY, (Module*)App->enemies);


	position.x = SCREEN_WIDTH;
	i_pos.y = position.y;

	srand(time(NULL));
	
}

void Wagon::Move()
{
	current_time = SDL_GetTicks();
	if (position.x > SCREEN_WIDTH / 2 - TILE * 3 / 2 && !middle)
	{
		position.x -= 2;
		move_time = current_time + 1000;
		if (position.x <= SCREEN_WIDTH / 2 - TILE * 3 / 2)
		{
			middle = true;
			death.speed = 0.0f;
			dead.speed = 0.0f;
			walk.speed = 0.0f;
		}
	}
	else if (current_time > move_time)
	{
		death.speed = 0.2f;
		dead.speed = 0.2f;
		walk.speed = 0.2f;
		position.x += 2;
	}

	switch (state)
	{
	case ST_REGULAR:
		
		if (middle)
			animation = &walk;

		if (position.x <= SCREEN_WIDTH / 2 - TILE * 3 / 2 + 5 && !has_shot)
		{
			
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
		}
		break;
	case ST_DYING:
		if (!death.Finished())
			animation = &death;
		else
			animation = &dead;
		break;
	}
}