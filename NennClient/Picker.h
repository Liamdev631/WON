#pragma once
#include <Irrlicht\irrlicht.h>
#include "ClientComponent.h"
#include <map>

using namespace irr;

enum struct PickerObjectType
{
	Entity,
};

struct PickerTableEntry
{
	PickerObjectType type;
	union
	{
		int tag_int;
		unsigned int tag_uint;
		float tag_float;
	};
	PickerTableEntry() = default;

	PickerTableEntry(PickerObjectType type, int value)
		: type(type), tag_int(value)
	{

	}

	PickerTableEntry(PickerObjectType type, unsigned int value)
		: type(type), tag_uint(value)
	{

	}

	PickerTableEntry(PickerObjectType type, float value)
		: type(type), tag_float(value)
	{

	}
};

class Picker : public ClientComponent
{
private:
	scene::ISceneNode* _selectedSceneNode;
	gui::IGUIStaticText* _targetText;
	std::map<scene::ISceneNode*, PickerTableEntry> _objectTable;

public:
	Picker(const GameClient* client);
	~Picker();

	void preTick() override;
	void tick() override;
	void postTick() override;

	scene::ISceneNode* getSelectedSceneNode() const;

	void addPickedObject(scene::ISceneNode* node, PickerTableEntry entry);
	void removePickedObject(scene::ISceneNode* node);
};

