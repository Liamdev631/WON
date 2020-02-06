#include "EntityComponent.h"
#include "GameClient.h"
#include "GraphicsComponent.h"

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
	for (auto& pair : _entityModels.)
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
		_entityModels[uid] = make_unique<EntityModel>(_client->component_graphics->getSceneManager());
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
