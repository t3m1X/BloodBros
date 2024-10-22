#include "Globals.h"
#include "Application.h"
#include "ModuleTextures.h"
#include "ModuleAudio.h"
#include "ModuleInput.h"
#include "ModuleRender.h"
#include "ModuleIntro.h"
#include "ModuleScene.h"
#include "ModuleFadeToBlack.h"
#include "ModuleText.h"
#include "ModuleUserI.h"

ModuleUserI::ModuleUserI()
{
	insert_coins.PushBack({ 137, 3, 200, 25 });
	insert_coins.PushBack({ 137, 230, 200, 25 });
	insert_coins.loop = true;
	insert_coins.speed = 0.1f;
	
	life_ball.PushBack({ 0, 288, 48, 48 });

	dynamite_image.PushBack({ 61, 298, 75, 75 });

	topbutt.PushBack({ 480, 288, 96, 48 });
	oneup.PushBack({ 576, 288, 96, 48 });

	foe.PushBack({ 165, 292, 150, 40 });
	foe_bar.PushBack({ 436, 292, 40, 40 });
	foe_bar.PushBack({ 390, 292, 40, 40 });
	foe_bar.PushBack({343, 292, 40, 40});

	hitpoints = 3;
	credit = 0;
	dynamite = 10;
	highscore = 0;


	
}
ModuleUserI::~ModuleUserI()
{
}
bool ModuleUserI::Start()
{
	LOG("Loading intro");

	UserInterface = App->textures->Load("sprites/ui-rearranged.png");
	credit_text = App->text->AddText(SCREEN_WIDTH/2 - 2*TILE,SCREEN_HEIGHT-TILE/2,"CREDIT");
	credit_counter = App->text->AddNumber(SCREEN_WIDTH / 2 + TILE/2 + 10, SCREEN_HEIGHT - TILE / 2, credit, 2);
	score_counter = App->text->AddNumber(0, 0, score, 8);
	dynamite_counter = App->text->AddNumber(0, SCREEN_HEIGHT - (TILE + TILE / 2) + 5, dynamite, 2);
	highscore_counter = App->text->AddNumber(TILE * 5, 0, highscore, 8);
	score = 0;
	killcount = 0;

	return true;
}
bool ModuleUserI::CleanUp()
{
	LOG("Unloading intro");

	App->textures->Unload(UserInterface);
	App->text->EraseText(credit_text);
	App->text->EraseText(credit_counter);
	App->text->EraseText(score_counter);
	App->text->EraseText(highscore_counter);
	App->text->EraseText(dynamite_counter);

	return true;
}
update_status ModuleUserI::Update()
{
	if (score > highscore)
		highscore = score;

	credit_counter->ChangeNumber(credit);
	score_counter->ChangeNumber(score);
	highscore_counter->ChangeNumber(highscore);

	int enemygauge = (ENEMY_GAUGE - killcount) / 2;
	
	if (enemygauge == 0 && killcount > ENEMY_GAUGE)
		enemygauge = 1;

	if (enemygauge < 0)
		enemygauge = 0;

	App->render->Blit(UserInterface, TILE * 2, SCREEN_HEIGHT - (TILE), &(foe.GetCurrentFrame()), 0.5);

	Uint32 position = TILE * 2 + 80;
	Uint32 count = 0;
	while (enemygauge - 2 >= 0)
	{
		App->render->Blit(UserInterface, position, SCREEN_HEIGHT - (TILE), &(foe_bar.frames[2]), 0.5);
		enemygauge -= 2;
		position += 20;
		++count;
	}

	while (enemygauge % 2 == 1)
	{
		App->render->Blit(UserInterface, position, SCREEN_HEIGHT - (TILE), &(foe_bar.frames[1]), 0.5);
		enemygauge--;
		position += 20;
		++count;
	}

	while (count < ENEMY_GAUGE / 4)
	{
		App->render->Blit(UserInterface, position, SCREEN_HEIGHT - (TILE), &(foe_bar.frames[0]), 0.5);
		position += 20;
		++count;
	}

	App->render->Blit(UserInterface, 0, SCREEN_HEIGHT - TILE*2 - 15, &(dynamite_image.GetCurrentFrame()),0.6);

	if (hitpoints >= 2)
	{
		App->render->Blit(UserInterface, 0, SCREEN_HEIGHT - (TILE), &(life_ball.GetCurrentFrame()), 0.6);
		if (hitpoints == 3)
			App->render->Blit(UserInterface, 23, SCREEN_HEIGHT - (TILE), &(life_ball.GetCurrentFrame()),0.6);
	}

	if (App->input->keyboard[SDL_SCANCODE_1] == KEY_STATE::KEY_DOWN)
		++credit;
	if (credit > 99)
		credit = 99;

	App->render->Blit(UserInterface, 190, 0, &(topbutt.GetCurrentFrame()), 0.6);


	/*
	App->render->Blit(UserInterface, SCREEN_WIDTH - SCREEN_WIDTH/3, SCREEN_HEIGHT - 25, &(insert_coins.GetCurrentFrame()));
	App->render->Blit(UserInterface, (SCREEN_WIDTH / 2) - 50, SCREEN_HEIGHT - 25, &credits, 1.0f);*/

	return UPDATE_CONTINUE;
}