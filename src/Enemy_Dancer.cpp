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
	
	animation = &walk;

	collider = App->collision->AddCollider({ x, y, 48, 48}, COLLIDER_TYPE::COLLIDER_ENEMY, (Module*)App->enemies);

	sfx = App->audio->LoadSFX("sound/soundfx/dancer_hit.wav");

	position.x = 0;
}

Dancer::~Dancer()
{
	App->audio->UnloadSFX(sfx);
}

void Dancer::Move()
{
	position.x += speed;
	
}

void Dancer::Collision()
{
	App->audio->PlaySFX(sfx);
	speed = 7;
	animation = &dance;
}