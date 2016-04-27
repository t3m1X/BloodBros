#include "Application.h"
#include "Enemy_GCowboy.h"
#include "Path.h"
#include "ModuleCollision.h"
#include "p2Point.h"
#include "ModuleParticles.h"

GCowboy::GCowboy(int x, int y) : Enemy(x, y)
{

	walk.PushBack({ 229, 662, 67, 144 });
	walk.PushBack({ 321, 659, 99, 144 });
	walk.PushBack({ 433, 663, 120, 140 });
	walk.PushBack({ 566, 661, 64, 144 });
	walk.PushBack({ 656, 662, 96, 144 });
	walk.PushBack({ 757, 664, 120, 140 });
	walk.speed = 0.1f;


	shoot.PushBack({ 891, 661, 123, 140 });
	shoot.PushBack({ 1025, 618, 102, 148 });
	shoot.speed = 0.1f;

	dead.PushBack({ 1132, 635, 105, 165 });
	dead.PushBack({ 1276, 677, 104, 128 });
	dead.PushBack({ 1411, 689, 128, 100 });
	dead.PushBack({ 23, 910, 128, 28 });
	dead.speed = 0.1f;


	i_pos.x = x;
	i_pos.y = y;


	GCowboy_path.PushBack({ -1, 0 }, 50, &walk);
	GCowboy_path.PushBack({ 0, 0 }, 50, &shoot);		//Walks, shoots and leaves; to improve
	GCowboy_path.PushBack({ -1, 0 }, 50, &walk);

}

void GCowboy::Move()
{

	position = i_pos + GCowboy_path.GetCurrentSpeed(&animation);

}
