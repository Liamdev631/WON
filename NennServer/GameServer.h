#pragma once
#include <memory>
#include <vector>

using namespace std;

class ServerComponent;
class EntityComponent;
class MovementComponent;
class NetworkComponent;

class GameServer
{
private:
	vector<ServerComponent*> _components;

public:
	unique_ptr<EntityComponent>		component_entity;
	unique_ptr<MovementComponent>	component_movement;
	unique_ptr<NetworkComponent>	component_network;

	GameServer();
	~GameServer();

	void tick();
};

