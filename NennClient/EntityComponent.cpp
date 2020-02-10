#include "EntityComponent.h"
#include "GameClient.h"
#include "GraphicsComponent.h"
#include "TerrainComponent.h"
#include "EntityModel.h"

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
	for (auto& uid : _activeEntities)
	{
		auto& entityModel = _entityModels[uid];
		auto destination = _entityTable[uid].position;
		entityModel->setDestination(destination.x, destination.y);
		auto terrainNode = _client->component_graphics->getTerrainComponent()->getNode();

		// Set each characters height to the height of the terrain
		vector3df currentPos = entityModel->getPosition();
		float height = terrainNode->getHeight(currentPos.X, currentPos.Z);
		entityModel->setHeight(height);
	}
}

void EntityComponent::postTick()
{

}

Entity& EntityComponent::getEntity(Entity::UID uid)
{
	Entity& entity = _entityTable[uid];
	if (!entity.active)
	{
		// Setup the new entity
		entity.active = true;
		_activeEntities.emplace(uid);

		// Create the EntityModel for this entity
		auto smgr = _client->component_graphics->getSceneManager();
		_entityModels[uid] = new EntityModel(_client, smgr->getRootSceneNode());
		_entityModels[uid]->drop();
	}
	return entity;
}

void EntityComponent::removeEntity(Entity::UID entity)
{
	_activeEntities.erase(entity);
	_entityTable.erase(entity);
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

