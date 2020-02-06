#pragma once
#include "ClientComponent.h"
#include <Irrlicht\IEventReceiver.h>

using namespace irr;

class UserInputComponent : public ClientComponent, IEventReceiver
{
private:


public:
	bool OnEvent(const SEvent& event) override;

	UserInputComponent(const GameClient* client);
	~UserInputComponent();

	void preTick() override;
	void tick() override;
	void postTick() override;
};

