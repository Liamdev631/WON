#pragma once
#include "ServerComponent.h"
#include "Settings.h"
#include <array>
#include "Entity.h"

using namespace std;

class MovementComponent : public ServerComponent
{
private:

public:
	MovementComponent(const GameServer* server);
	~MovementComponent();

	void preTick() override;
	void tick() override;
	void postTick() override;
};

