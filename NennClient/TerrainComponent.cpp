#include "TerrainComponent.h"
#include "GameClient.h"
#include "GraphicsComponent.h"
#include <Irrlicht\irrlicht.h>

using namespace irr;
using namespace scene;

TerrainComponent::TerrainComponent(const GameClient* client)
	: ClientComponent(client), _terrainNode(nullptr)
{
	auto graphicsComponent = client->component_graphics.get();
	if (!graphicsComponent)
	{
		printf("ERROR: TerrainComponent: GraphicsComponent must be constructed before the TerrainComponent!\n");
		return;
	}

	auto smgr = graphicsComponent->getSceneManager();
	_terrainNode = smgr->addTerrainSceneNode("../Content/heightmaps/overworld.png",
		nullptr, -1, { 0, 0, 0 }, { 0, 0, 0 }, { 1, 1.0f / 8, 1 }, SColor(255, 255, 255, 255),
		5, E_TERRAIN_PATCH_SIZE::ETPS_17);
	if (_terrainNode)
	{
		auto grassTexture = graphicsComponent->getVideoDriver()->getTexture("../Content/textures/terrain/meadow_grass.png");
		_terrainNode->setMaterialFlag(EMF_LIGHTING, false);
		_terrainNode->setMaterialTexture(0, grassTexture);
		_terrainNode->scaleTexture(512);
	}
}

TerrainComponent::~TerrainComponent()
{

}

void TerrainComponent::preTick()
{

}

void TerrainComponent::tick()
{

}

void TerrainComponent::postTick()
{

}
