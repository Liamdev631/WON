#include "EntityModel.h"
#include "GameClient.h"
#include "GraphicsComponent.h"
#include "TerrainComponent.h"
#include "EntityComponent.h"

using namespace core;

EntityModel::EntityModel(Entity::UID uid, const GameClient* client, scene::ISceneNode* parent, s32 id)
    : scene::ISceneNode(parent, client->component_graphics->getSceneManager(), id), uid(uid), _mesh(nullptr), _animator(nullptr), _client(client)
{
    _mesh = SceneManager->addAnimatedMeshSceneNode(SceneManager->getMesh("../Content/models/sydney.md2"), this);
    _mesh->setScale(vector3df(0.005f));
    _mesh->setPosition({0, 0, 0});
    _mesh->setMaterialFlag(video::EMF_LIGHTING, false);
    _mesh->setMaterialTexture(0, SceneManager->getVideoDriver()->getTexture("../Content/models/sydney.bmp"));
    _mesh->setMD2Animation(EMAT_RUN);

    // Shadows
    _mesh->addShadowVolumeSceneNode();
}

EntityModel::~EntityModel()
{

}

void EntityModel::setDestination(vec2f pos)
{
    vector3df destination = { pos.x, 0, pos.y };
    _animator = SceneManager->createFlyStraightAnimator(getPosition(), destination, 100);
    removeAnimators();
    addAnimator(_animator);

    // Make the model face the direction of movement
    float dx = pos.x - getPosition().X;
    float dy = pos.y - getPosition().Z;
    if (dx != 0 || dy != 0)
    {
        float angle = 180 + core::radToDeg(atan2f(dy, -dx));
        _mesh->setRotation({ 0, angle, 0 });
    }
}

void EntityModel::update()
{
    // Move to the position we're supposed to be in
    auto destination = _client->component_entity->getEntity(uid).position;
    setDestination(destination);

    // Set each characters height to the height of the terrain
    auto terrainNode = _client->component_graphics->getTerrainComponent()->getNode();
    vector3df currentPos = _mesh->getAbsolutePosition();
    float height = terrainNode->getHeight(currentPos.X, currentPos.Z);
    setHeight(height);
}

void EntityModel::render()
{

}

void EntityModel::setHeight(float height)
{
    _mesh->setPosition({ 0, height + 0.1f, 0 });// +0.62f, 0
}

void EntityModel::printText(std::wstring text)
{
    auto node = _mesh;
    const wchar_t* ttext = L" ";

    if (!text.empty())
        ttext = text.c_str();

    vector3df start = node->getAbsolutePosition();

    f32 height = node->getBoundingBox().getExtent().Y * getScale().Y;

    start.Y += height - 30;
    vector3df end = start;
    end.Y += height + 50;

    SColor color(255, 255, 255, 255);
    dimension2df size = { 10.0f, 2.0f };
    unsigned int duration = 1000 * 4;

    auto smgr = _client->component_graphics->getSceneManager();
    auto gui = _client->component_graphics->getGUI();
    IBillboardTextSceneNode* nodetext = smgr->addBillboardTextSceneNode(0, ttext, smgr->getRootSceneNode(), size, start, -1, color, color);
    scene::ISceneNodeAnimator* anim = smgr->createDeleteAnimator(duration);
    scene::ISceneNodeAnimator* anim2 = smgr->createFlyStraightAnimator(start, end, duration);
    if (nodetext && anim)
    {
        nodetext->addAnimator(anim);
        nodetext->addAnimator(anim2);
    }
}
