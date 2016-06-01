#ifndef __ENEMY_HORSE_H__
#define __ENEMY_HORSE_H__

#include "Enemy.h"
#include "p2Point.h"
#include "Path.h"


struct Mix_Chunk;

class Horse : public Enemy
{
private:

	Animation walk;
	Animation shoot;
	Animation dead;
	Animation neigh;
	Animation regular;
	Animation dead_indian;
	Animation* animation_indian;
	Mix_Chunk* sfx;
	p2Point<int> i_pos;
	Path Horse_path;

	Uint32 current_time = 0;
	Uint32 shoot_end = 0;

	bool has_shot = false;



public:

	Horse(int x, int y);
	~Horse();
	void Move();
	void Collision();
	void Draw(SDL_Texture* sprites);
};

#endif // __ENEMY_HORSE_H__