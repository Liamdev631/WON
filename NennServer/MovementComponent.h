#pragma once
#include "ServerComponent.h"
#include "Settings.h"
#include "Entity.h"
#include <array>

using namespace std;

class MovementComponent : public ServerComponent
{
private:
	EntityTable<rect2f> _movementBoundaries;

public:
	MovementComponent(const GameServer* server);
	~MovementComponent();

	void preTick() override;
	void tick() override;
	void postTick() override;
};

