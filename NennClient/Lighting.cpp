#include "Lighting.h"
#include "GameClient.h"
#include "GraphicsComponent.h"
#include <Irrlicht\irrlicht.h>
#include "IDFlags.h"

using namespace irr;

constexpr float VerticalScale = 0.0f;

Lighting::Lighting(scene::ISceneNode* parent, scene::ISceneManager* smgr)
	: scene::ISceneNode(parent, smgr, IDFlags::IsNotPickable), _sunlight(nullptr)
{
    // Setup directional lights
    _sunlight = smgr->addLightSceneNode(smgr->getRootSceneNode(), core::vector3df(0.0f, 0.0f, 0.0f),
        video::SColor(0, 200, 200, 200), 5000.0f, IDFlags::IsNotPickable);
    _sunlight->setLightType(video::ELT_DIRECTIONAL);
    _sunlight->setRotation({ 45, 0, 0 });
    _sunlight->setName("Sunlight");
    //_sunlight->enableCastShadow(true);

    // Setup ambient lights
    smgr->setAmbientLight(video::SColorf(127.0f / 255, 140.0f / 255, 148.0f / 255, 1.0f));

    // Setup the sky dome
    auto skyDomeTex = smgr->getVideoDriver()->getTexture("Content/textures/sky/skydome.jpg");
    _skyDome = smgr->addSkyDomeSceneNode(skyDomeTex, 16, 8, 0.999f, 2, 1000, smgr->getRootSceneNode(), IDFlags::IsNotPickable);
    _skyDome->setName("SkyDome");
}

Lighting::~Lighting()
{

}
