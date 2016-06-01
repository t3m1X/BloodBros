#include "Globals.h"
#include "Application.h"
#include "ModuleItems.h"
#include "ModuleCollision.h"
#include "ModuleTextures.h"
#include "ModuleRender.h"
#include "ModuleUserI.h"

#include "SDL/include/SDL.h"
#pragma comment( lib, "SDL_mixer/libx86/SDL2_mixer.lib" )

Bonus::~Bonus()
{
	if (collider != nullptr)
	{
		App->collision->EraseCollider(collider);
		collider = nullptr;
	}
}

ModuleItems::ModuleItems()
{
	for (uint i = 0; i < MAX_BONUS; ++i)
		bonus[i] = nullptr;

	//pushBacks here
}

ModuleItems::~ModuleItems()
{}

bool ModuleItems::Start()
{
	sprites = App->textures->Load("sprites/PowerUp1.png");

	return true;
}

update_status ModuleItems::Update()
{
	for (uint i = 0; i < MAX_BONUS; ++i)
	{
		if (bonus[i] != nullptr)
		{
			bonus[i]->y += bonus[i]->v;
			if (bonus[i]->y == bonus[i]->yo + 10)
				bonus[i]->v = -1;
		}
	}

	for (uint i = 0; i < MAX_BONUS; ++i)
	{
		if (bonus[i] != nullptr)
			App->render->Blit(sprites, bonus[i]->x, bonus[i]->y, &bonus[i]->animation->GetCurrentFrame());
	}

	return UPDATE_CONTINUE;
}

update_status ModuleItems::PostUpdate()
{
	
	for (uint i = 0; i < MAX_BONUS; ++i)
	{
		uint currenttime = SDL_GetTicks();
		if (bonus[i] != nullptr)
		{
			if (bonus[i]->lifespan < currenttime)
			{
				delete bonus[i];
				bonus[i] = nullptr;
			}
		}
	}
	return UPDATE_CONTINUE;
}


bool ModuleItems::CleanUp()
{
	for (uint i = 0; i < MAX_BONUS; ++i)
	{
		if (bonus[i] != nullptr)
		{
			delete bonus[i];
			bonus[i] = nullptr;
		}
	}

	App->textures->Unload(sprites);
	return true;
}

void ModuleItems::SpawnBonus(int x, int y, BONUS_TYPE type)
{
	for (uint i = 0; i < MAX_BONUS; ++i)
	{
		if (bonus[i] == nullptr)
		{
			switch (type)
			{
			case SCORE_70000:
				bonus[i] = new Bonus(type, x, y, &an_score_70000, App->collision->AddCollider(an_score_70000.ConsultCurrentFrame(), COLLIDER_BONUS, this), SDL_GetTicks() + 10000);
				break;
			case SCORE_50000:
				bonus[i] = new Bonus(type, x, y, &an_score_50000, App->collision->AddCollider(an_score_50000.ConsultCurrentFrame(), COLLIDER_BONUS, this), SDL_GetTicks() + 10000);
				break;
			case SCORE_20000:
				bonus[i] = new Bonus(type, x, y, &an_score_20000, App->collision->AddCollider(an_score_20000.ConsultCurrentFrame(), COLLIDER_BONUS, this), SDL_GetTicks() + 10000);
				break;
			case SCORE_10000:
				bonus[i] = new Bonus(type, x, y, &an_score_10000, App->collision->AddCollider(an_score_10000.ConsultCurrentFrame(), COLLIDER_BONUS, this), SDL_GetTicks() + 10000);
				break;
			case SCORE_7000:
				bonus[i] = new Bonus(type, x, y, &an_score_7000, App->collision->AddCollider(an_score_7000.ConsultCurrentFrame(), COLLIDER_BONUS, this), SDL_GetTicks() + 10000);
				break;
			case SCORE_5000:
				bonus[i] = new Bonus(type, x, y, &an_score_5000, App->collision->AddCollider(an_score_5000.ConsultCurrentFrame(), COLLIDER_BONUS, this), SDL_GetTicks() + 10000);
				break;
			case SCORE_2000:
				bonus[i] = new Bonus(type, x, y, &an_score_2000, App->collision->AddCollider(an_score_2000.ConsultCurrentFrame(), COLLIDER_BONUS, this), SDL_GetTicks() + 10000);
				break;
			case SCORE_1000:
				bonus[i] = new Bonus(type, x, y, &an_score_1000, App->collision->AddCollider(an_score_1000.ConsultCurrentFrame(), COLLIDER_BONUS, this), SDL_GetTicks() + 10000);
				break;

			}
			break;
		}
	}
}

void ModuleItems::OnCollision(Collider* c1, Collider* c2)
{
	for (uint i = 0; i < MAX_BONUS; ++i)
	{
		if (bonus[i] != nullptr && bonus[i]->collider == c1)
		{
			switch (bonus[i]->type)
			{
			case SCORE_70000:
				App->useri->score += 70000;
				break;
			case SCORE_50000:
				App->useri->score += 50000;
				break;
			case SCORE_20000:
				App->useri->score += 20000;
				break;
			case SCORE_10000:
				App->useri->score += 10000;
				break;
			case SCORE_7000:
				App->useri->score += 7000;
				break;
			case SCORE_5000:
				App->useri->score += 5000;
				break;
			case SCORE_2000:
				App->useri->score += 2000;
				break;
			case SCORE_1000:
				App->useri->score += 1000;
				break;
			}
			break;
		}
	}
}