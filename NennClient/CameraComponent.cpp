#include "CameraComponent.h"
#include "GameClient.h"
#include "GraphicsComponent.h"
#include <Irrlicht\irrlicht.h>

using namespace irr;
using namespace scene;

CameraComponent::CameraComponent(const GameClient* client)
	: ClientComponent(client), _cameraNode(nullptr)
{
	auto graphicsComponent = client->component_graphics.get();
	if (!graphicsComponent)
	{
		printf("ERROR: CameraComponent: GraphicsComponent must be constructed before the CameraComponent!\n");
		return;
	}

	auto smgr = graphicsComponent->getSceneManager();
	_cameraNode = smgr->addCameraSceneNode(nullptr, { 20, 15, 20, }, { 0, 1, 0 });
	if (_cameraNode)
		printf("CameraComponent: Initialized\n");

	/* Test model
	IAnimatedMesh* mesh = smgr->getMesh("../Content/models/sydney.md2");
	if (mesh)
	{
		IAnimatedMeshSceneNode* node = smgr->addAnimatedMeshSceneNode(mesh);
		if (node)
		{
			node->setMaterialFlag(EMF_LIGHTING, false);
			node->setMD2Animation(scene::EMAT_STAND);
			node->setMaterialTexture(0, graphicsComponent->getVideoDriver()->getTexture("../Content/models/sydney.bmp"));
		}
	}*/
}

CameraComponent::~CameraComponent()
{

}

void CameraComponent::preTick()
{

}

void CameraComponent::tick()
{

}

void CameraComponent::postTick()
{

}
