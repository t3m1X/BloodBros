#ifndef __BUILDING_Top_Pipes2__
#define __BUILDING_Top_Pipes2__

#include "Enemy.h"
#include "p2Point.h"
#include "Path.h"

class Top_Pipes2 : public Enemy
{
private:

	Animation state;
	Animation dead_state;
	Uint32 this_call;
	Uint32 next_call;
	SDL_Rect last_anim;

public:

	Top_Pipes2(int x, int y);

	void Draw(SDL_Texture* sprites);
	void Collision();
	void Move();
};

#endif // __BUILDING_Top_Pipes2__