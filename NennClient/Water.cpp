#include "Water.h"
#include "GameClient.h"
#include "GraphicsComponent.h"
#include <Irrlicht\irrlicht.h>
#include "IDFlags.h"

using namespace irr;

constexpr float VerticalScale = 0.0f;

Water::Water(scene::ISceneNode* parent, scene::ISceneManager* smgr)
	: scene::ISceneNode(parent, smgr, IDFlags::IsNotPickable), _waterNode(nullptr)
{
	return;
	auto mesh = smgr->addHillPlaneMesh("WaterMesh",
		core::dimension2d<f32>(4, 4),
		core::dimension2d<u32>(512/4, 512/4));
	_waterNode = smgr->addWaterSurfaceSceneNode(mesh, 0.00025f, 0.0001f, 0.003f, SceneManager->getRootSceneNode());
	_waterNode->setID(IDFlags::IsNotPickable);
	_waterNode->setPosition(core::vector3df(256, 1, 256));
	_waterNode->setVisible(true);
}

Water::~Water()
{

}
