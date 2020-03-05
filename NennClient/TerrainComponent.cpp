#include "TerrainComponent.h"
#include "GameClient.h"
#include "GraphicsComponent.h"
#include <Irrlicht\irrlicht.h>
#include "IDFlags.h"

using namespace irr;

constexpr float VerticalScale = 0.2f;

TerrainComponent::TerrainComponent(scene::ISceneNode* parent, scene::ISceneManager* smgr, s32 id)
	: scene::ISceneNode(parent, smgr, IDFlags::IsNotPickable), _terrainNode(nullptr), _octreeSceneNode(nullptr)
{
	_terrainNode = SceneManager->addTerrainSceneNode("Content/heightmaps/overworld.png",
		this, IDFlags::IsNotPickable, { 0, 0, 0 }, { 0, 0, 0 }, { 1, VerticalScale, 1 }, SColor(255, 255, 255, 255),
		5, E_TERRAIN_PATCH_SIZE::ETPS_65, 2);
	_terrainNode->setName("TerrainComponent");
	if (_terrainNode)
	{
		auto grassTexture = SceneManager->getVideoDriver()->getTexture("Content/textures/terrain/meadow_grass.png");
		auto detailTexture = SceneManager->getVideoDriver()->getTexture("Content/textures/terrain/detail.png");
		_terrainNode->setMaterialTexture(0, grassTexture);
		_terrainNode->setMaterialTexture(1, detailTexture);
		_terrainNode->setMaterialFlag(EMF_LIGHTING, true);
		_terrainNode->scaleTexture(512, 128);
		_terrainNode->setAutomaticCulling(true);
	}
}

TerrainComponent::~TerrainComponent()
{
	_terrainNode->drop();
	_octreeSceneNode->drop();
}
