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
	walk.PushBack({ 0, 432, 144, 48 });
	walk.PushBack({ 144, 432, 144, 48 });
	walk.PushBack({ 288, 432, 144, 48 });
	walk.PushBack({ 432, 432, 144, 48 });
	walk.speed = 0.2f;

	
	//cowboy up the wagon
	shoot.PushBack({ 1440, 2064,96, 96 });
	shoot.PushBack({ 1536, 2016, 96, 144 });
	shoot.PushBack({ 1440, 2064, 96, 96} );
	shoot.speed = 0.2f;
	shoot.loop = false;
	//----

	//dead cowboy wagon animation
	dead.PushBack({ 1920, 1968, 96, 144 });
	dead.speed = 0.1f;

	
	
	
	animation = &walk;

	collider = App->collision->AddCollider({ 0, 0, 70, 70 }, COLLIDER_TYPE::COLLIDER_ENEMY, (Module*)App->enemies);


	position.x = SCREEN_WIDTH;
	i_pos.y = position.y;

	srand(time(NULL));
	
}

void Wagon::Move()
{
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

}