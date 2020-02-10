#include "GameServer.h"
#include "EntityComponent.h"
#include "MovementComponent.h"
#include "NetworkComponent.h"
#include <thread>
#include <chrono>

using namespace std;
using namespace chrono_literals;

GameServer::GameServer()
{
	component_entity = make_unique<EntityComponent>(this);
	component_movement = make_unique<MovementComponent>(this);
	component_network = make_unique<NetworkComponent>(this);

	_components = {
		component_entity.get(),
		component_movement.get(),
		component_network.get()
	};
}

GameServer::~GameServer()
{

}

void GameServer::tick()
{
	static int tick = 0;
	printf("tick\n");
	json j;
	j["message"] = "print-string";
	j["string"] = "tick " + std::to_string(tick++);
	component_network->connections.sendJson(j, component_entity->getActivePlayers());

	for (auto c : _components)
		c->preTick();
	for (auto c : _components)
		c->tick();
	for (auto c : _components)
		c->postTick();

	this_thread::sleep_for(100ms);
}
