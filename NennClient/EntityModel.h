#pragma once
#include <Irrlicht\irrlicht.h>
#include <string>
#include <Entity.h>
#include "PickerNode.h"

using namespace std;
using namespace irr;

class GameClient;

class EntityModel : public scene::ISceneNode
{
private:
	scene::IAnimatedMeshSceneNode* _mesh;
	scene::ISceneNodeAnimator* _movementAnimator;
	PickerNode* _pickerNode;
	
	const GameClient* _client;
	bool _walking;

public:
	Entity::UID uid;

	EntityModel(Entity::UID uid, const GameClient* client, scene::ISceneNode* parent);
	~EntityModel();

	void setDestination(vec2f pos);

	void update();

	void render() override;

	virtual const core::aabbox3d<f32>& getBoundingBox() const
	{
		if (_mesh)
			return _mesh->getBoundingBox();
		static auto bb = core::aabbox3df(0, 0, 0, 0, 0, 0);
		return bb;
	}

	void setHeight(float height);

	scene::ISceneNode* getMesh()
	{
		return _mesh;
	}

	void printText(std::wstring text);

	void setIsPlayer();
};
