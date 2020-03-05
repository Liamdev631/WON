#pragma once
#include <memory>
#include <vector>

using namespace std;

class ClientComponent;
class NetworkComponent;
class GraphicsComponent;
class CameraComponent;
class GameStateComponent;
class EntityComponent;
class InputComponent;
class Picker;
class GUI;

class GameClient
{
private:
	vector<ClientComponent*> _components;

public:
	unique_ptr<InputComponent> component_input;
	unique_ptr<NetworkComponent> component_network;
	unique_ptr<GraphicsComponent> component_graphics;
	unique_ptr<CameraComponent> component_camera;
	unique_ptr<GameStateComponent> component_gameState;
	unique_ptr<EntityComponent> component_entity;
	unique_ptr<Picker> component_picker;
	unique_ptr<GUI> component_gui;

	GameClient();
	~GameClient();

	void tick();
};

