#ifndef __MODULEEND_H__
#define __MODULEEND_H__

#include "Module.h"
#include "Animation.h"
#include "p2Point.h"

class ModuleEnd : public Module
{
public:

	ModuleEnd();
	~ModuleEnd();

	bool Start();
	update_status Update();
	bool CleanUp();

public:

	SDL_Texture* EndScreen = nullptr;
	SDL_Rect back;
};


#endif //__MODULEEND_H__