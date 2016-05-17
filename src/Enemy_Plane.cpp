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


	fly.PushBack({ 157, 67, 22, 10 });
	fly.PushBack({ 483, 62, 43, 22 });
	fly.PushBack({ 797, 65, 85, 37 });
	fly.PushBack({ 104, 192, 128, 53 });
	fly.PushBack({ 419, 188, 170, 64 });
	fly.PushBack({ 734, 179, 212, 82 });
	fly.PushBack({ 41, 3016, 253, 101 });
	fly.PushBack({ 355, 299, 298, 126 });
	fly.speed = 0.045f;
	fly.loop = false;

	animation = &fly;

	collider = App->collision->AddCollider({ 0, 0, 32, 16 }, COLLIDER_TYPE::COLLIDER_ENEMY, (Module*)App->enemies);

}

void Plane::Move()
{
	if (has_shot)
	{
		position.y -= 4;
	}

	if (position.x + fly.frames[fly.next_frame()].w / 2 < SCREEN_WIDTH / 2)
	{
		position.x += 1;
		position.y += 0.5;
	}
	else if (position.x + fly.frames[fly.next_frame()].w / 2 > SCREEN_WIDTH / 2)
	{
		position.x -= 1;
		position.y += 0.5;
	}
	else if (!has_shot)
	{
		App->particles->AddParticle(App->particles->bomb, position.x, position.y + (fly.frames[7].h - fly.frames[7].h / 4), COLLIDER_ENEMY_SHOT);
		App->particles->AddParticle(App->particles->bomb, position.x + fly.frames[7].w / 2, position.y + (fly.frames[7].h - fly.frames[7].h / 4), COLLIDER_ENEMY_SHOT);
		App->particles->AddParticle(App->particles->bomb, position.x + fly.frames[7].w , position.y + (fly.frames[7].h - fly.frames[7].h / 4), COLLIDER_ENEMY_SHOT);
		has_shot = true;
	}

}
