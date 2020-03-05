#include "MovementComponent.h"
#include "EntityComponent.h"
#include "NetworkComponent.h"
#include "GameServer.h"
#include "Settings.h"
#include <json.hpp>
#include <iostream>

using namespace nlohmann;

MovementComponent::MovementComponent(const GameServer* server)
	: ServerComponent(server), _movementBoundaries({})
{
	return;
	// Load the movement boundaries from a json file
	FILE* file;
	char buffer[512];
	const char* filename = "Content/data/npc-movement-boundaries.json";
	fopen_s(&file, filename, "r");
	if (!file)
	{
		printf("MovementComponent: Failed to open %s!\n", filename);
		return;
	}
	size_t bytesRead = fread_s(buffer, 512, sizeof(char), 512 / sizeof(char), file);

	string jString = string(buffer, bytesRead);
	json j = json::parse(jString);

	auto arr = j["npc-movement-boundaries"];
	assert(arr.is_array());
	for (auto& elem : arr)
	{
		Entity::UID uid = arr.get<Entity::UID>();
	}
}

MovementComponent::~MovementComponent()
{

}

void MovementComponent::preTick()
{
	for (auto uid : _server->component_entity->getActiveEntities())
	{
		auto& entity = _server->component_entity->getEntity(uid);
		entity.lastPosition = entity.position;
	}
}

void MovementComponent::tick()
{
	// Detect speed hacks
	if (EnableSpeedHackDetection)
	{
		for (auto uid : _server->component_entity->getActiveEntities())
		{
			auto& entity = _server->component_entity->getEntity(uid);
			vec2f moveDelta = entity.position - entity.lastPosition;
			if (moveDelta.length() > MaxSpeed * 1.1f)
			{
				moveDelta.normalize();
				moveDelta = moveDelta * MaxSpeed;
				entity.position = entity.lastPosition + moveDelta;
				_server->component_entity->setEntityUpdateFlag(uid);
			}
		}
	}

	// Test move
	if (true)
	{
		for (Entity::UID uid : _server->component_entity->getActiveEntities())
		{
			if (_server->component_entity->isPlayer(uid))
				continue;
			auto& entity = _server->component_entity->getEntity(uid);
			static float time;
			time += 0.01f;
			entity.position.x += cos(time * 0.3f + uid) * 0.05f;
			entity.position.y += sin(time * 0.3f + uid) * 0.05f;
			_server->component_entity->setEntityUpdateFlag(uid);
		}
	}
}

void MovementComponent::postTick()
{

}
