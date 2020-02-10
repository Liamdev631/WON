#include "TerrainComponent.h"
#include "GameClient.h"
#include "GraphicsComponent.h"
#include <Irrlicht\irrlicht.h>

using namespace irr;

constexpr float VerticalScale = 0.4f;

TerrainComponent::TerrainComponent(scene::ISceneNode* parent, scene::ISceneManager* smgr, s32 id)
	: scene::ISceneNode(parent, smgr, id), _terrainNode(nullptr)
{
	_terrainNode = SceneManager->addTerrainSceneNode("../Content/heightmaps/overworld.png",
		this, -1, { 0, 0, 0 }, { 0, 0, 0 }, { 1, VerticalScale, 1 }, SColor(255, 255, 255, 255),
		5, E_TERRAIN_PATCH_SIZE::ETPS_33, 4);
	if (_terrainNode)
	{
		auto grassTexture = SceneManager->getVideoDriver()->getTexture("../Content/textures/terrain/meadow_grass.png");
		auto detailTexture = SceneManager->getVideoDriver()->getTexture("../Content/textures/terrain/detail.png");
		_terrainNode->setMaterialTexture(0, grassTexture);
		_terrainNode->setMaterialTexture(1, detailTexture);
		_terrainNode->setMaterialFlag(EMF_LIGHTING, true);
		_terrainNode->scaleTexture(256, 32);
	}
}

TerrainComponent::~TerrainComponent()
{

}
