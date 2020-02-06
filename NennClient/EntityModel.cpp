#include "EntityModel.h"
#include <Irrlicht\irrlicht.h>

EntityModel::EntityModel(ISceneManager* scene)
	: _scene(scene), _mesh(nullptr), _animator(nullptr)
{
    _mesh = scene->addAnimatedMeshSceneNode(scene->getMesh("../Content/models/sydney.md2"));
    _animator = scene->createFlyStraightAnimator(core::vector3df(100, 0, 60), core::vector3df(-100, 0, 60), 3500, true);
}

EntityModel::~EntityModel()
{
    _mesh->drop();
    _animator->drop();
}
