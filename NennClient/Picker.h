#pragma once
#include <Irrlicht\irrlicht.h>
#include "ClientComponent.h"
#include <set>
#include "PickerNode.h"

using namespace irr;

class Picker : public ClientComponent
{
private:
	PickerNode* _selectedSceneNode;
	gui::IGUIStaticText* _targetText;
	std::set<PickerNode*> _objectTable;

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

