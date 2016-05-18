#include "Application.h"
#include "Building_RPipe.h"
#include "Path.h"
#include "ModuleCollision.h"
#include "p2Point.h"
#include "ModuleParticles.h"
#include "ModuleRender.h"

#include "SDL/include/SDL.h"
#pragma comment( lib, "SDL_mixer/libx86/SDL2_mixer.lib" )

RPipe::RPipe(int x, int y) : Enemy(x, y)
{

	state.PushBack({ 1680, 384, 336, 144 });
	state.PushBack({ 1680, 816, 336, 144 });
	state.PushBack({ 1680, 672, 336, 144 });
	state.speed = 1.0f;
	state.loop = false;


	collider = App->collision->AddCollider({ x, y, 144, 144 }, COLLIDER_TYPE::COLLIDER_ENEMY, (Module*)App->enemies);

}


void RPipe::Draw(SDL_Texture* sprites)
{
	App->render->Blit(sprites, position.x, position.y, &(state.ConsultCurrentFrame()));
}


void RPipe::Collision()
{
	this_call = SDL_GetTicks();

	if (this_call > next_call)
	{
		if (state.Finished() != 1)
		{
			App->particles->AddParticle(App->particles->explosion, position.x, position.y + 40);
			App->particles->AddParticle(App->particles->explosion, position.x + 48, position.y);
			next_call = this_call + 200;
		}
		if (state.Finished())
		{
			isDead = true;
		}

		else
			state.GetCurrentFrame();
	}
}