#ifndef __BUILDING_RWATERTOWER__
#define __BUILDING_RWATERTOWER__

#include "Enemy.h"
#include "p2Point.h"
#include "Path.h"

class RWaterTower : public Enemy
{
private:

	Animation building;
	Uint32 this_call;
	Uint32 next_call = 0;
	SDL_Rect last_anim;

public:

	RWaterTower(int x, int y);

	void Draw(SDL_Texture* sprites);
	void Collision();
};

#endif // __BUILDING_RWATERTOWER__