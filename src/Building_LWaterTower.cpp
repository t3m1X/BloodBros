#include "Application.h"
#include "Building_LWaterTower.h"
#include "Path.h"
#include "ModuleCollision.h"
#include "p2Point.h"
#include "ModuleParticles.h"
#include "ModuleRender.h"

LWaterTower::LWaterTower(int x, int y) : Enemy(x, y)
{
	state.PushBack({ 34, 1974, 22, 10 });
	state.PushBack({ 66, 1968, 43, 22 });
	state.PushBack({ 120, 1957, 85, 37 });

	state.speed = 1.0f;
	state.loop = false;

	collider = App->collision->AddCollider({ x, y, 32, 16 }, COLLIDER_TYPE::COLLIDER_ENEMY, (Module*)App->enemies);

}


void LWaterTower::Draw(SDL_Texture* sprites)
{
	App->render->Blit(sprites, position.x, position.y, &(state.ConsultCurrentFrame()));
}
