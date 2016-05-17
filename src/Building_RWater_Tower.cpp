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
	state.PushBack({ 1392, 0, 288, 480 });
	state.PushBack({ 1392, 960, 288, 480 });
	state.PushBack({ 1392, 1440, 288, 480 });
	

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