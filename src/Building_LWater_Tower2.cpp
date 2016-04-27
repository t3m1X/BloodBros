#include "Application.h"
#include "Building_LWaterTower2.h"
#include "Path.h"
#include "ModuleCollision.h"
#include "p2Point.h"
#include "ModuleParticles.h"
#include "ModuleRender.h"

#include "SDL/include/SDL.h"
#pragma comment( lib, "SDL_mixer/libx86/SDL2_mixer.lib" )

LWaterTower2::LWaterTower2(int x, int y) : Enemy(x, y)
{
	state.PushBack({ 1120, 64, 200, 448 });
	state.PushBack({ 1120, 533, 200, 448 });
	state.PushBack({ 1120, 1015, 200, 448 });
	state.PushBack({ 1120, 1507, 200, 448 });

	state.speed = 1.0f;
	state.loop = false;

	collider = App->collision->AddCollider({ x, y, 200, 448 }, COLLIDER_TYPE::COLLIDER_ENEMY, (Module*)App->enemies);

	position.x = SCREEN_WIDTH
}


void LWaterTower2::Draw(SDL_Texture* sprites)
{
	App->render->Blit(sprites, position.x, position.y, &(state.ConsultCurrentFrame()));
}


void LWaterTower2::Collision()
{
	this_call = SDL_GetTicks();

	if (this_call > next_call)
	{
		next_call = this_call + 2000;
		if (state.Finished())
		{
			App->particles->AddParticle(App->particles->explosion, position.x, position.y);
			isDead = true;
		}
		else
			state.GetCurrentFrame();
	}
}