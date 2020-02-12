#pragma once
#include "Settings.h"
#include "Entity.h"
#include "ServerComponent.h"
#include <array>
#include <set>

using namespace std;

class EntityComponent : public ServerComponent
{
private:
	// The table of all Entities.
	EntityTable<Entity> _entityTable;

	// Update flags. If the flag is set, the entity's new status
	// should be sent to nearby players.
	EntityTable<bool> _entityUpdateFlags;

	// Timeout counters. If the counter reacher 0, remove the
	// player from the server.
	PlayerTable<unsigned int> _timeoutTable;

	set<Entity::UID> _activeEntities;
	set<Entity::UID> _activePlayers;

public:
	EntityComponent(const GameServer* server);
	~EntityComponent() = default;

	// Entity information functions
	Entity& getEntity(Entity::UID uid);
	set<Entity::UID> getActiveEntities() const;
	set<Entity::UID> getActivePlayers() const;
	bool isEntityActive(Entity::UID uid);
	bool isPlayer(Entity::UID uid) const;
	
	// Entity management functions
	Entity& initializePlayer(Entity::UID uid);
	Entity::UID grabNextAvailableNPC();
	void removeEntity(Entity::UID uid);
	void broadcastEntityUpdate(Entity::UID uid);
	
	// Network functions
	void sendPlayerUID(Entity::UID uid);
	void sendEntityUpdateToPlayer(Entity::UID from, Entity::UID to);

	void clearUpdateFlags();
	void setEntityUpdateFlag(Entity::UID uid);

	// ServerComponent virtual functions
	void preTick() override;
	void tick() override;
	void postTick() override;
};
