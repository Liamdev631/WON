#pragma once
#include <Irrlicht\irrlicht.h>

using namespace irr;
class GameClient;

class EntityModel : public scene::ISceneNode
{
private:
	scene::IAnimatedMeshSceneNode* _mesh;
	scene::ISceneNodeAnimator* _animator;
	const GameClient* _client;

public:
	EntityModel(const GameClient* client, scene::ISceneNode* parent, s32 id = -1);
	~EntityModel();

	void setDestination(float x, float y);

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
};
