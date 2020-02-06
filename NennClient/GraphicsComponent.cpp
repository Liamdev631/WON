#include "GraphicsComponent.h"
#include "GameClient.h"

GraphicsComponent::GraphicsComponent(const GameClient* client)
	: ClientComponent(client), _device(nullptr), _driver(nullptr), _sceneManager(nullptr), _gui(nullptr)
{
	SIrrlichtCreationParameters params;
	params.AntiAlias = 8;
	params.Fullscreen = false;
	params.DriverType = EDT_OPENGL;
	_device = createDevice(video::EDT_OPENGL, dimension2d<u32>(640, 480), 16, false, false, false, 0);
	if (!_device)
		return;
	_device->setWindowCaption(L"World of Nenn");
	_driver = _device->getVideoDriver();
	_sceneManager = _device->getSceneManager();
	_gui = _device->getGUIEnvironment();

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
