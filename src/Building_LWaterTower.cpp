#include "Application.h"
#include "Building_LWaterTower.h"
#include "Path.h"
#include "ModuleCollision.h"
#include "p2Point.h"
#include "ModuleParticles.h"
#include "ModuleRender.h"

#include "SDL/include/SDL.h"
#pragma comment( lib, "SDL_mixer/libx86/SDL2_mixer.lib" )

LWaterTower::LWaterTower(int x, int y) : Enemy(x, y)
{
	state.PushBack({ 1152, 0, 240, 480 });
	state.PushBack({ 1152, 960, 240, 480 });
	state.PushBack({ 1152, 1440, 240, 480 });
	state.speed = 1.0f;
	state.loop = false;

	


	collider = App->collision->AddCollider({ x, y, 200, 448 }, COLLIDER_TYPE::COLLIDER_ENEMY, (Module*)App->enemies);

}


void LWaterTower::Draw(SDL_Texture* sprites)
{
	App->render->Blit(sprites, position.x, position.y, &(state.ConsultCurrentFrame()));
}


void LWaterTower::Collision()
{
	this_call = SDL_GetTicks();

	if (this_call > next_call)
	{
		next_call = this_call + 500;
		if (state.Finished())
		{
			App->particles->AddParticle(App->particles->dust, position.x-144 , position.y+448-120 );
			isDead = true; 
		}
		
		else
			state.GetCurrentFrame();
	}
}