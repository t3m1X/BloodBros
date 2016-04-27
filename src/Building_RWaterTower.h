#ifndef __BUILDING_RWATERTOWER__
#define __BUILDING_RWATERTOWER__

#include "Enemy.h"
#include "p2Point.h"
#include "Path.h"

class RWaterTower : public Enemy
{
private:

	Animation state;
	Uint32 this_call;
	Uint32 next_call = 0;

public:

	RWaterTower(int x, int y);

	void Draw(SDL_Texture* sprites);
	void Collision();
};

#endif // __BUILDING_RWATERTOWER__