#pragma once
#include "ClientComponent.h"
#include <Irrlicht\irrlicht.h>

using namespace irr;

class GUI : public ClientComponent
{
private:
	gui::IGUIEnvironment* _gui;
	gui::IGUIImage* _crosshair;

public:
	GUI(const GameClient* client);
	~GUI();

	void preTick() override;
	void tick() override;
	void postTick() override;
};

