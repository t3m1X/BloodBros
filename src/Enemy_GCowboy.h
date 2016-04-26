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
	Collider* c_GCowboy;


public:

	GCowboy(int x, int y);

	void Update();
};

#endif // __ENEMY_GCOWBOY_H__