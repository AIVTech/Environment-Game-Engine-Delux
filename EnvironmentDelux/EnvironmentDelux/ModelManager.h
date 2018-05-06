#ifndef MODELMANAGER_H
#define MODELMANAGER_H

#include "StaticModel.h"
#include "StaticLoader.h"

class ModelManager
{
public:
	ModelManager(StaticLoader loader);

	StaticModel Stall;
	StaticModel Farmhouse;
	StaticModel Pine;

private:
	void LoadModels();
	StaticLoader loader;
};

#endif // !MODELMANAGER_H