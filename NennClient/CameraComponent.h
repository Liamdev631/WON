#pragma once
#include "ClientComponent.h"
#include "Irrlicht\ICameraSceneNode.h"

using namespace irr::scene;

class CameraComponent : public ClientComponent
{
private:
	ICameraSceneNode* _cameraNode;

public:
	CameraComponent(const GameClient* client);
	~CameraComponent();

	void preTick() override;
	void tick() override;
	void postTick() override;
};
