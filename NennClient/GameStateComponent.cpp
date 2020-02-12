#include "GameStateComponent.h"
#include "GameClient.h"
#include "EntityComponent.h"

GameStateComponent::GameStateComponent(const GameClient* client)
	: ClientComponent(client), thisPlayersUID(NO_UID), thisPlayersModel(nullptr)
	, thisPlayersEntity(nullptr)
{

}

GameStateComponent::~GameStateComponent()
{

}

void GameStateComponent::preTick()
{

}

void GameStateComponent::tick()
{

}

void GameStateComponent::postTick()
{
	// TODO: There's no sense in checking this every tick
	if (thisPlayersUID != NO_UID)
	{
		if (!thisPlayersModel)
			thisPlayersModel = _client->component_entity->getEntityModel(thisPlayersUID);
	}
}
