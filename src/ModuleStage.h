#ifndef __MODULESTAGE_H__
#define __MODULESTAGE_H__

#include "Module.h"

class ModuleStage : public Module
{
public:

	ModuleStage();
	~ModuleStage();

	bool Start();
	update_status Update();
	bool CleanUp();

public:

	SDL_Texture* StageScreen = nullptr;
};


#endif //__MODULESTAGE_H__