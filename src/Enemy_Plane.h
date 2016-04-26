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

	void Move();
};

#endif // __ENEMY_PLANE_H__