#pragma once
#include <Irrlicht\irrlicht.h>
#include "ClientComponent.h"


using namespace irr;
using namespace core;
using namespace scene;
using namespace video;
using namespace io;
using namespace gui;

class GameClient;
class TerrainComponent;
class Water;
class Lighting;
class Input;

class GraphicsComponent : public ClientComponent
{
private:
	IrrlichtDevice* _device;
	IVideoDriver* _driver;
	ISceneManager* _sceneManager;
	IGUIEnvironment* _gui;

	TerrainComponent* _terrain;
	Water* _water;
	Lighting* _lighting;



public:
	GraphicsComponent(const GameClient* client);
	~GraphicsComponent();

	void preTick() override;
	void tick() override;
	void postTick() override;

	IrrlichtDevice* getDevice() const;
	IVideoDriver* getDriver() const;
	ISceneManager* getSceneManager() const;
	IGUIEnvironment* getGUI() const;

	TerrainComponent* getTerrainComponent() const;
	Water* getWater() const;
	Lighting* getLighting() const;
};

