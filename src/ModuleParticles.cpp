#include <math.h>
#include "Globals.h"
#include "Application.h"
#include "ModuleTextures.h"
#include "ModuleRender.h"
#include "ModuleParticles.h"

#include "SDL/include/SDL_timer.h"

ModuleParticles::ModuleParticles()
{
	for(uint i = 0; i < MAX_ACTIVE_PARTICLES; ++i)
		active[i] = nullptr;

	// Explosion particle
	explosion.anim.PushBack({ 186, 338, 192, 192 });
	explosion.anim.PushBack({ 390, 338, 192, 192 });
	explosion.anim.PushBack({ 593, 341, 192, 192 });
	explosion.anim.loop = false;
	explosion.anim.speed = 0.3f;

	bomb.anim.PushBack({ 854, 283, 17, 21 });
	bomb.anim.PushBack({ 808, 283, 15, 24 });
	bomb.anim.PushBack({ 754, 280, 24, 30 });
	bomb.anim.PushBack({ 700, 280, 33, 27 });
	bomb.anim.PushBack({ 649, 280, 33, 27 });
	bomb.anim.PushBack({ 595, 274, 36, 36 });
	bomb.anim.PushBack({ 544, 271, 30, 42 });
	bomb.anim.PushBack({ 493, 268, 36, 48 });
	bomb.anim.loop = false;
	bomb.speed.y = 5;
	bomb.speed.x = -1;
	bomb.anim.speed = 0.3f;
	bomb.life = 5000;

	shoot.anim.PushBack({ 832, 70, 20, 20 });
	shoot.anim.PushBack({ 861, 70, 20, 20 });
	shoot.anim.speed = 0.3f;
	shoot.speed.y = 5;
	shoot.life = 2000;

	shoot_right.anim.PushBack({ 832, 70, 20, 20 });
	shoot_right.anim.PushBack({ 861, 70, 20, 20 });
	shoot_right.anim.speed = 0.3f;
	shoot_right.speed.y = 5;
	shoot_right.speed.x = 5;
	shoot_right.life = 2000;

	shoot_left.anim.PushBack({ 832, 70, 20, 20 });
	shoot_left.anim.PushBack({ 861, 70, 20, 20 });
	shoot_left.anim.speed = 0.3f;
	shoot_left.speed.y = 5;
	shoot_left.speed.x = -5;
	shoot_left.life = 2000;

	bullet_collision.anim.PushBack({24,54,54,42});
	bullet_collision.anim.PushBack({ 117, 48, 78, 48 });
	bullet_collision.anim.PushBack({ 205, 21, 90, 75 });
	bullet_collision.anim.loop = false;
	bullet_collision.anim.speed = 0.3f;
}

ModuleParticles::~ModuleParticles()
{}

// Load assets
bool ModuleParticles::Start()
{
	LOG("Loading particles");
	graphics = App->textures->Load("sprites/explosives_1.png");

	return true;
}

// Unload assets
bool ModuleParticles::CleanUp()
{
	LOG("Unloading particles");
	App->textures->Unload(graphics);

	for(uint i = 0; i < MAX_ACTIVE_PARTICLES; ++i)
	{
		if(active[i] != nullptr)
		{
			delete active[i];
			active[i] = nullptr;
		}
	}

	return true;
}

// Update: draw background
update_status ModuleParticles::Update()
{
	for (uint i = 0; i < MAX_ACTIVE_PARTICLES; ++i)
	{
		Particle* p = active[i];

		if (p == nullptr)
			continue;

		if (p->Update() == false)
		{
			delete p;
			active[i] = nullptr;
		}
		else if (SDL_GetTicks() >= p->born)
		{
			App->render->Blit(graphics, p->position.x, p->position.y, &(p->anim.GetCurrentFrame()));
			if (p->fx_played == false)
			{
				p->fx_played = true;
				//play particle fx here
			}
		}
	}

	return UPDATE_CONTINUE;
}

void ModuleParticles::AddParticle(const Particle& particle, int x, int y, COLLIDER_TYPE collider_type, Uint32 delay)
{
	for (uint i = 0; i < MAX_ACTIVE_PARTICLES; ++i)
	{
		if (active[i] == nullptr)
		{
			Particle* p = new Particle(particle);
			p->born = SDL_GetTicks() + delay;
			p->position.x = x;
			p->position.y = y;
			if (collider_type != COLLIDER_NONE)
				p->collider = App->collision->AddCollider(p->anim.GetCurrentFrame(), collider_type, this);
			active[i] = p;
			break;
		}
	}
}

void ModuleParticles::OnCollision(Collider* c1, Collider* c2)
{
	for (uint i = 0; i < MAX_ACTIVE_PARTICLES; ++i)
	{
		// Always destroy particles that collide
		if (active[i] != nullptr && active[i]->collider == c1)
		{
			AddParticle(bullet_collision, active[i]->position.x, active[i]->position.y);
			delete active[i];
			active[i] = nullptr;
			break;
		}
	}
}

// -------------------------------------------------------------
// -------------------------------------------------------------

Particle::Particle()
{
	position.SetToZero();
	speed.SetToZero();
}

Particle::Particle(const Particle& p) : 
anim(p.anim), position(p.position), speed(p.speed),
fx(p.fx), born(p.born), life(p.life)
{}

Particle::~Particle()
{
	if (collider != nullptr)
		App->collision->EraseCollider(collider);
}

bool Particle::Update()
{
	bool ret = true;

	if (life > 0)
	{
		if ((SDL_GetTicks() - born) > life)
			ret = false;
	}
	else
		if (anim.Finished())
			ret = false;

	position.x += speed.x;
	position.y += speed.y;

	if (collider != nullptr)
		collider->SetPos(position.x, position.y);

	return ret;
}