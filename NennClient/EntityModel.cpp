#include "EntityModel.h"
#include "GameClient.h"
#include "GraphicsComponent.h"
#include "TerrainComponent.h"
#include "EntityComponent.h"
#include "Picker.h"
#include "IDFlags.h"

using namespace core;

EntityModel::EntityModel(Entity::UID uid, const GameClient* client, scene::ISceneNode* parent)
    : scene::ISceneNode(parent, client->component_graphics->getSceneManager()), uid(uid), _mesh(nullptr),
    _movementAnimator(nullptr), _client(client), _walking(false)
{
    setID(IDFlags::IsNotPickable);

    // Setup the mesh
    std::string name = "EntityModel_";
    name.append(std::to_string(uid));
    setName(name.c_str());
    _mesh = SceneManager->addAnimatedMeshSceneNode(SceneManager->getMesh("Content/models/sydney.md2"), this);
    _mesh->setID(IDFlags::IsNotPickable);
    _mesh->setScale(vector3df(0.005f));
    _mesh->setPosition({0, 0, 0});
    _mesh->setMaterialFlag(video::EMF_LIGHTING, false);
    _mesh->setMaterialTexture(0, SceneManager->getVideoDriver()->getTexture("Content/models/sydney.bmp"));
    _mesh->setMD2Animation(EMAT_STAND);
    auto meshName = name;
    meshName.append("_mesh");
    _mesh->setName(meshName.c_str());

    // Setup the node that makes is possible to pick this
    PickerNode = SceneManager->addSphereSceneNode(30, 16, _mesh);
    PickerNode->setID(IDFlags::IsPickable);
    PickerNode->setVisible(true);
    auto pickerName = name;
    pickerName.append("_picker");
    PickerNode->setName(pickerName.c_str());

    _client->component_picker->addPickedObject(PickerNode, PickerTableEntry(PickerObjectType::Entity, uid));

    // Shadows
    if (ShadowsEnabled)
        _mesh->addShadowVolumeSceneNode();
}

EntityModel::~EntityModel()
{
    _client->component_picker->removePickedObject(this);

}

void EntityModel::setDestination(vec2f pos)
{
    removeAnimators();
    _movementAnimator = SceneManager->createFlyStraightAnimator(getPosition(), { pos.x, 0, pos.y }, 100);
    addAnimator(_movementAnimator);
    _mesh->setMD2Animation(EMAT_STAND);

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
    float dx = destination.x - getPosition().X;
    float dy = destination.y - getPosition().Z;
    float dist = sqrtf(dx * dx + dy * dy);
    if (dist > 0.01f)
    {
        _movementAnimator = SceneManager->createFlyStraightAnimator(getPosition(), { destination.x, 0, destination.y }, 100);
        addAnimator(_movementAnimator);

        // Make the model face the direction of movement
        float angle = 180 + core::radToDeg(atan2f(dy, -dx));
        _mesh->setRotation({ 0, angle, 0 });

        // Trigger the walking animation if needed
        if (!_walking)
        {
            _walking = true;
            _mesh->setMD2Animation(EMAT_RUN);
        }
    }
    else
    {
        if (_walking)
        {
            _movementAnimator->drop();
            _walking = false;
            _mesh->setMD2Animation(EMAT_STAND);
        }
    }

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
    const wchar_t* ttext = L" ";

    if (!text.empty())
        ttext = text.c_str();

    vector3df start = _mesh->getPosition();

    f32 height = _mesh->getBoundingBox().getExtent().Y;

    //start.Y += height;
    vector3df end = start;
    end.Y += height + 50;

    SColor color(255, 255, 255, 255);
    dimension2df size = { 0.2f, 0.05f };
    unsigned int duration = 1000 * 4;

    auto smgr = _client->component_graphics->getSceneManager();
    auto gui = _client->component_graphics->getGUI();
    IBillboardTextSceneNode* nodetext = smgr->addBillboardTextSceneNode(0, ttext, smgr->getRootSceneNode(), size, start);
    /*scene::ISceneNodeAnimator* anim = smgr->createDeleteAnimator(duration);
    scene::ISceneNodeAnimator* anim2 = smgr->createFlyStraightAnimator(start, end, duration);
    if (nodetext && anim)
    {
        nodetext->addAnimator(anim);
        nodetext->addAnimator(anim2);
    }*/
}

void EntityModel::setIsPlayer()
{
    PickerNode->setID(IDFlags::IsNotPickable);
}
