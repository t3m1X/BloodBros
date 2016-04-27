#ifndef __BUILDING_LWATERTOWER__
#define __BUILDING_LWATERTOWER__

#include "Enemy.h"
#include "p2Point.h"
#include "Path.h"

class LWaterTower : public Enemy
{
private:

	Animation state;

public:

	LWaterTower(int x, int y);

};

#endif // __BUILDING_LWATERTOWER__