#pragma once
#include "ClientComponent.h"
#include "Irrlicht\ITerrainSceneNode.h"

using namespace irr::scene;

class TerrainComponent : public ClientComponent
{
private:
	ITerrainSceneNode* _terrainNode;

public:
	TerrainComponent(const GameClient* client);
	~TerrainComponent();

	void preTick() override;
	void tick() override;
	void postTick() override;
};
