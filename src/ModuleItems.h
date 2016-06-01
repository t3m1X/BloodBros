#ifndef __ModuleItems_H__
#define __ModuleItems_H__

#define MAX_BONUS 50

#include "Module.h"
#include "Animation.h"

enum BONUS_TYPE
{
	SCORE_70000 = 0,
	SCORE_50000,
	SCORE_20000,
	SCORE_10000,
	SCORE_7000,
	SCORE_5000,
	SCORE_2000,
	SCORE_1000
};

struct SDL_Texture;

struct Bonus
{
	BONUS_TYPE type;
	int x, y, yo, v;
	uint lifespan;
	Animation* animation;
	Collider* collider;

	Bonus(BONUS_TYPE _type, int _x, int _y, Animation* _animation, Collider* _collider, uint _lifespan):
		type(_type),
		x(_x),
		y(_y),
		yo(_y),
		v(-5),
		animation(_animation),
		collider(_collider),
		lifespan(_lifespan)
	{}
	
	~Bonus();

};

class ModuleItems : public Module
{
public:

	ModuleItems();
	~ModuleItems();

	bool Start();

	update_status Update();
	update_status PostUpdate();
	bool CleanUp();

	void OnCollision(Collider* c1, Collider* c2);

	void SpawnBonus(int x, int y, BONUS_TYPE type);

private:

	Bonus* bonus[MAX_BONUS];
	SDL_Texture* sprites;

	Animation an_score_70000;
	Animation an_score_50000;
	Animation an_score_20000;
	Animation an_score_10000;
	Animation an_score_7000;
	Animation an_score_5000;
	Animation an_score_2000;
	Animation an_score_1000;
};

#endif // __ModuleItems_H__
