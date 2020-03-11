#pragma once
#include "Entity.h"
#include <Settings.h>

class EntityComponent;

class NPCLoader
{
public:
	static void loadNCPs(EntityComponent* entityComponent);
};
