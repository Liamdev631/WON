#pragma once
#include "ClientComponent.h"
#include <Irrlicht\irrlicht.h>

using namespace irr;
using namespace core;
using namespace scene;
using namespace video;
using namespace io;
using namespace gui;

class GameClient;

class GraphicsComponent : public ClientComponent
{
private:
	IrrlichtDevice* _device;
	IVideoDriver* _driver;
	ISceneManager* _sceneManager;
	IGUIEnvironment* _gui;

public:
	GraphicsComponent(const GameClient* client);
	~GraphicsComponent();

	void preTick() override;
	void tick() override;
	void postTick() override;
};

