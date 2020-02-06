#pragma once
#include "ClientComponent.h"
#include <Entity.h>

constexpr Entity::UID NO_UID = UINT32_MAX;

class GameStateComponent : public ClientComponent
{
public:
	Entity::UID thisPlayersUID;

	GameStateComponent(const GameClient* client);
	~GameStateComponent();

	void preTick() override;
	void tick() override;
	void postTick() override;
};
