#include "Application.h"
#include "Enemy_Plane.h"
#include "Path.h"
#include "ModuleCollision.h"
#include "p2Point.h"
#include "ModuleParticles.h"

Plane::Plane(int x) : Enemy(x, 25)
{
	if (x < SCREEN_WIDTH / 2)
		position.x = SCREEN_WIDTH / 4;
	else
		position.x = SCREEN_WIDTH / 4 * 3;


	fly.PushBack({ 53, 2962, 32, 16 });
	fly.PushBack({ 101, 2954, 64, 32 });
	fly.PushBack({ 181, 2937, 128, 56 });
	fly.PushBack({ 329, 2926, 192, 80 });
	fly.PushBack({ 550, 2920, 256, 96 });
	fly.PushBack({ 822, 2914, 319, 123 });
	fly.PushBack({ 25, 3046, 379, 152 });
	fly.PushBack({ 459, 3110, 448, 188 });
	fly.speed = 0.045f;
	fly.loop = false;

	animation = &fly;

	collider = App->collision->AddCollider({ 0, 0, 32, 16 }, COLLIDER_TYPE::COLLIDER_ENEMY, (Module*)App->enemies);

}

void Plane::Move()
{

	if (position.x + fly.ConsultCurrentFrame().w < SCREEN_WIDTH / 2 + fly.frames[7].w/2)
	{
		position.x += 0.05;
		position.y += 0.25;
	}
	else if (position.x - fly.ConsultCurrentFrame().w > SCREEN_WIDTH / 2 - fly.frames[7].w / 2)
	{
		position.x -= 0.05;
		position.y += 0.25;
	}
	else
	{
		position.y -= 4;
	}

}
