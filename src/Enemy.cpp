#include "Application.h"
#include "Enemy.h"
#include "ModuleCollision.h"
#include "ModuleRender.h"
#include "ModuleParticles.h"
#include "ModuleUserI.h"

Enemy::Enemy(int x, int y) : position(x, y), collider(nullptr)
{
	state = ST_REGULAR;
}

Enemy::~Enemy()
{
	if (collider != nullptr)
		App->collision->EraseCollider(collider);
}

const Collider* Enemy::GetCollider() const
{
	return collider;
}

void Enemy::Draw(SDL_Texture* sprites)
{
	animation->GetCurrentFrame();
	if (collider != nullptr)
	{
		collider->SetPos(position.x, position.y);
		collider->SetSize(animation->ConsultCurrentFrame().w, animation->ConsultCurrentFrame().h);
	}

	App->render->Blit(sprites, position.x, position.y, &(animation->ConsultCurrentFrame()));
}

void Enemy::Collision()
{
	if (collider != nullptr)
	{
		App->collision->EraseCollider(collider);
		collider = nullptr;
	}
	App->useri->score += 100;
	App->useri->killcount += 1;
	state = ST_DYING;
}
