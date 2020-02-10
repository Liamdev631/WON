#include "Lighting.h"
#include "GameClient.h"
#include "GraphicsComponent.h"
#include <Irrlicht\irrlicht.h>

using namespace irr;

constexpr float VerticalScale = 0.0f;

Lighting::Lighting(scene::ISceneNode* parent, scene::ISceneManager* smgr, s32 id)
	: scene::ISceneNode(parent, smgr, id), _sunlight(nullptr)
{
    _sunlight = smgr->addLightSceneNode(0, core::vector3df(0.0f, 0.0f, 0.0f),
        video::SColor(0, 200, 200, 200), 5000.0f);
    _sunlight->setLightType(video::ELT_DIRECTIONAL);
    _sunlight->enableCastShadow(true);
}

Lighting::~Lighting()
{

}
