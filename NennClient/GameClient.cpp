#include "GameClient.h"
#include "NetworkComponent.h"
#include "GraphicsComponent.h"
#include <thread>
#include <chrono>

using namespace chrono_literals;

GameClient::GameClient()
{
	component_network = make_unique<NetworkComponent>(this);
	component_graphics = make_unique<GraphicsComponent>(this);
	_currentState = make_unique<GameState>();
	_components = {
		component_network.get()
	};
}

GameClient::~GameClient()
{

}

void GameClient::tick()
{
	for (auto c : _components)
	{
		c->preTick();
		c->tick();
		c->postTick();
	}

	// Tick the render component last
	component_graphics->preTick();
	component_graphics->tick();
	component_graphics->postTick();
}

