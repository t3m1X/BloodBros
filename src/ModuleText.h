#ifndef __MODULETEXT_H__
#define __MODULETEXT_H__

#include "Module.h"
#define MAX_TEXT 16

struct SDL_Texture;

struct Text
{
	bool to_delete = false;
	int _x;
	int _y;
	char* _text;
	SDL_Texture* _font;

	Text(int x, int y, char* text, SDL_Texture* font) :
		_x(x),
		_y(y),
		_font(font)
	{
		int length = SDL_strlen(text);

		_text = new char[length + 1];

		for (int i = 0; i < length; ++i)
			_text[i] = text[i];

		_text[length] = '\0';
	}

	~Text()
	{
		delete _text;
		_text = nullptr;
	}

	void ChangeText(char* newtext)
	{
		_text = newtext;
	}

	void Draw();

};

class ModuleText : public Module
{
public:

	ModuleText();
	~ModuleText();

	bool Start();
	update_status Update();
	bool CleanUp();

	Text* AddText(int x, int y, char* text);
	Text* AddNumber(int x, int y, int number, unsigned int size, char default_char = '0');
	bool EraseText(Text* text);

public:

	Text* texts[MAX_TEXT];
	SDL_Texture* uitexture;
};


#endif //__MODULETEXT_H__