#ifndef __CAN__
#define __CAN__

#include "Enemy.h"
#include "p2Point.h"
#include "Path.h"

class Can : public Enemy
{
private:

	Animation still;
	Animation flying;

	uint y_pos;

	bool fly = false;
	bool mid_fly = false;
	

public:

	Can(int x, int y);

	void Collision();
	void Move();
};

#endif // __BUILDING_CAN__