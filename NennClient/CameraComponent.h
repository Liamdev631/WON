#pragma once
#include "ClientComponent.h"
#include "Irrlicht\ICameraSceneNode.h"

using namespace irr;
using namespace core;

class CameraComponent : public ClientComponent
{
private:
	scene::ICameraSceneNode* _cameraNode;

public:
	float Direction;
	float ZDirection;

	CameraComponent(const GameClient* client);
	~CameraComponent();

	void preTick() override;
	void tick() override;
	void postTick() override;

	line3df getRay() const;

	scene::ICameraSceneNode* getCameraNode();
};
