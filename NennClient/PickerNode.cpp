#include "PickerNode.h"

PickerNode::PickerNode(scene::ISceneNode* parent, scene::ISceneManager* sceneManager, irr::s32 idMask)
	: scene::ISceneNode(parent, sceneManager, idMask | IDFlags::IsPickable), _collisionMesh(nullptr)
{
	_collisionMesh = SceneManager->addSphereSceneNode(1, 8, this, IDFlags::IsPickable);
	_collisionMesh->setVisible(false);
	setRadius(1);
}

PickerNode::~PickerNode()
{
	_collisionMesh->drop();
	_collisionMesh = nullptr;
}

void PickerNode::setRadius(float radius)
{
	_radius = radius;
	_bb = core::aabbox3df(-_radius, -_radius, -_radius, _radius, _radius, _radius);
	_collisionMesh->setScale(core::vector3df(radius));
}
