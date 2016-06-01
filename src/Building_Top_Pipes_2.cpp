#include "Application.h"
#include "Building_Top_Pipes_2.h"
#include "Path.h"
#include "ModuleCollision.h"
#include "p2Point.h"
#include "ModuleParticles.h"
#include "ModuleRender.h"
#include "ModuleScene.h"
#include "ModuleUserI.h"

#include "SDL/include/SDL.h"
#pragma comment( lib, "SDL_mixer/libx86/SDL2_mixer.lib" )

Top_Pipes2::Top_Pipes2(int x, int y) : Enemy(x, y)
{
	building.PushBack({ 1680, 1056, 432, 96 });
	building.PushBack({ 1680, 1248, 432, 96 });
	building.PushBack({ 1680, 1440, 432, 96 });
	building.speed = 1.0f;
	building.loop = false;

	dead_building.PushBack({ 1680, 1440, 432, 96 });
	dead_building.speed = 1.0f;


	collider = App->collision->AddCollider({ x + 24, y, 375, 48 }, COLLIDER_TYPE::COLLIDER_ENEMY, (Module*)App->enemies);

}


void Top_Pipes2::Draw(SDL_Texture* sprites)
{
	App->render->Blit(sprites, position.x, position.y, &(building.ConsultCurrentFrame()));
}


void Top_Pipes2::Collision()
{
	this_call = SDL_GetTicks();

	if (this_call > next_call)
	{
		App->particles->AddParticle(App->particles->explosion, position.x, position.y - 30);
		App->particles->AddParticle(App->particles->explosion, position.x + 120 + 120 + 120, position.y - 30);
		App->particles->AddParticle(App->particles->explosion, position.x + 120 + 120, position.y - 30);
		App->particles->AddParticle(App->particles->explosion, position.x + 120, position.y - 30);
		next_call = this_call + 200;

		if (building.Finished())
		{
			state = ST_DYING;

			App->collision->EraseCollider(collider);

			App->scene->toppipe2 = false;

			App->useri->score += 400;
		}
		else
			building.GetCurrentFrame();
	}
}

void Top_Pipes2::Move()
{
	if (state == ST_DYING)
	{
		position.y += 7;
	}
	if (position.y >= SCREEN_HEIGHT / 2)
		isDead = true;

}