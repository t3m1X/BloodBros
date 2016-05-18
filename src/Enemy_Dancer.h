#ifndef __ENEMY_DANCER_H__
#define __ENEMY_DANCER_H__

#include "Enemy.h"
#include "p2Point.h"
#include "Path.h"

struct Mix_Chunk;

class Dancer : public Enemy
{
private:

	Animation walk;
	Animation dance;
	Animation dead;
	p2Point<int> i_pos;
	Path Dancer_path;
	Mix_Chunk* sfx;
	Uint32 speed;
	Uint32 hitpoints;



public:

	Dancer(int x, int y);
	~Dancer();

	void Move();
	void Collision();

};

#endif // __ENEMY_DANCER_H__