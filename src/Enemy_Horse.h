#ifndef __ENEMY_HORSE_H__
#define __ENEMY_HORSE_H__

#include "Enemy.h"
#include "p2Point.h"
#include "Path.h"

class Horse : public Enemy
{
private:

	Animation walk;
	Animation shoot;
	Animation dead;
	p2Point<int> i_pos;
	Path Horse_path;

	Uint32 current_time = 0;
	Uint32 shoot_end = 0;

	bool has_shot = false;



public:

	Horse(int x, int y);
	void Move();
};

#endif // __ENEMY_HORSE_H__