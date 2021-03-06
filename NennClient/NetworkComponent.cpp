#include "NetworkComponent.h"
#include "GameStateComponent.h"
#include "EntityComponent.h"
#include "CameraComponent.h"
#include "GameClient.h"
#include <string>
#include <vector>
#include <json.hpp>
#include "EntityModel.h"
#include "Config.h"
#include "IDFlags.h"

using namespace std;
using namespace nlohmann;

NetworkComponent::NetworkComponent(const GameClient* client)
	: ClientComponent(client), _connectionStatus(ConnectionStatus::Disconnected)
{
	printf("NetworkComponent: Attempting connection to server.\n");
	_socket.setBlocking(false);
	auto connectResult = _socket.connect("localhost", ServerPort, sf::seconds(5));
	/*if (connectResult == sf::Socket::Status::Done)
		printf("NetworkComponent: Connected to the server!\n");
	else
		printf("NetworkComponent: Connection to server failed! Code %u\n", static_cast<unsigned int>(connectResult));
	_socket.setBlocking(false);*/
}

NetworkComponent::~NetworkComponent()
{
	_socket.setBlocking(true);
	_socket.disconnect();
}

void NetworkComponent::preTick()
{

}

void NetworkComponent::tick()
{
	sf::Packet packet;
	for (int i = 0; i < 10; i++)
	{
		sf::Socket::Status currentNetStatus = _socket.receive(packet);
		switch (currentNetStatus)
		{
			case sf::Socket::Status::Disconnected:
			{
				if (_connectionStatus == ConnectionStatus::Disconnected)
					break;
				_connectionStatus = ConnectionStatus::Disconnected;
				printf("NetworkComponent: Disconnected from the server!\n");
				break;
			}

			case sf::Socket::Status::Done:
			{
				if (_connectionStatus != ConnectionStatus::Connected)
				{
					_connectionStatus = ConnectionStatus::Connected;
					onConnected();
				}

				std::string s;
				packet >> s;
				json j = json::parse(s);
				std::string message = j["message"];

				// Determine which type of message to decode
				if (message == "hello-player")
				{
					const Entity::UID uid = j["uid"];
					const float x = j["x"];
					const float y = j["y"];

					Entity& playerEntity = _client->component_entity->getEntity(uid);
					EntityModel* playerModel = _client->component_entity->getEntityModel(uid);

					playerEntity.position = { x, y };
					playerModel->setIsPlayer();

					// Create references to this player in the GameState component
					auto gs = _client->component_gameState.get();
					gs->thisPlayersUID = uid;
					gs->thisPlayersEntity = &playerEntity;
					gs->thisPlayersModel = playerModel;
					
					// Make sure our own player is not pickable
					playerModel->setID(IDFlags::IsNotPickable);

					printf("NetworkComponent: You have been assigned uid %u\n", uid);
					break;
				}
				else if (message == "entity-update")
				{
					const Entity::UID uid = j["uid"];
					if (uid != _client->component_gameState->thisPlayersUID)
					{
						const float x = j["x"];
						const float y = j["y"];
						auto& entity = _client->component_entity->getEntity(uid);
						entity.position = { x, y };
						//printf("NetworkComponent: Entity %u moved to (%f, %f)\n", uid, x, y);
					}

					break;
				}
				else if (message == "print-string")
				{
					std::string str = j["string"];
					auto thisPlayersModel = _client->component_gameState->thisPlayersModel;
					if (thisPlayersModel)
					{
						thisPlayersModel->printText(wstring(str.begin(), str.end()));
					}
					printf("PRINT: %s\n", str.c_str());
				}
				else if (message == "entity-removed")
				{
					const Entity::UID uid = j["uid"];
					printf("NetworkComponent: Entity %u removed\n", uid);
					_client->component_entity->removeEntity(uid);
					break;
				}
				else
				{
					printf("Unimplemented message type: '%s'\n", message.c_str());
					break;
				}
			}

			default:
				break;
		}
	}

}

void NetworkComponent::onConnected()
{
	printf("NetworkComponent: Connected to the server!\n");

	// Send login info to the server
	Config config("login.config");
	json j = config.read();
	//j["message"] = "login-info";
	//sendJson(j);
}

void NetworkComponent::postTick()
{

}

void NetworkComponent::sendJson(json& j)
{
	sf::Packet packet;
	packet << j.dump(-1, ' ', true);
	_socket.send(packet);
}
