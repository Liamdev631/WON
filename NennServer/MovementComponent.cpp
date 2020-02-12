#include "MovementComponent.h"
#include "EntityComponent.h"
#include "NetworkComponent.h"
#include "GameServer.h"
#include "Settings.h"
#include <json.hpp>

using namespace nlohmann;

MovementComponent::MovementComponent(const GameServer* server)
	: ServerComponent(server)
{

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
	/*for (Entity::UID uid : _server->component_entity->getActiveEntities())
	{
		auto& entity = _server->component_entity->getEntity(uid);
		static float time;
		time += 0.01f;
		entity.position.x = 316 + cos(time * 5.0f + uid) * 1.0f;
		entity.position.y = 316 + sin(time * 5.0f + uid) * 1.0f;
		_server->component_entity->setEntityUpdateFlag(uid);
	}*/
}

void MovementComponent::postTick()
{

}
