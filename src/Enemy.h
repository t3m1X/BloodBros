#ifndef __ENEMY_H__
#define __ENEMY_H__

#include "p2Point.h"
#include "Animation.h"

struct SDL_Texture;
struct Collider;

enum Enemy_State
{
	ST_REGULAR,
	ST_DYING
};

class Enemy
{
protected:
	Animation* animation;
	Collider* collider;

public:
	Enemy_State state;
	iPoint position;
	bool isDead = false;

public:

	Enemy(int x, int y);
	virtual ~Enemy();

	const Collider* GetCollider() const;

	virtual void Move() {};
	virtual void Draw(SDL_Texture* sprites);

	virtual void Collision();

};

#endif // __ENEMY_H__