#include "GameClient.h"
#include "NetworkComponent.h"
#include "GraphicsComponent.h"
#include "CameraComponent.h"
#include "CameraComponent.h"
#include "GameStateComponent.h"
#include "EntityComponent.h"
#include <thread>
#include <chrono>

using namespace chrono_literals;

GameClient::GameClient()
{
	component_graphics = make_unique<GraphicsComponent>(this);
	component_network = make_unique<NetworkComponent>(this);
	component_camera = make_unique<CameraComponent>(this);
	component_gameState = make_unique<GameStateComponent>(this);
	component_entity = make_unique<EntityComponent>(this);

	_components = {
		component_gameState.get(),
		component_entity.get(),
		component_camera.get(),
	};
}

GameClient::~GameClient()
{

}

void GameClient::tick()
{
	// 
	component_network->preTick();
	component_network->tick();
	component_network->postTick();

	for (auto c : _components)
		c->preTick();
	for (auto c : _components)
		c->tick();
	for (auto c : _components)
		c->postTick();

	// The graphics component must be ticked last because it will sleep to maintain the designated framerate
	component_graphics->preTick();
	component_graphics->tick();
	component_graphics->postTick();
}

