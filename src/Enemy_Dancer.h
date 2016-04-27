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

	Uint32 speed = 2;



public:

	Dancer(int x, int y);

	void Move();
	void Collision();

};

#endif // __ENEMY_DANCER_H__