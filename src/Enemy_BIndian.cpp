#include "Application.h"
#include "Enemy_BIndian.h"
#include "Path.h"
#include "ModuleCollision.h"
#include "p2Point.h"
#include "ModuleParticles.h"

#include "SDL/include/SDL.h"
#pragma comment( lib, "SDL_mixer/libx86/SDL2_mixer.lib" )


BIndian::BIndian(int x, int y) : Enemy(x, y)
{
	walk.PushBack({ 270, 441, 47, 90});
	walk.PushBack({ 333, 438, 66, 93});
	walk.speed = 0.2f;

	shoot.PushBack({ 413, 435, 48, 96});
	shoot.PushBack({ 478, 438, 48, 93});
	shoot.speed = 0.1f;
	shoot.loop = false;

	dead.PushBack({ 548, 435, 84, 96});
	dead.PushBack({ 652, 456, 48, 75});
	dead.PushBack({ 716, 474, 75, 57});
	dead.PushBack({ 803, 516, 75, 15});
	dead.speed = 0.1f;
	


	animation = &walk;
	collider = App->collision->AddCollider({ 0, 0, 50, 90 }, COLLIDER_TYPE::COLLIDER_ENEMY, (Module*)App->enemies);

	

	position.x = SCREEN_WIDTH;
	i_pos.y = position.y;

}

void BIndian::Move()
{
	current_time = SDL_GetTicks();

	if (current_time >= shoot_end)
	{
		position.x += 2;
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
		App->particles->AddParticle(App->particles->shoot, position.x, position.y);
		has_shot = true;
	}

}