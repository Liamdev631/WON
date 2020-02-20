#include "Lighting.h"
#include "GameClient.h"
#include "GraphicsComponent.h"
#include <Irrlicht\irrlicht.h>

using namespace irr;

constexpr float VerticalScale = 0.0f;

Lighting::Lighting(scene::ISceneNode* parent, scene::ISceneManager* smgr, s32 id)
	: scene::ISceneNode(parent, smgr, id), _sunlight(nullptr)
{
    _sunlight = smgr->addLightSceneNode(smgr->getRootSceneNode(), core::vector3df(0.0f, 0.0f, 0.0f),
        video::SColor(0, 200, 200, 200), 5000.0f);
    _sunlight->setLightType(video::ELT_DIRECTIONAL);
    _sunlight->setRotation({ 45, 0, 0 });
    //_sunlight->enableCastShadow(true);

    smgr->setAmbientLight(video::SColorf(127.0f / 255, 140.0f / 255, 148.0f / 255, 1.0f));

    auto skyDomeTex = smgr->getVideoDriver()->getTexture("../Content/textures/sky/skydome.jpg");
    _skyDome = smgr->addSkyDomeSceneNode(skyDomeTex, 16, 8, 0.999f, 2, 1000, smgr->getRootSceneNode());
}

Lighting::~Lighting()
{

}
