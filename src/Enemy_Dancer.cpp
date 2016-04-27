#include "Application.h"
#include "Enemy_Dancer.h"
#include "Path.h"
#include "ModuleCollision.h"
#include "p2Point.h"
#include "ModuleParticles.h"
#include "ModuleAudio.h"


Dancer::Dancer(int x, int y) : Enemy(x, y)
{

	walk.PushBack({58, 2249, 72, 135 });
	walk.PushBack({ 151, 2252, 78, 132 });
	walk.speed = 0.2f;

	dance.PushBack({ 238, 2255, 96, 129 });
	dance.PushBack({ 337, 2255, 96, 129 });
	dance.PushBack({ 436, 2255, 96, 129 });
	dance.PushBack({ 535, 2261, 96, 123 });
	dance.speed = 0.5f;
	

	/*dead.PushBack({ 1132, 635, 105, 165 });
	dead.PushBack({ 1276, 677, 104, 128 });
	dead.PushBack({ 1411, 689, 128, 100 });
	dead.PushBack({ 23, 910, 128, 28 });
	dead.speed = 0.1f;*/

	animation = &walk;

	collider = App->collision->AddCollider({ 0, 0, 70,  }, COLLIDER_TYPE::COLLIDER_ENEMY, (Module*)App->enemies);

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
	speed = 5;
	App->audio->PlaySFX(sfx);
	speed = 10;
	animation = &dance;
}