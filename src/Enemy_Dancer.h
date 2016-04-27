#ifndef __ENEMY_DANCER_H__
#define __ENEMY_DANCER_H__

#include "Enemy.h"
#include "p2Point.h"
#include "Path.h"

class Dancer : public Enemy
{
private:

	Animation walk;
	Animation dance;
	Animation dead;
	p2Point<int> i_pos;
	Path Dancer_path;



public:

	Dancer(int x, int y);

	void Move();
};

#endif // __ENEMY_DANCER_H__