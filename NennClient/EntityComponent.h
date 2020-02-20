#pragma once
#include "ClientComponent.h"
#include <Settings.h>
#include <Entity.h>
#include <map>
#include <memory>
#include <set>

using namespace std;

class EntityModel;

class EntityComponent : public ClientComponent
{
private:
	std::map<Entity::UID, Entity> _entities;
	std::map<Entity::UID, EntityModel*> _entityModels;
	set<Entity::UID> _activeEntities;
	
public:

	EntityComponent(const GameClient* client);
	~EntityComponent();

	void preTick() override;
	void tick() override;
	void updateThisPlayer();
	void postTick() override;

	Entity& getEntity(Entity::UID uid);
	void removeEntity(Entity::UID uid);
	EntityModel* getEntityModel(Entity::UID uid);

	const set<Entity::UID>& getActiveEntities() const;
};
