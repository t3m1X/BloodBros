#include "Application.h"
#include "Building_RWaterTower.h"
#include "Path.h"
#include "ModuleCollision.h"
#include "p2Point.h"
#include "ModuleParticles.h"
#include "ModuleRender.h"

#include "SDL/include/SDL.h"
#pragma comment( lib, "SDL_mixer/libx86/SDL2_mixer.lib" )

RWaterTower::RWaterTower(int x, int y) : Enemy(x, y)
{
	state.PushBack({ 1687, 61, 257, 463 });
	state.PushBack({ 1689, 1022, 255, 464 });
	state.PushBack({ 1690, 1506, 254, 464 });
	

	state.speed = 1.0f;
	state.loop = false;

	collider = App->collision->AddCollider({ x, y, 200, 448 }, COLLIDER_TYPE::COLLIDER_ENEMY, (Module*)App->enemies);

	position.x = SCREEN_WIDTH-250;
}


void RWaterTower::Draw(SDL_Texture* sprites)
{
	App->render->Blit(sprites, position.x, position.y, &(state.ConsultCurrentFrame()));
}


void RWaterTower::Collision()
{
	this_call = SDL_GetTicks();

	if (this_call > next_call)
	{
		next_call = this_call + 1000;
		if (state.Finished())
		{
			App->particles->AddParticle(App->particles->dust, position.x, position.y + 448 - 120);
			isDead = true;
		}
		else
			state.GetCurrentFrame();
	}
}