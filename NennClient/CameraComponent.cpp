#include "CameraComponent.h"
#include "GameClient.h"
#include "GraphicsComponent.h"
#include "GameStateComponent.h"
#include "EntityComponent.h"
#include <Irrlicht\irrlicht.h>
#include "EntityModel.h"
#include <Settings.h>

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
	_cameraNode = smgr->addCameraSceneNode(nullptr, { 5, 2, 5, }, { 256, 1, 256 });
	if (_cameraNode)
		printf("CameraComponent: Initialized\n");
}

CameraComponent::~CameraComponent()
{

}

void CameraComponent::preTick()
{

}

void CameraComponent::tick()
{
	Entity::UID thisPlayerUID = _client->component_gameState->thisPlayersUID;
	if (thisPlayerUID != NO_UID)
	{
		// Move the camera to follow the player
		auto thisPlayerModel = _client->component_entity->getEntityModel(thisPlayerUID);
		if (thisPlayerModel)
		{
			vector3df target = thisPlayerModel->getMesh()->getAbsolutePosition();
			vector3df offset = vector3df(0, sinf(CameraAngle), -cosf(CameraAngle)) * CameraBoomLength;
			vector3df position = target + offset;
			_cameraNode->setTarget(target);
			_cameraNode->setPosition(position);
		}
	}
}

void CameraComponent::postTick()
{

}
