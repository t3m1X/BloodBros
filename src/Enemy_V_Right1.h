#ifndef __ENEMY_Enemy_V_Right1_H__
#define __ENEMY_Enemy_V_Right1_H__

#include "Enemy.h"
#include "p2Point.h"
#include "Path.h"

class Enemy_V_Right1 : public Enemy
{
private:

	Animation appear;
	Animation walk;
	Animation dead;
	p2Point<int> i_pos;
	Path path;

	Uint32 current_time = 0;



public:

	Enemy_V_Right1(int x, int y);

	void Move();
};

#endif // __ENEMY_Enemy_V_Right1_H__