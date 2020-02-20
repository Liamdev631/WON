#include "EntityComponent.h"
#include "GameClient.h"
#include "GraphicsComponent.h"
#include "TerrainComponent.h"
#include "GameStateComponent.h"
#include "EntityModel.h"
#include <json.hpp>
#include "NetworkComponent.h"

using namespace nlohmann;

EntityComponent::EntityComponent(const GameClient* client)
	: ClientComponent(client)
{

}

EntityComponent::~EntityComponent()
{

}

void EntityComponent::preTick()
{

}

void EntityComponent::tick()
{
	updateThisPlayer();

	for (auto& uid : getActiveEntities())
		_entityModels[uid]->update();
}

void EntityComponent::updateThisPlayer()
{
	Entity::UID thisPlayersUID = _client->component_gameState->thisPlayersUID;
	if (thisPlayersUID == NO_UID)
		return;

	Entity& thisPlayer = getEntity(thisPlayersUID);
	EntityModel* thisPlayersModel = getEntityModel(thisPlayersUID);

	float dx = thisPlayer.position.x - thisPlayersModel->getPosition().X;
	float dy = thisPlayer.position.y - thisPlayersModel->getPosition().Z;
	float dist2 = dx * dx + dy * dy;
	printf("%f, %f\n", dx, dy);

	//if (thisPlayersModel->getPosition().X != thisPlayer.position.x ||
	//	thisPlayersModel->getPosition().Z != thisPlayer.position.y)
	if (dist2 > 0.001f)
	{
		static int UpdateCounter = 0;
		if (UpdateCounter++ == 6) // 10 times per second
		{
			UpdateCounter = 0;
			// If we moved the player, relay it to the server
			json j;
			j["message"] = "move-to-position";
			j["x"] = thisPlayersModel->getPosition().X;
			j["y"] = thisPlayersModel->getPosition().Z;
			_client->component_network->sendJson(j);
		}
	}
}

void EntityComponent::postTick()
{

}

Entity& EntityComponent::getEntity(Entity::UID uid)
{
	assert(uid != NO_UID);
	Entity& entity = _entities[uid];
	if (!entity.active)
	{
		// Setup the new entity
		entity.active = true;
		_activeEntities.emplace(uid);

		// Create the EntityModel for this entity
		auto smgr = _client->component_graphics->getSceneManager();
		_entityModels[uid] = new EntityModel(uid, _client, smgr->getRootSceneNode());
		_entityModels[uid]->drop();
	}
	return entity;
}

void EntityComponent::removeEntity(Entity::UID entity)
{
	_activeEntities.erase(entity);
	_entities.erase(entity);
	_entityModels.erase(entity);
}

const set<Entity::UID>& EntityComponent::getActiveEntities() const
{
	return _activeEntities;
}

EntityModel* EntityComponent::getEntityModel(Entity::UID uid)
{
	if (_activeEntities.find(uid) == _activeEntities.end())
		auto e = getEntity(uid); // TODO: This is bad
	return _entityModels[uid];
}
