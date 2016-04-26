#ifndef __ENEMY_BINDIAN__
#define __ENEMY_BINDIAN__

#include "Enemy.h"
#include "p2Point.h"
#include "Path.h"

class BIndian : public Enemy
{

private:

	Animation walk;
	Animation shoot;
	Animation dead;
	p2Point<int> i_pos;
	Path BIndian_path;
	Collider* c_BIndian;

public:

	BIndian(int x, int y);

	void Move();

};

#endif 