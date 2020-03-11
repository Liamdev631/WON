#include "PickerDisplay.h"
#include "GameClient.h"
#include <Irrlicht\irrlicht.h>
#include "GraphicsComponent.h"
#include "Picker.h"

PickerDisplay::PickerDisplay(const GameClient* client)
	: _client(client)
{
	_targetText = _client->component_graphics->getGUI()->addStaticText(L"TEXT", recti(10, 10, 100, 18), false, false);
}

void PickerDisplay::update()
{
	auto pickedSceneNode = _client->component_picker->getSelectedSceneNode();
	if (pickedSceneNode)
	{
		_targetText->setText(L"ENTITY");
	}
	else
		_targetText->setText(L"NO ENTITY");
}