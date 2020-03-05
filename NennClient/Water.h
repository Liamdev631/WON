#pragma once
#include <Irrlicht\irrlicht.h>

using namespace irr;

class Water : public scene::ISceneNode
{
private:
	scene::ISceneNode* _waterNode;

public:
	Water(scene::ISceneNode* parent, scene::ISceneManager* smgr);
	~Water();

	virtual void render()
	{
		for (auto& child : getChildren())
			child->render();
	}

	virtual const core::aabbox3d<f32>& getBoundingBox() const
	{
		if (_waterNode)
			return _waterNode->getBoundingBox();
		static auto bb = core::aabbox3df(0, 0, 0, 0, 0, 0);
		return bb;
	}
};
