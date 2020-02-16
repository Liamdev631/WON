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
	: ClientComponent(client), _cameraNode(nullptr), Direction(0), ZDirection(-85)
{
	auto graphics = client->component_graphics.get();
	if (!graphics)
	{
		printf("ERROR: CameraComponent: GraphicsComponent must be constructed before the CameraComponent!\n");
		return;
	}

	auto smgr = graphics->getSceneManager();
	_cameraNode = smgr->addCameraSceneNode(nullptr, { 5, 2, 5, }, { 256, 1, 256 });
	if (_cameraNode)
		printf("CameraComponent: Initialized\n");
	//_cameraNode = smgr->addCameraSceneNodeMaya(smgr->getRootSceneNode(), 100.0f, 0.5f, -1);
	_cameraNode->setNearValue(0.1f);
	_cameraNode->setFarValue(1024.0f);
}

CameraComponent::~CameraComponent()
{

}

void CameraComponent::preTick()
{

}

void CameraComponent::tick()
{
	auto graphics = _client->component_graphics.get();
	if (!graphics)
		return;

	// Use mouse input to rotate the camera
	core::position2d<f32> cursorPos = graphics->getDevice()->getCursorControl()->getRelativePosition();
	core::vector3df cameraPos = _cameraNode->getAbsolutePosition();

	float change_x = (cursorPos.X - 0.5) * TurnSensitivity;
	float change_y = (cursorPos.Y - 0.5) * TurnSensitivity;
	Direction += change_x;
	ZDirection -= change_y;
	if (ZDirection < -90)
		ZDirection = -90;
	else
		if (ZDirection > -MinCameraAngle)
			ZDirection = -MinCameraAngle;
	if (Direction > 360)
		Direction -= 360;
	_client->component_graphics->getDevice()->getCursorControl()->setPosition(0.5f, 0.5f);

	auto thisPlayerModel = _client->component_gameState->thisPlayersModel;
	if (thisPlayerModel)
	{
		core::vector3df playerPos = thisPlayerModel->getMesh()->getAbsolutePosition();

		float xf = playerPos.X - cos(Direction * PI / 180.0f) * CameraBoomLength;
		float yf = playerPos.Y - sin(ZDirection * PI / 180.0f) * CameraBoomLength;
		float zf = playerPos.Z + sin(Direction * PI / 180.0f) * CameraBoomLength;

		_cameraNode->setPosition(core::vector3df(xf, yf, zf));
		_cameraNode->setTarget(core::vector3df(playerPos.X, playerPos.Y, playerPos.Z));
		thisPlayerModel->setRotation(core::vector3df(0, Direction, 0));
	}

	return;
}

void CameraComponent::postTick()
{
	
}
