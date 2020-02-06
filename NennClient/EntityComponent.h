#pragma once
#include "ClientComponent.h"
#include <Settings.h>
#include <Entity.h>
#include <map>
#include <memory>
#include <set>
#include "EntityModel.h"

using namespace std;

class EntityComponent : public ClientComponent
{
private:
	std::map<Entity::UID, Entity> _entityTable;
	set<Entity::UID> _activeEntities;
	std::map<Entity::UID, unique_ptr<EntityModel>> _entityModels;
	
public:

	EntityComponent(const GameClient* client);
	~EntityComponent();

	void preTick() override;
	void tick() override;
	void postTick() override;

	Entity& getEntity(Entity::UID entity);
	void removeEntity(Entity::UID entity);

	const set<Entity::UID>& getActiveEntities() const;
};
