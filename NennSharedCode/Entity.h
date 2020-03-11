#pragma once
#include "vec.h"

constexpr unsigned int EntityNameLength = 32;

enum struct EntityType : unsigned short
{
	Player = 0,
	GreenSlime = 1,
	RedSlime = 2,
	Goblin = 3,
};

struct Entity
{
	char name[EntityNameLength];
	vec2f lastPosition;
	vec2f position;
	EntityType type;
	bool active;

	typedef unsigned int UID;

	Entity();
};
