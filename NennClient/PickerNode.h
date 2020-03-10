#pragma once
#include <Irrlicht\ISceneNode.h>
#include "IDFlags.h"
#include <assert.h>
#include <Entity.h>

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

	PickerTableEntry()
		: type(PickerObjectType::Entity), tag_int(0)
	{

	}

	void setEntity(Entity::UID uid)
	{
		type = PickerObjectType::Entity;
		tag_uint = uid;
	}

	Entity::UID getEntity()
	{
		assert(type == PickerObjectType::Entity);
		return tag_uint;
	}
};

class PickerNode : public scene::ISceneNode
{
private:
	float _radius;
	core::aabbox3df _bb;

public:
	PickerTableEntry data;

	PickerNode(scene::ISceneNode* parent = nullptr, scene::ISceneManager* sceneManager = nullptr, irr::s32 idMask = 0)
		: scene::ISceneNode(parent, sceneManager, idMask | IDFlags::IsPickable)
	{
		setRadius(1);
	}

	const core::aabbox3df& getBoundingBox() const override
	{
		return _bb;
	}

	void render() override
	{

	}

	void setRadius(float radius)
	{
		_radius = radius;
		_bb = core::aabbox3df(-radius, -radius, -radius, radius, radius, radius);
	}

	float getRadius()
	{
		return _radius;
	}
};

