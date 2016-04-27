#ifndef __ENEMY_GCOWBOY_H__
#define __ENEMY_GCOWBOY_H__

#include "Enemy.h"
#include "p2Point.h"
#include "Path.h"

class GCowboy : public Enemy
{
private:

	Animation walk;
	Animation shoot;
	Animation dead;
	p2Point<int> i_pos;
	Path GCowboy_path;

	bool has_shot = false;
	


public:

	GCowboy(int x, int y);

	void Move();
};

#endif // __ENEMY_GCOWBOY_H__