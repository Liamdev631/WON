#include "Water.h"
#include "GameClient.h"
#include "GraphicsComponent.h"
#include <Irrlicht\irrlicht.h>

using namespace irr;

constexpr float VerticalScale = 0.0f;

Water::Water(scene::ISceneNode* parent, scene::ISceneManager* smgr, s32 id)
	: scene::ISceneNode(parent, smgr, id), _waterNode(nullptr)
{
	auto mesh = smgr->addHillPlaneMesh("myHill",
		core::dimension2d<f32>(4, 4),
		core::dimension2d<u32>(512/4, 512/4));
	_waterNode = smgr->addWaterSurfaceSceneNode(mesh, 0.025f, 0.01f, 0.3f);
	_waterNode->setPosition(core::vector3df(0, 2, 0));
	_waterNode->setMaterialFlag(EMF_LIGHTING, false);
	_waterNode->setVisible(false);
}

Water::~Water()
{

}
