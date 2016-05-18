#ifndef __ENEMY_WAGON_H__
#define __ENEMY_WAGON_H__

#include "Enemy.h"
#include "p2Point.h"
#include "Path.h"

class Wagon : public Enemy
{
private:

	Animation walk;
	Animation shoot;
	Animation dead;
	p2Point<int> i_pos;
	Path Wagon_path;

	Uint32 current_time = 0;
	Uint32 shoot_end = 0;

	bool has_shot = false;



public:

	Wagon(int x, int y);
	void Move();
};

#endif // __ENEMY_GCOWBOY_H__