#ifndef __BUILDING_LWATERTOWER__
#define __BUILDING_LWATERTOWER__

#include "Enemy.h"
#include "p2Point.h"
#include "Path.h"

class LWaterTower : public Enemy
{
private:

	Animation state;
	Uint32 this_call;
	Uint32 next_call = 0;

public:

	LWaterTower(int x, int y);

	void Draw(SDL_Texture* sprites);
	void Collision();
};

#endif // __BUILDING_LWATERTOWER__