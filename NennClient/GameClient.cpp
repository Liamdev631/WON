#include "GameClient.h"
#include "NetworkComponent.h"
#include "GraphicsComponent.h"
#include "CameraComponent.h"
#include "CameraComponent.h"
#include "GameStateComponent.h"
#include "EntityComponent.h"
#include "Input.h"
#include "Picker.h"
#include "GUI.h"
#include <thread>
#include <chrono>

using namespace chrono_literals;

GameClient::GameClient()
{
	component_input = make_unique<InputComponent>(this);
	component_graphics = make_unique<GraphicsComponent>(this);
	component_network = make_unique<NetworkComponent>(this);
	component_camera = make_unique<CameraComponent>(this);
	component_gameState = make_unique<GameStateComponent>(this);
	component_entity = make_unique<EntityComponent>(this);
	component_picker = make_unique<Picker>(this);
	component_gui = make_unique<GUI>(this);

	_components = {
		component_network.get(),
		component_gameState.get(),
		component_input.get(),
		component_entity.get(),
		component_camera.get(),
		component_picker.get(),
	};
}

GameClient::~GameClient()
{

}

void GameClient::tick()
{
	component_graphics->preTick();
	component_gui->preTick();

	for (auto c : _components)
		c->preTick();
	for (auto c : _components)
		c->tick();
	for (auto c : _components)
		c->postTick();

	component_gui->tick();
	component_graphics->tick();
	component_gui->postTick();
	component_graphics->postTick();
	//printf("%i\n", component_graphics->getDriver()->getFPS());
}

