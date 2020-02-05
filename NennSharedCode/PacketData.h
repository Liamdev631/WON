#pragma once
#include "vec.h"
#include <string>
#include "Entity.h"
#include <json.hpp>

using namespace std;
using namespace nlohmann;

struct entity_description
{
	char name[EntityNameLength];
	float x;
	float y;
	Entity::UID uid;
};

void to_json(json& j, const entity_description& p)
{
	j = json{
		{"name", p.name },
		{"x", p.x },
		{"y", p.y },
		{"uid", p.uid}
	};
}

void from_json(const json& j, entity_description& p)
{
	j.at("name").get_to(p.name);
	j.at("x").get_to(p.x);
	j.at("y").get_to(p.y);
	j.at("uid").get_to(p.uid);
}
