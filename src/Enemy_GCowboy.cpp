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

	/*FIRST COWBOY : 67 X 144 1632 X 1586
	SECOND : 99 X 144 1632 X 1586
		THIRD : 120 X 140 1632 X 1586
			FOURTH : 64 X 144  1632 X 1586
				FIFTH : 96 X 144 1632 X 1586
					SIXTH : 120 X 140 1632 X 1586
					SEVENTH : 123 X 140 1632 X 1586
					EIGHTH : 102 X 180 1632 X 1586
					NINTH : 105 X 165 1632 X 1586
					 10TH : 104 X 128  1632 X 1586
					 11TH : 128 X 100  1632 X 1586
					 12TH : 128 X 28   1632 X 1586*/
	walk.speed = 0.1f;

	i_pos.x = x;
	i_pos.y = y;


	/*GCowboy_path.PushBack({ -1, 0 }, 50, &walk);
	GCowboy_path.PushBack({ 0, 0 }, 50, &shoot);		//Walks, shoots and leaves; to improve
	GCowboy_path.PushBack({ -1, 0 }, 50, &walk);*/

}

void GCowboy::Update()
{

	position = i_pos + GCowboy_path.GetCurrentSpeed(&animation);

}
