#pragma once
#include <Irrlicht\irrlicht.h>
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
	irr::scene::IMeshSceneNode* _collisionMesh;

public:
	PickerTableEntry data;

	PickerNode(scene::ISceneNode* parent = nullptr, scene::ISceneManager* sceneManager = nullptr, irr::s32 idMask = 0);
	~PickerNode();

	const core::aabbox3df& getBoundingBox() const override
	{
		return _bb;
	}

	void render() override
	{

	}

	// Sets the radius of this picker node. This is the absolute size, not relative
	// to the parent.
	void setRadius(float radius);

	float getRadius()
	{
		return _radius;
	}
};

