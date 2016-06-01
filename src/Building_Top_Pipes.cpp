#include "Application.h"
#include "Building_Top_Pipes.h"
#include "Path.h"
#include "ModuleCollision.h"
#include "p2Point.h"
#include "ModuleParticles.h"
#include "ModuleRender.h"
#include "ModuleScene.h"
#include "ModuleUserI.h"

#include "SDL/include/SDL.h"
#pragma comment( lib, "SDL_mixer/libx86/SDL2_mixer.lib" )

Top_Pipes::Top_Pipes(int x, int y) : Enemy(x, y)
{
	state.PushBack({ 1680, 960, 528, 96 });
	state.PushBack({ 1680, 1152, 528, 96 });
	state.PushBack({ 1680, 1344, 528, 96 });
	state.speed = 1.0f;
	state.loop = false;

	dead_state.PushBack({ 1680, 1344, 528, 96 });
	dead_state.speed = 1.0f;


	collider = App->collision->AddCollider({ x+24, y, 475, 48 }, COLLIDER_TYPE::COLLIDER_ENEMY, (Module*)App->enemies);

}


void Top_Pipes::Draw(SDL_Texture* sprites)
{
	App->render->Blit(sprites, position.x, position.y, &(state.ConsultCurrentFrame()));
}


void Top_Pipes::Collision()
{
	this_call = SDL_GetTicks();

	if (this_call > next_call)
	{
		App->particles->AddParticle(App->particles->explosion, position.x, position.y - 30);
		App->particles->AddParticle(App->particles->explosion, position.x + 120 + 120 + 120, position.y - 30);
		App->particles->AddParticle(App->particles->explosion, position.x + 120 + 120, position.y - 30);
		App->particles->AddParticle(App->particles->explosion, position.x + 120, position.y - 30);
		next_call = this_call + 200;
		   
		if (state.Finished())
		{
			App->collision->EraseCollider(collider);

			App->scene->toppipe = false;

			App->useri->score += 400;
		}
		else
			state.GetCurrentFrame();
	}
}

void Top_Pipes::Move()
{
	if (state.Finished())
	{
		position.y += 7;
	}
	 if (position.y >= SCREEN_HEIGHT/2)
		isDead = true;

}