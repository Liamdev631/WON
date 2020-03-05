#pragma once
#include <Irrlicht\irrlicht.h>

using namespace irr;

class TerrainComponent : public scene::ISceneNode
{
private:
	scene::ITerrainSceneNode* _terrainNode;
	scene::IMeshSceneNode* _octreeSceneNode;

public:
	TerrainComponent(scene::ISceneNode* parent, scene::ISceneManager* smgr, s32 id = -1);
	~TerrainComponent();

	virtual void render()
	{
		for (auto& child : getChildren())
			child->render();
	}

	virtual const core::aabbox3d<f32>& getBoundingBox() const
	{
		if (_terrainNode)
			return _terrainNode->getBoundingBox();
		static auto bb = core::aabbox3df(0, 0, 0, 0, 0, 0);
		return bb;
	}

	scene::ITerrainSceneNode* getNode() const
	{
		return _terrainNode;
	}
};
