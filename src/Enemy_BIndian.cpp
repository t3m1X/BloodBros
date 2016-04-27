#include "Application.h"
#include "Enemy_BIndian.h"
#include "Path.h"
#include "ModuleCollision.h"
#include "p2Point.h"
#include "ModuleParticles.h"

BIndian::BIndian(int x, int y) : Enemy(x, y)
{
	walk.PushBack({ 270, 441, 47, 90});
	walk.PushBack({ 333, 438, 66, 93});
	walk.speed = 0.1f;

	shoot.PushBack({ 413, 435, 48, 96});
	shoot.PushBack({ 478, 438, 48, 93});
	shoot.speed = 0.1f;

	dead.PushBack({ 548, 435, 84, 96});
	dead.PushBack({ 652, 456, 48, 75});
	dead.PushBack({ 716, 474, 75, 57});
	dead.PushBack({ 803, 516, 75, 15});
	dead.speed = 0.1f;
	

	i_pos.x = x;
	i_pos.y = y;

	collider = App->collision->AddCollider({ 0, 0, 70, 70 }, COLLIDER_TYPE::COLLIDER_ENEMY, (Module*)App->enemies);

	position.x = SCREEN_WIDTH;

}

void BIndian::Move()
{

}