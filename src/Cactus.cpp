#include "Application.h"
#include "Cactus.h"
#include "Path.h"
#include "ModuleCollision.h"
#include "p2Point.h"
#include "ModuleParticles.h"
#include "ModuleRender.h"

#include "SDL/include/SDL.h"
#pragma comment( lib, "SDL_mixer/libx86/SDL2_mixer.lib" )

Cactus::Cactus(int x, int y) : Enemy(x, y)
{
	state.PushBack({ 1776, 96, 48, 144 });
	state.PushBack({ 1728, 96, 48, 144 });
	state.PushBack({ 1680, 96, 48, 144 });
	state.speed = 1.0f;
	state.loop = false;




	collider = App->collision->AddCollider({ x, y, 96, 192 }, COLLIDER_TYPE::COLLIDER_ENEMY, (Module*)App->enemies);

}


void Cactus::Draw(SDL_Texture* sprites)
{
	App->render->Blit(sprites, position.x, position.y, &(state.ConsultCurrentFrame()));
}


void Cactus::Collision()
{
	this_call = SDL_GetTicks();

	if (this_call > next_call)
	{
		App->particles->AddParticle(App->particles->cactusboom, position.x-48, position.y+48);
		next_call = this_call + 200;
		if (state.Finished())
		{
			isDead = true;
		}

		else
			state.GetCurrentFrame();
	}
}