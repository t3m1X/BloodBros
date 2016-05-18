#ifndef __BUILDING_RPipe__
#define __BUILDING_RPipe__

#include "Enemy.h"
#include "p2Point.h"
#include "Path.h"

class RPipe : public Enemy
{
private:

	Animation state;
	Animation dead_state;
	Uint32 this_call;
	Uint32 next_call = 0;

public:

	RPipe(int x, int y);

	void Draw(SDL_Texture* sprites);
	void Collision();
};

#endif // __BUILDING_CACTUS__