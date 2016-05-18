#ifndef __BUILDING_LPipe__
#define __BUILDING_LPipe__

#include "Enemy.h"
#include "p2Point.h"
#include "Path.h"

class LPipe : public Enemy
{
private:

	Animation state;
	Animation dead_state;
	Uint32 this_call;
	Uint32 next_call = 0;

public:

	LPipe(int x, int y);

	void Draw(SDL_Texture* sprites);
	void Collision();
};

#endif // __BUILDING_CACTUS__