#pragma once
#include <memory>
#include <vector>

using namespace std;

class ClientComponent;
class NetworkComponent;
class GraphicsComponent;
class CameraComponent;
class TerrainComponent;
class GameStateComponent;
class EntityComponent;

class GameClient
{
private:
	vector<ClientComponent*> _components;

public:
	unique_ptr<NetworkComponent> component_network;
	unique_ptr<GraphicsComponent> component_graphics;
	unique_ptr<CameraComponent> component_camera;
	unique_ptr<TerrainComponent> component_terrain;
	unique_ptr<GameStateComponent> component_gameState;
	unique_ptr<EntityComponent> component_entity;

	GameClient();
	~GameClient();

	void tick();
};

