#pragma once
#include <memory>
#include <vector>
#include "GameState.h"

using namespace std;

class ClientComponent;
class NetworkComponent;
class GraphicsComponent;
class CameraComponent;

class GameClient
{
private:
	vector<ClientComponent*> _components;

public:
	unique_ptr<NetworkComponent> component_network;
	unique_ptr<GraphicsComponent> component_graphics;
	unique_ptr<CameraComponent> component_camera;

	unique_ptr<GameState> _currentState;

	GameClient();
	~GameClient();

	void tick();
};

