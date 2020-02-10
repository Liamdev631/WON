#pragma once
#include "ClientComponent.h"
#include <Entity.h>

constexpr Entity::UID NO_UID = UINT32_MAX;
class EntityModel;

class GameStateComponent : public ClientComponent
{
public:
	Entity::UID thisPlayersUID;
	EntityModel* thisPlayersModel;

	GameStateComponent(const GameClient* client);
	~GameStateComponent();

	void preTick() override;
	void tick() override;
	void postTick() override;
};
