#include "EntityModel.h"
#include "GameClient.h"
#include "GraphicsComponent.h"
#include "TerrainComponent.h"

using namespace core;

EntityModel::EntityModel(const GameClient* client, scene::ISceneNode* parent, s32 id)
    : scene::ISceneNode(parent, client->component_graphics->getSceneManager(), id), _mesh(nullptr), _animator(nullptr), _client(client)
{
    _mesh = SceneManager->addAnimatedMeshSceneNode(SceneManager->getMesh("../Content/models/sydney.md2"), this);
    _mesh->setScale(vector3df(0.0125f));
    _mesh->setPosition({0, 0, 0});
    _mesh->setMaterialFlag(video::EMF_LIGHTING, false);
    _mesh->setMaterialTexture(0, SceneManager->getVideoDriver()->getTexture("../Content/models/sydney.bmp"));
    _mesh->setMD2Animation(EMAT_RUN);
}

EntityModel::~EntityModel()
{
    //if (_animator)
    //    _animator->drop();
}

void EntityModel::setDestination(float x, float y)
{
    vector3df destination = { x, 0, y };
    _animator = SceneManager->createFlyStraightAnimator(getPosition(), destination, 100);
    removeAnimators();
    addAnimator(_animator);

    // Make the model face the direction of movement
    float dy = getPosition().Z - y;
    float dx = getPosition().X - x;
    if (dx != 0 || dy != 0)
    {
        float angle = core::radToDeg(atan2f(dy, -dx));
        _mesh->setRotation({ 0, angle, 0 });
    }
}

void EntityModel::render()
{

}

void EntityModel::setHeight(float height)
{
    _mesh->setPosition({ 0, height + 0.62f, 0 });
}
