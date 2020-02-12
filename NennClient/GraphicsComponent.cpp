#include "GraphicsComponent.h"
#include "GameClient.h"
#include "TerrainComponent.h"
#include "Water.h"
#include "Lighting.h"
#include "GameStateComponent.h"
#include "EntityComponent.h"
#include "Input.h"

GraphicsComponent::GraphicsComponent(const GameClient* client)
	: ClientComponent(client), _device(nullptr), _driver(nullptr), _sceneManager(nullptr),
	_gui(nullptr), _terrain(nullptr), _lighting(nullptr), _water(nullptr)
{
	SIrrlichtCreationParameters params;
	params.AntiAlias = 8;
	params.Fullscreen = false;
	params.DriverType = EDT_OPENGL;
	_device = createDevice(video::EDT_OPENGL, dimension2d<u32>(640, 480), 24, false, false, true, &_client->component_input->input);
	if (!_device)
		return;
	_device->setWindowCaption(L"World of Nenn");
	_driver = _device->getVideoDriver();
	_sceneManager = _device->getSceneManager();
	_gui = _device->getGUIEnvironment();

	_terrain = new TerrainComponent(_sceneManager->getRootSceneNode(), _sceneManager);

	_water = new Water(_sceneManager->getRootSceneNode(), _sceneManager);

	_lighting = new Lighting(_sceneManager->getRootSceneNode(), _sceneManager);

	//_gui->addStaticText(L"Hello World! This is the Irrlicht Software renderer!", rect<s32>(10, 10, 260, 22), true);
}

GraphicsComponent::~GraphicsComponent()
{
	_device->drop();
}

void GraphicsComponent::preTick()
{

}

void GraphicsComponent::tick()
{
	// All the scene rendering happens here.
	if (!_device->run())
		return;
	_driver->beginScene(true, true, SColor(255, 0, 0, 255));
	_sceneManager->drawAll();
	_gui->drawAll();
	_driver->endScene();
}

void GraphicsComponent::postTick()
{
	
}

IrrlichtDevice* GraphicsComponent::getDevice() const
{
	return _device;
}

IVideoDriver* GraphicsComponent::getVideoDriver() const
{
	return _driver;
}

ISceneManager* GraphicsComponent::getSceneManager() const
{
	return _sceneManager;
}

IGUIEnvironment* GraphicsComponent::getGUI() const
{
	return _gui;
}

TerrainComponent* GraphicsComponent::getTerrainComponent() const
{
	return _terrain;
}

Water* GraphicsComponent::getWater() const
{
	return _water;
}

Lighting* GraphicsComponent::getLighting() const
{
	return _lighting;
}
