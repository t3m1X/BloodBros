#ifndef __ENEMY_PLANE_H__
#define __ENEMY_PLANE_H__

#include "Enemy.h"
#include "p2Point.h"
#include "Path.h"


struct Mix_Chunk;

class Plane : public Enemy
{
private:

	Animation fly;
	Uint32 hitpoints;
	Mix_Chunk* sfx;

public:

	Plane(int x);
	~Plane();
	bool has_shot = false;

	void Move();
	void Collision();
};

#endif // __ENEMY_PLANE_H__