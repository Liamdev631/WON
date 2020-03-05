#include "GUI.h"
#include "GameClient.h"
#include "GraphicsComponent.h"

GUI::GUI(const GameClient* client)
	: ClientComponent(client)
{
	_gui = _client->component_graphics->getGUI();
	if (!_gui)
	{
		printf("GUI: ERROR! GraphicsComponent must be initialized before GUI!\n");
		return;
	}

	auto driver = _client->component_graphics->getDriver();
	

	// Load the crosshair texture
	//driver->makeColorKeyTexture(_crosshairTexture, core::position2d<s32>(0, 0));
	auto rtSize = driver->getCurrentRenderTargetSize();
	vector2di center = { int(rtSize.Width / 2), int(rtSize.Height / 2) };

	recti crosshairBounds = recti(center.X - 16, center.Y - 16, center.X + 16, center.Y + 16);
	_crosshair = _gui->addImage(crosshairBounds);
	auto crosshairTexture = driver->getTexture("Content/gui/cursor.png");
	_crosshair->setImage(crosshairTexture);
}

GUI::~GUI()
{
	_crosshair->drop();
}

void GUI::preTick()
{

}

void GUI::tick()
{

}

void GUI::postTick()
{

}
