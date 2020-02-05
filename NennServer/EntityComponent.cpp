#include "EntityComponent.h"
#include "GameServer.h"
#include "NetworkComponent.h"
#include <assert.h>
#include "json.hpp"

using namespace nlohmann;

EntityComponent::EntityComponent(const GameServer* server)
	: ServerComponent(server)
{
	for (unsigned int i = 0; i < NumberOfPlayers; i++)
		_timeoutTable[i] = 0;
	clearUpdateFlags();
}

void EntityComponent::clearUpdateFlags()
{
	for (unsigned int i = 0; i < NumberOfEntities; i++)
		_entityUpdateFlags[i] = false;
}

Entity& EntityComponent::getEntity(Entity::UID uid)
{
	return _entityTable[uid];
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
	while (_entityTable[uid].active) { uid++; }
	assert(uid < _entityTable.size());
	_activeEntities.emplace(uid);
	Entity& entity = _entityTable[uid];
	entity.active = true;

	return uid;
}

void EntityComponent::grabNextAvailablePlayer(Entity::UID uid)
{
	assert(uid < NumberOfPlayers);
	_activeEntities.emplace(uid);
	_activePlayers.emplace(uid);
	Entity& entity = _entityTable[uid];
	entity.active = true;
}

void EntityComponent::onEntityRemoved(Entity::UID uid)
{
	_entityTable[uid].active = false;
	_activeEntities.erase(uid);
	if (isPlayer(uid))
		_activePlayers.erase(uid);
}

void EntityComponent::onEntityAdded(Entity::UID uid)
{
	if (isPlayer(uid))
	{
		// Tell the player about all nearby entities, including itself
		for (Entity::UID entity : _server->component_entity->getActiveEntities())
			sendEntityUpdateToPlayer(entity, uid);
	}

	// Tell nearby players about this entity
	for (Entity::UID player : _server->component_entity->getActivePlayers())
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
					onEntityRemoved(uid);
	}
}

void EntityComponent::postTick()
{
	for (Entity::UID entity : getActiveEntities())
	{
		// If the entities update flag was set, nearby players need to be sent an entity-update packet
		if (_entityUpdateFlags[entity])
		{
			for (Entity::UID player : _activePlayers)
				sendEntityUpdateToPlayer(entity, player);
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
	auto entity = _entityTable[from];

	// build json
	json msg;
	msg["message"] = "entity-update";
	msg["uid"] = from;
	msg["x"] = entity.position.x;
	msg["y"] = entity.position.y;
	
	// send json through packet
	sf::Packet packet;
	packet << msg.dump();
	_server->component_network->connections.socket[to].send(packet);
}
