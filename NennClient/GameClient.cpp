#include "GameClient.h"
#include "NetworkComponent.h"
#include "GraphicsComponent.h"
#include <thread>
#include <chrono>
#include "CameraComponent.h"

using namespace chrono_literals;

GameClient::GameClient()
{
	component_network = make_unique<NetworkComponent>(this);
	component_graphics = make_unique<GraphicsComponent>(this);
	component_camera = make_unique<CameraComponent>(this);

	_components = {
		component_network.get()
	};

	_currentState = make_unique<GameState>();
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

