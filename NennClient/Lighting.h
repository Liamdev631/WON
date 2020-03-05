#pragma once
#include <Irrlicht\irrlicht.h>

using namespace irr;

class Lighting : public scene::ISceneNode
{
private:
	scene::ILightSceneNode* _sunlight;
	scene::ISceneNode* _skyDome;

public:
	Lighting(scene::ISceneNode* parent, scene::ISceneManager* smgr);
	~Lighting();

	virtual void render()
	{
		for (auto& child : getChildren())
			child->render();
	}

	virtual const core::aabbox3d<f32>& getBoundingBox() const
	{
		if (_sunlight)
			return _sunlight->getBoundingBox();
		static auto bb = core::aabbox3df(0, 0, 0, 0, 0, 0);
		return bb;
	}
};
