#pragma once
#include <Irrlicht\IGUIStaticText.h>

using namespace irr;

class GameClient;

class PickerDisplay
{
private:
	// A reference to the base client
	const GameClient* _client;

	// Text to be displayed
	gui::IGUIStaticText* _targetText;

public:
	// Initializes the state of the picker display.
	PickerDisplay(const GameClient* client);

	// Updates the display subcomponent of the Picker component.
	void update();
};
