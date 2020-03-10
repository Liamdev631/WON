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
	params.AntiAlias = 16;
	params.Fullscreen = false;
	params.DriverType = EDT_OPENGL;
	params.Vsync = true;
	params.DeviceType = EIDT_BEST;
	params.Doublebuffer = true;
	params.Bits = 24;
	params.Stencilbuffer = ShadowsEnabled;
	params.EventReceiver = &_client->component_input->input;
	params.WindowSize = { 1366, 768 };
	_device = createDeviceEx(params);
	if (!_device)
		return;

	_driver = _device->getVideoDriver();
	_sceneManager = _device->getSceneManager();
	_gui = _device->getGUIEnvironment();

	_terrain = new TerrainComponent(_sceneManager->getRootSceneNode(), _sceneManager);
	_lighting = new Lighting(_sceneManager->getRootSceneNode(), _sceneManager);
	_water = new Water(_sceneManager->getRootSceneNode(), _sceneManager);

	_device->getCursorControl()->setVisible(false);
	_device->setWindowCaption(L"World of Nenn");
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
	if (!_device->isWindowActive())
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

IVideoDriver* GraphicsComponent::getDriver() const
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
