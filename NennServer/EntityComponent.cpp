#include "EntityComponent.h"
#include "GameServer.h"
#include "NetworkComponent.h"
#include <assert.h>
#include "json.hpp"
#include "NPCLoader.h"

using namespace nlohmann;

EntityComponent::EntityComponent(const GameServer* server)
	: ServerComponent(server)
{
	for (unsigned int i = 0; i < NumberOfPlayers; i++)
		_timeoutTable[i] = 0;
	clearUpdateFlags();

	NPCLoader::loadNCPs(this);

	// Move the NPCs to random positions for now
	for (Entity::UID uid = NumberOfPlayers; uid < NumberOfEntities; uid++)
	{
		Entity& entity = getEntity(uid);
		if (!entity.active)
			continue;
		entity.position.x = 256 + (rand() % 500) / 100.0f;
		entity.position.y = 256 + (rand() % 500) / 100.0f;
	}
}

void EntityComponent::clearUpdateFlags()
{
	for (unsigned int i = 0; i < NumberOfEntities; i++)
		_entityUpdateFlags[i] = false;
}

Entity& EntityComponent::getEntity(Entity::UID uid)
{
	return _entities[uid];
}

bool EntityComponent::isEntityActive(Entity::UID uid)
{
	return getEntity(uid).active;
}

set<Entity::UID> EntityComponent::getActiveEntities() const
{
	return _activeEntities;
}

set<Entity::UID> EntityComponent::getActivePlayers() const
{
	return _activePlayers;
}

Entity::UID EntityComponent::grabNextAvailableNPC()
{
	Entity::UID uid = NumberOfPlayers; // Normal entities come after players
	while (_entities[uid].active) { uid++; }
	assert(uid < _entities.size());
	_activeEntities.emplace(uid);
	Entity& entity = _entities[uid];
	entity.active = true;

	return uid;
}

Entity& EntityComponent::initializePlayer(Entity::UID uid)
{
	assert(uid < NumberOfPlayers);
	_activeEntities.emplace(uid);
	_activePlayers.emplace(uid);
	Entity& entity = _entities[uid];
	entity.active = true;
	entity.type = EntityType::Player;
	entity.position.x = 256 + float(rand() % 5);
	entity.position.y = 256 + float(rand() % 5);
	return entity;
}

void EntityComponent::removeEntity(Entity::UID uid)
{
	auto& entity = _entities[uid];

	// build json
	json msg;
	msg["message"] = "entity-removed";
	msg["uid"] = uid;
	_server->component_network->connections.sendJson(msg, getActivePlayers());

	entity.active = false;
	_activeEntities.erase(uid);
	if (isPlayer(uid))
		_activePlayers.erase(uid);
}

void EntityComponent::broadcastEntityUpdate(Entity::UID uid)
{
	if (isPlayer(uid))
	{
		// Tell the player about all nearby entities, including itself
		for (Entity::UID entity : getActiveEntities())
			sendEntityUpdateToPlayer(entity, uid);
	}

	// Tell nearby players about this entity
	for (Entity::UID player : getActivePlayers())
		if (player != uid)
			sendEntityUpdateToPlayer(player, uid);
}

bool EntityComponent::isPlayer(Entity::UID uid) const
{
	return uid < NumberOfPlayers;
}

void EntityComponent::preTick()
{
	clearUpdateFlags();
}

void EntityComponent::tick()
{
	// Remove timed-out players
	if (EnableConnectionTimeout)
	{
		for (Entity::UID uid = 0; uid < NumberOfPlayers; uid++)
			if (_server->component_network->connections.status[uid] == ConnectionStatus::Reconnecting)
				if (_timeoutTable[uid]-- == 0)
					removeEntity(uid);
	}
}

void EntityComponent::postTick()
{
	for (Entity::UID entity : getActiveEntities())
	{
		// If the entities update flag was set, nearby players need to be sent an entity-update packet
		if (_entityUpdateFlags[entity])
		{
			for (Entity::UID player : getActivePlayers())
			{
				sendEntityUpdateToPlayer(entity, player);
				//printf("from:%u to:%u\n", entity, player);
			}
		}
	}
}

void EntityComponent::sendPlayerUID(Entity::UID uid)
{

}

void EntityComponent::setEntityUpdateFlag(Entity::UID uid)
{
	_entityUpdateFlags[uid] = true;
}

void EntityComponent::sendEntityUpdateToPlayer(Entity::UID from, Entity::UID to)
{
	assert(isPlayer(to));

	auto& entity = _entities[from];

	json msg;
	msg["message"] = "entity-update";
	msg["uid"] = from;
	msg["x"] = entity.position.x;
	msg["y"] = entity.position.y;
	_server->component_network->connections.sendJson(msg, to);
}
