#include <math.h>
#include "Globals.h"
#include "Application.h"
#include "ModuleTextures.h"
#include "ModuleRender.h"
#include "ModuleParticles.h"
#include "ModulePlayer.h"

#include "SDL/include/SDL_timer.h"

ModuleParticles::ModuleParticles()
{
	for(uint i = 0; i < MAX_ACTIVE_PARTICLES; ++i)
		active[i] = nullptr;

	// Explosion particle
	explosion.anim.PushBack({ 0, 96, 144, 144 });
	explosion.anim.PushBack({ 144, 96, 144, 144 });
	explosion.anim.PushBack({ 288, 96, 144, 144 });
	explosion.anim.loop = false;
	explosion.anim.speed = 0.3f;

	bomb.anim.PushBack({ 576, 96, 48, 48 });
	bomb.anim.PushBack({ 624, 96, 48, 48 });
	bomb.anim.PushBack({ 672, 96, 48, 48 });
	bomb.anim.PushBack({ 720, 96, 48, 48 });
	bomb.anim.PushBack({ 768, 96, 48, 48 });
	bomb.anim.loop = false;
	bomb.speed.y = 5;
	bomb.speed.x = -1;
	bomb.anim.speed = 0.3f;
	bomb.life = 5000;

	bomb2.anim.PushBack({ 720, 240, 48, 48 });
	bomb2.anim.PushBack({ 672, 240, 48, 48 });
	bomb2.anim.PushBack({ 624, 240, 48, 48 });
	bomb2.anim.PushBack({ 576, 240, 48, 48 });
	bomb2.anim.PushBack({ 528, 240, 48, 48 });
	bomb2.anim.PushBack({ 480, 240, 48, 48 });
	bomb2.anim.PushBack({ 432, 240, 48, 48 });
	bomb2.anim.PushBack({ 384, 240, 48, 48 });
	bomb2.anim.loop = false;
	bomb2.anim.speed = 0.3f;
	bomb2.life = 5000;

	shoot.anim.PushBack({ 768, 0, 48, 48 });
	shoot.anim.PushBack({ 816, 0, 48, 48 });
	shoot.anim.speed = 0.3f;
	shoot.speed.y = 5;
	shoot.life = 2000;

	shoot_right.anim.PushBack({ 768, 0, 48, 48 });
	shoot_right.anim.PushBack({ 816, 0, 48, 48 });
	shoot_right.anim.speed = 0.3f;
	shoot_right.speed.y = 5;
	shoot_right.speed.x = 5;
	shoot_right.life = 2000;

	shoot_left.anim.PushBack({ 768, 0, 48, 48 });
	shoot_left.anim.PushBack({ 816, 0, 48, 48 });
	shoot_left.anim.speed = 0.3f;
	shoot_left.speed.y = 5;
	shoot_left.speed.x = -5;
	shoot_left.life = 2000;


	shoot_player.anim.PushBack({ 768, 0, 48, 48 });
	shoot_player.anim.PushBack({ 816, 0, 48, 48 });
	shoot_player.anim.speed = 0.3f;
	shoot_player.speed.y = 5;
	shoot_player.life = 2000;

	bullet_collision.anim.PushBack({ 0, 0, 96, 96 });
	bullet_collision.anim.PushBack({ 96, 0, 96, 96 });
	bullet_collision.anim.PushBack({ 192, 0, 96, 96 });
	bullet_collision.anim.loop = false;
	bullet_collision.anim.speed = 0.3f;

	dust.anim.PushBack({ 0, 480, 336, 144 });
	dust.anim.PushBack({ 336, 480, 336, 144 });
	dust.life = 7500;
	dust.anim.speed = 0.3f;

	end_dust.anim.PushBack({ 0, 624, 336, 144 });
	end_dust.anim.PushBack({ 336, 624, 336, 144 });
	end_dust.anim.PushBack({ 672, 624, 336, 144 });
	end_dust.anim.loop = false;
	end_dust.anim.speed = 0.3f;

	cactusboom.anim.PushBack({ 672, 528 , 96, 96});
	cactusboom.anim.PushBack({ 768, 528, 96, 96 });
	cactusboom.anim.PushBack({ 864, 528, 96, 96 });
	cactusboom.anim.loop = false;
	cactusboom.anim.speed = 0.1f;

	firearrow.anim.PushBack({ 768, 240, 48, 48 });
	firearrow.anim.PushBack({ 816, 240, 48, 48 });
	firearrow.anim.PushBack({ 864, 240, 48, 48 });
	firearrow.anim.PushBack({ 912, 240, 48, 96 });
	firearrow.anim.loop = false;
	firearrow.anim.speed = 0.1f;
	firearrow.life = 2000;
	firearrow.speed.y = 4;


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
	shoot_player.speed.x = (App->player->position.x - SCREEN_WIDTH / 2) / 20;

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
			//AddParticle(explosion, active[i]->position.x, active[i]->position.y);
			if (App->player->player_collider == c2)
				App->player->Collision();

			delete active[i];
			active[i] = nullptr;
			break;
		}
	}
}

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