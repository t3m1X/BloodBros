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
}

ModuleParticles::~ModuleParticles()
{}

// Load assets
bool ModuleParticles::Start()
{
	LOG("Loading particles");
	graphics = App->textures->Load("sprites/explosives_1.png");

	// Explosion particle
	explosion.anim.PushBack({186, 338, 192, 192});
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
	bomb.anim.speed = 0.3f;

	shoot.anim.PushBack({ 832, 39, 27, 27 });
	shoot.anim.PushBack({ 870, 39, 27, 27 });
	shoot.anim.speed = 0.3f;

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
	for(uint i = 0; i < MAX_ACTIVE_PARTICLES; ++i)
	{
		Particle* p = active[i];

		if(p == nullptr)
			continue;

		if(p->Update() == false)
		{
			delete p;
			active[i] = nullptr;
		}
		else if(SDL_GetTicks() >= p->born)
		{
			App->render->Blit(graphics, p->position.x, p->position.y, &(p->anim.GetCurrentFrame()));
			if(p->fx_played == false)
			{
				p->fx_played = true;
				// Play particle fx here
			}
		}
	}

	return UPDATE_CONTINUE;
}

void ModuleParticles::AddParticle(const Particle& particle, int x, int y, Uint32 delay)
{
	Particle* p = new Particle(particle);
	p->born = SDL_GetTicks() + delay;
	p->position.x = x;
	p->position.y = y;

	active[last_particle++] = p;
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

bool Particle::Update()
{
	bool ret = true;

	if(life > 0)
	{
		if((SDL_GetTicks() - born) > life)
			ret = false;
	}
	else
		if(anim.Finished())
			ret = false;

	position.x += speed.x;
	position.y += speed.y;

	return ret;
}