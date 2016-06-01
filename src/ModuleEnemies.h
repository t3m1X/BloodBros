#ifndef __ModuleEnemies_H__
#define __ModuleEnemies_H__

#include "Module.h"


#define MAX_ENEMIES 40
#define MAX_BUILDINGS 12    

enum ENEMY_TYPES
{
	NO_TYPE,
	G_COWBOY,
	B_INDIAN,
	PLANE,
	L_WATERTOWER,
	R_WATERTOWER,
	DANCER,
	V_FORMATION_R1,
	V_FORMATION_R2,
	V_FORMATION_R3,
	V_FORMATION_L1,
	V_FORMATION_L2,
	V_FORMATION_L3,
	CACTUS,
	WAGON,
	HORSE,
	LPIPE,
	RPIPE,
	TOP_PIPES,
	TOP_PIPES2,
	CAN
};

class Enemy;

struct EnemyInfo
{
	ENEMY_TYPES type = ENEMY_TYPES::NO_TYPE;
	int x, y;
	bool front;
	bool building;
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

	void killEverything();

	bool AddEnemy(ENEMY_TYPES type, int x, int y, bool front, bool building = false);

private:

	void SpawnEnemy(const EnemyInfo& info);

private:

	EnemyInfo queue[MAX_ENEMIES];
	Enemy* enemies[MAX_ENEMIES];
	SDL_Texture* sprites;
};

#endif // __ModuleEnemies_H__