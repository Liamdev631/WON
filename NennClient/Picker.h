#pragma once
#include "ClientComponent.h"
#include <set>
#include "PickerNode.h"
#include "PickerDisplay.h"

using namespace irr;


class Picker : public ClientComponent
{
private:
	PickerNode* _selectedSceneNode;
	std::set<PickerNode*> _objects;
	PickerDisplay* _pickerDisplay;

public:
	Picker(const GameClient* client);
	~Picker();

	void preTick() override;
	void tick() override;
	void postTick() override;

	PickerNode* getSelectedSceneNode() const;

	void addPickedObject(PickerNode* node);
	void removePickedObject(PickerNode* node);
};

