#include "Application.h"
#include "Enemy_Dancer.h"
#include "Path.h"
#include "ModuleCollision.h"
#include "p2Point.h"
#include "ModuleParticles.h"
#include "ModuleAudio.h"


Dancer::Dancer(int x, int y) : Enemy(x, y)
{

	walk.PushBack({0, 2688, 96, 144 });
	walk.PushBack({ 96, 2688, 96, 144 });
	walk.speed = 0.2f;

	dance.PushBack({ 192, 2688, 96, 144 });
	dance.PushBack({ 288, 2688, 96, 144 });
	dance.speed = 0.25f;
	

	dead.PushBack({ 588, 2688, 96, 144 });
	dead.PushBack({ 1276, 2688, 96, 144 });
	dead.PushBack({ 1411, 2688, 96, 144 });
	dead.PushBack({ 23, 2688, 96, 144 });
	dead.speed = 0.1f;
	dead.loop = false;

	speed = 2;
	hitpoints = 6;

	animation = &walk;

	collider = App->collision->AddCollider({ x, y, 48, 48}, COLLIDER_TYPE::COLLIDER_ENEMY, (Module*)App->enemies);

	sfx = App->audio->LoadSFX("sound/soundfx/dancer_hit.wav");

	position.x = x;
	position.y = y;
}

Dancer::~Dancer()
{
	App->audio->UnloadSFX(sfx);
}

void Dancer::Move()
{
	switch (state)
	{
	case ST_REGULAR:
		position.x += speed;
		break;
	case ST_DYING:
		animation = &dead;
		isDead = dead.Finished();
	}
	
}

void Dancer::Collision()
{
	if (hitpoints != 0)
	{
		App->audio->PlaySFX(sfx);
		speed = 7;
		animation = &dance;
		--hitpoints;
	}
	else
	{
		App->collision->EraseCollider(collider);
		collider = nullptr;
		state = ST_DYING;
	}
}