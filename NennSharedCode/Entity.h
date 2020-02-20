#pragma once
#include "vec.h"

constexpr unsigned int EntityNameLength = 32;

struct Entity
{
	char name[EntityNameLength];
	vec2f lastPosition;
	vec2f position;
	bool active;

	typedef unsigned int UID;

	Entity();
};
