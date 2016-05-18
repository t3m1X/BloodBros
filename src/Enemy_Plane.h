#ifndef __ENEMY_PLANE_H__
#define __ENEMY_PLANE_H__

#include "Enemy.h"
#include "p2Point.h"
#include "Path.h"

class Plane : public Enemy
{
private:

	Animation fly;

public:

	Plane(int x);
	bool has_shot = false;

	void Move();
	void Collision();
};

#endif // __ENEMY_PLANE_H__