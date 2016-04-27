#include "Application.h"
#include "ModuleInput.h"
#include "ModuleRender.h"
#include "ModuleEnemies.h"
#include "ModuleParticles.h"
#include "ModuleTextures.h"
#include "Enemy.h"
#include "Enemy_GCowboy.h"
#include "Enemy_BIndian.h"
#include "Enemy_Plane.h"
#include "Enemy_Dancer.h"
#include "Building_LWaterTower.h"
#include "Building_RWaterTower.h"

#define SPAWN_MARGIN 50

ModuleEnemies::ModuleEnemies()
{
	for (uint i = 0; i < MAX_ENEMIES / 2; ++i)
	{
		f_enemies[i] = nullptr;
		b_enemies[i] = nullptr;
	}
}

// Destructor
ModuleEnemies::~ModuleEnemies()
{
}

bool ModuleEnemies::Start()
{
	// Create a prototype for each enemy available so we can copy them around
	sprites = App->textures->Load("sprites/EnemySprites.png");

	return true;
}

update_status ModuleEnemies::PreUpdate()
{
	// check camera position to decide what to spawn
	for (uint i = 0; i < MAX_ENEMIES; ++i)
	{
		if (queue[i].type != ENEMY_TYPES::NO_TYPE)
		{
			if (queue[i].x * SCREEN_SIZE < App->render->camera.x + (App->render->camera.w * SCREEN_SIZE) + SPAWN_MARGIN)
			{
				SpawnEnemy(queue[i]);
				queue[i].type = ENEMY_TYPES::NO_TYPE;
				LOG("Spawning enemy at %d", queue[i].x * SCREEN_SIZE);
			}
		}
	}

	return UPDATE_CONTINUE;
}

// Called before render is available
update_status ModuleEnemies::Update()
{
	for (uint i = 0; i < MAX_ENEMIES / 2; ++i)
	{
		if (f_enemies[i] != nullptr) f_enemies[i]->Move();
		if (b_enemies[i] != nullptr) b_enemies[i]->Move();
	}

	for (uint i = 0; i < MAX_ENEMIES / 2; ++i)
	{
		if (b_enemies[i] != nullptr)
			b_enemies[i]->Draw(sprites);

		if (f_enemies[i] != nullptr)
			f_enemies[i]->Draw(sprites);
	}

	return UPDATE_CONTINUE;
}

update_status ModuleEnemies::PostUpdate()
{
	// check camera position to decide what to spawn
	for (uint i = 0; i < MAX_ENEMIES / 2; ++i)
	{
		if (f_enemies[i] != nullptr)
		{
			if (f_enemies[i]->position.x * SCREEN_SIZE < (App->render->camera.x) - SPAWN_MARGIN)
			{
				LOG("DeSpawning enemy at %d", f_enemies[i]->position.x * SCREEN_SIZE);
				delete f_enemies[i];
				f_enemies[i] = nullptr;
			}
		}

		if (b_enemies[i] != nullptr)
		{
			if (b_enemies[i]->position.x * SCREEN_SIZE < (App->render->camera.x) - SPAWN_MARGIN)
			{
				LOG("DeSpawning enemy at %d", b_enemies[i]->position.x * SCREEN_SIZE);
				delete b_enemies[i];
				b_enemies[i] = nullptr;
			}
		}
	}

	return UPDATE_CONTINUE;
}

// Called before quitting
bool ModuleEnemies::CleanUp()
{
	LOG("Freeing all enemies");

	App->textures->Unload(sprites);

	for (uint i = 0; i < MAX_ENEMIES/2; ++i)
	{
		if (f_enemies[i] != nullptr)
		{
			delete f_enemies[i];
			f_enemies[i] = nullptr;
		}

		if (b_enemies[i] != nullptr)
		{
			delete b_enemies[i];
			b_enemies[i] = nullptr;
		}
	}

	return true;
}

bool ModuleEnemies::AddEnemy(ENEMY_TYPES type, int x, int y, bool front)
{
	bool ret = false;

	for (uint i = 0; i < MAX_ENEMIES; ++i)
	{
		if (queue[i].type == ENEMY_TYPES::NO_TYPE)
		{
			queue[i].type = type;
			queue[i].x = x;
			queue[i].y = y;
			queue[i].front = front;
			ret = true;
			break;
		}
	}

	return ret;
}

void ModuleEnemies::SpawnEnemy(const EnemyInfo& info)
{
	// find room for the new enemy
	uint i = 0;
	Enemy** newenemy;
	if (info.front)
	{
		for (; f_enemies[i] != nullptr && i < MAX_ENEMIES / 2; ++i);
		newenemy = &f_enemies[i];
	}
	else
	{
		for (; b_enemies[i] != nullptr && i < MAX_ENEMIES / 2; ++i);
		newenemy = &b_enemies[i];
	}

	if (i != MAX_ENEMIES / 2)
	{
		switch (info.type)
		{
		case ENEMY_TYPES::PLANE:
			*newenemy = new Plane(info.x);
			break;
		case ENEMY_TYPES::G_COWBOY:
			*newenemy = new GCowboy(info.x, info.y);
			break;
		case ENEMY_TYPES::B_INDIAN:
			*newenemy = new BIndian(info.x, info.y);
			break;
		case ENEMY_TYPES::DANCER:
			*newenemy = new Dancer(info.x, info.y);
			break;
		case ENEMY_TYPES::L_WATERTOWER:
			*newenemy = new LWaterTower(info.x, info.y);
			break;
		case ENEMY_TYPES::R_WATERTOWER:
			*newenemy = new RWaterTower(info.x, info.y);
		}
	}
}

void ModuleEnemies::OnCollision(Collider* c1, Collider* c2)
{
	for (uint i = 0; i < MAX_ENEMIES / 2; ++i)
	{
		if (f_enemies[i] != nullptr && f_enemies[i]->GetCollider() == c1)
		{
			f_enemies[i]->Collision();
			if (f_enemies[i]->isDead)
			{
				delete f_enemies[i];
				f_enemies[i] = nullptr;
			}
			break;
		}

		if (b_enemies[i] != nullptr && b_enemies[i]->GetCollider() == c1)
		{
			b_enemies[i]->Collision();
			if (b_enemies[i]->isDead)
			{
				delete b_enemies[i];
				b_enemies[i] = nullptr;
			}
			break;
		}
	}
}