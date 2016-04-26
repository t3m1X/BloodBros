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


	fly.PushBack({ 53, 127, 32, 16 });
	fly.PushBack({ 101, 119, 64, 32 });
	fly.PushBack({ 181, 102, 128, 56 });
	fly.PushBack({ 329, 91, 192, 80 });
	fly.PushBack({ 550, 85, 256, 96 });
	fly.PushBack({ 822, 79, 319, 123 });
	fly.PushBack({ 25, 211, 379, 152 });
	fly.PushBack({ 459, 275, 448, 188 });

	fly.speed = 0.1f;

	collider = App->collision->AddCollider({ 0, 0, 32, 16 }, COLLIDER_TYPE::COLLIDER_ENEMY, (Module*)App->enemies);

}

void Plane::Move()
{

	if (position.x < SCREEN_WIDTH / 2)
	{
		position.x++;
		position.y--;
	}
	else if (position.x > SCREEN_WIDTH / 2)
	{
		position.x--;
		position.y--;
	}
	else
	{
		position.y++;
	}

}
