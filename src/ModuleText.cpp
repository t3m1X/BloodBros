#include "Globals.h"
#include "Application.h"
#include "ModuleText.h"
#include "ModuleRender.h"
#include "ModuleTextures.h"

void Text::Draw()
{
	char* text = _text;
	int letter = 0;
	SDL_Rect* position;
	position->w = TILE;
	position->h = TILE;
	while (text != '\0')
	{
		if (*text >= ' ' && *text <= '&')
		{
			position->y = ((*text - ' ') / 15) * TILE;
			position->x = ((*text - ' ') % 15) * TILE;
		}

		App->render->Blit(_font, _x + letter * TILE, _y, position);
		letter++;
		text++;
	}
}

ModuleText::ModuleText()
{
}

bool ModuleText::Start()
{
	uitexture = App->textures->Load("sprites/ui-rearranged.png");
	for (int i = 0; i < MAX_TEXT; ++i)
		texts[i] = nullptr;

	return true;
}

update_status ModuleText::Update()
{
	for (int i = 0; i < MAX_TEXT; ++i)
	{
		if (texts[i] != nullptr)
			texts[i]->Draw();
	}
}

bool ModuleText::CleanUp()
{
	LOG("Freeing all texts");

	for (uint i = 0; i < MAX_TEXT; ++i)
	{
		if (texts[i] != nullptr)
		{
			delete texts[i];
			texts[i] = nullptr;
		}
	}

	return true;
}

Text* ModuleText::AddText(int x, int y, char* text)
{
	Text* ret = nullptr;

	for (uint i = 0; i < MAX_TEXT; ++i)
	{
		if (texts[i] == nullptr)
		{
			ret = texts[i] = new Text(x, y, text, uitexture);
			break;
		}
	}

	return ret;
}

Text* ModuleText::AddNumber(int x, int y, int number, int size, char default_char = '0')
{
	Text* ret = nullptr;
	char* text = new char[size];
	while (number > 0)
	{
		text[size-- - 1] = '0' + number % 10;
		number /= 10;
	}

	for (int i = 0; i < size; ++i)
		text[i] = default_char;

	for (uint i = 0; i < MAX_TEXT; ++i)
	{
		if (texts[i] == nullptr)
		{
			ret = texts[i] = new Text(x, y, text, uitexture);
			break;
		}
	}

	delete text;
	return ret;
}

bool ModuleText::EraseText(Text* text)
{
	for (uint i = 0; i < MAX_TEXT; ++i)
	{
		if (texts[i] == text)
		{
			delete texts[i];
			texts[i] = nullptr;
			return true;
		}
	}

	return false;
}