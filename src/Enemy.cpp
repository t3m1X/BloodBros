#include "Application.h"
#include "Enemy.h"
#include "ModuleCollision.h"
#include "ModuleRender.h"
#include "ModuleParticles.h"

Enemy::Enemy(int x, int y) : position(x, y), collider(nullptr)
{}

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
	App->particles->AddParticle(App->particles->explosion, position.x, position.y);
	isDead = true;
}
