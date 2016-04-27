#ifndef __ModuleEnemies_H__
#define __ModuleEnemies_H__

#include "Module.h"
#include "Enemy_GCowboy.h"

#define MAX_ENEMIES 20
#define MAX_BUILDINGS 8

enum ENEMY_TYPES
{
	NO_TYPE,
	G_COWBOY,
	B_INDIAN,
	PLANE,
};

class Enemy;

struct EnemyInfo
{
	ENEMY_TYPES type = ENEMY_TYPES::NO_TYPE;
	int x, y;
	bool front;
};

class ModuleEnemies : public Module
{
public:

	ModuleEnemies();
	~ModuleEnemies();

	bool Start();
	update_status PreUpdate();
	update_status Update();
	update_status PostUpdate();
	bool CleanUp();
	void OnCollision(Collider* c1, Collider* c2);

	bool AddEnemy(ENEMY_TYPES type, int x, int y, bool front = true);

private:

	void SpawnEnemy(const EnemyInfo& info);

private:

	EnemyInfo queue[MAX_ENEMIES];
	Enemy* f_enemies[MAX_ENEMIES / 2];
	Enemy* b_enemies[MAX_ENEMIES / 2];
	SDL_Texture* sprites;
};

#endif // __ModuleEnemies_H__