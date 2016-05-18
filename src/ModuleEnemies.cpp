#include "Application.h"
#include "ModuleInput.h"
#include "ModuleRender.h"
#include "ModuleEnemies.h"
#include "ModuleParticles.h"
#include "ModuleTextures.h"
#include "ModuleUserI.h"
#include "Enemy.h"
#include "Enemy_GCowboy.h"
#include "Enemy_BIndian.h"
#include "Enemy_Plane.h"
#include "Enemy_Dancer.h"
#include "Building_LWaterTower.h"
#include "Building_RWaterTower.h"
#include "Enemy_V_Right1.h"
#include "Enemy_V_Left1.h"
#include "Enemy_V_Right2.h"
#include "Enemy_V_Left2.h"
#include "Enemy_V_Right3.h"
#include "Enemy_V_Left3.h"
#include "Cactus.h"
#include "Enemy_Wagon.h"
#include "Enemy_Horse.h"
#include "Building_LPipe.h"
#include "Building_RPipe.h"
#include "ModulePlayer.h"

#define SPAWN_MARGIN 50

ModuleEnemies::ModuleEnemies()
{
	for (uint i = 0; i < MAX_ENEMIES; ++i)
	{
		enemies[i] = nullptr;
	}
}

// Destructor
ModuleEnemies::~ModuleEnemies()
{
}

bool ModuleEnemies::Start()
{
	// Create a prototype for each enemy available so we can copy them around
	sprites = App->textures->Load("sprites/EnemySprites-rearranged.png");

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

	for (uint i = 0; i < MAX_ENEMIES; ++i)
	{
		if (enemies[i] != nullptr)
		{
			if (enemies[i]->isDead)
			{
				delete enemies[i];
				enemies[i] = nullptr;
			}
		}
	}

	return UPDATE_CONTINUE;
}

// Called before render is available
update_status ModuleEnemies::Update()
{

	for (uint i = 0; i < MAX_ENEMIES; ++i)
	{
		if (enemies[i] != nullptr) enemies[i]->Move();
	}

	for (uint i = MAX_ENEMIES - 1; i > 0; --i)
	{
		if (enemies[i] != nullptr) enemies[i]->Draw(sprites);
	}

	return UPDATE_CONTINUE;
}

update_status ModuleEnemies::PostUpdate()
{
	// check camera position to decide what to spawn
	for (uint i = 0; i < MAX_ENEMIES; ++i)
	{
		if (enemies[i] != nullptr)
		{
			if (enemies[i]->position.x * SCREEN_SIZE < (App->render->camera.x) - SPAWN_MARGIN)
			{
				LOG("DeSpawning enemy at %d", enemies[i]->position.x * SCREEN_SIZE);
				delete enemies[i];
				enemies[i] = nullptr;
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

	for (uint i = 0; i < MAX_ENEMIES; ++i)
	{
		if (enemies[i] != nullptr)
		{
			delete enemies[i];
			enemies[i] = nullptr;
		}
	}

	return true;
}

bool ModuleEnemies::AddEnemy(ENEMY_TYPES type, int x, int y, bool front, bool building)
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
			queue[i].building = building;
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
	if (info.building)
	{
		if (info.front)
			for (i = MAX_ENEMIES / 2 - 2; enemies[i] != nullptr && i < MAX_ENEMIES / 2; ++i);
		else
			for (i = MAX_ENEMIES - 2; enemies[i] != nullptr && i < MAX_ENEMIES; ++i);
	}
	else
	{
		if (info.front)
			for (; enemies[i] != nullptr && i < MAX_ENEMIES / 2 - 2; ++i);
		else
			for (i = MAX_ENEMIES / 2; enemies[i] != nullptr && i < MAX_ENEMIES - 2; ++i);
	}

	if (i != MAX_ENEMIES)
	{
		switch (info.type)
		{
		case ENEMY_TYPES::PLANE:
			enemies[i] = new Plane(info.x);
			break;
		case ENEMY_TYPES::G_COWBOY:
			enemies[i] = new GCowboy(info.x, info.y);
			break;
		case ENEMY_TYPES::B_INDIAN:
			enemies[i] = new BIndian(info.x, info.y);
			break;
		case ENEMY_TYPES::DANCER:
			enemies[i] = new Dancer(info.x, info.y);
			break;
		case ENEMY_TYPES::L_WATERTOWER:
			enemies[i] = new LWaterTower(info.x, info.y);
			break;
		case ENEMY_TYPES::R_WATERTOWER:
			enemies[i] = new RWaterTower(info.x, info.y);
			break;
		case ENEMY_TYPES::V_FORMATION_R1:
			enemies[i] = new Enemy_V_Right1(info.x, info.y);
			break;
		case ENEMY_TYPES::V_FORMATION_L1:
			enemies[i] = new Enemy_V_Left1(info.x, info.y);
			break;
		case ENEMY_TYPES::V_FORMATION_R2:
			enemies[i] = new Enemy_V_Right2(info.x, info.y);
			break;
		case ENEMY_TYPES::V_FORMATION_L2:
			enemies[i] = new Enemy_V_Left2(info.x, info.y);
			break;
		case ENEMY_TYPES::V_FORMATION_R3:
			enemies[i] = new Enemy_V_Right3(info.x, info.y);
			break;
			case ENEMY_TYPES::V_FORMATION_L3:
			enemies[i] = new Enemy_V_Left3(info.x, info.y);
			break;
		case ENEMY_TYPES::CACTUS:
			enemies[i] = new Cactus(info.x, info.y);
			break;
		case ENEMY_TYPES::WAGON:
			enemies[i] = new Wagon(info.x, info.y);
			break;
		case ENEMY_TYPES::HORSE:
			enemies[i] = new Horse(info.x, info.y);
			break;
		case ENEMY_TYPES::LPIPE:
			enemies[i] = new LPipe(info.x, info.y);
			break;
		case ENEMY_TYPES::RPIPE:
			enemies[i] = new RPipe(info.x, info.y);
		}
	}
}

void ModuleEnemies::OnCollision(Collider* c1, Collider* c2)
{
	for (uint i = 0; i < MAX_ENEMIES; ++i)
	{
		if (enemies[i] != nullptr && enemies[i]->GetCollider() == c1)
		{
			enemies[i]->Collision();
			if (enemies[i]->isDead)
			{
				delete enemies[i];
				enemies[i] = nullptr;
			}
			break;
		}
	}
}