#pragma once
#include <Irrlicht\ISceneNodeAnimator.h>
#include <Irrlicht\IAnimatedMeshSceneNode.h>
#include <Irrlicht\ISceneManager.h>

using namespace irr;
using namespace scene;

class EntityModel
{
private:
	ISceneManager* _scene;
	IAnimatedMeshSceneNode* _mesh;
	ISceneNodeAnimator* _animator;

public:
	EntityModel(ISceneManager* scene);
	~EntityModel();
};
