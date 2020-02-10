#include "NetworkComponent.h"
#include "GameStateComponent.h"
#include "EntityComponent.h"
#include "CameraComponent.h"
#include "GameClient.h"
#include <string>
#include <vector>
#include <json.hpp>

using namespace std;
using namespace nlohmann;

NetworkComponent::NetworkComponent(const GameClient* client)
	: ClientComponent(client), _connectionStatus(ConnectionStatus::Disconnected)
{
	printf("NetworkComponent: Attempting connection to server.\n");
	_socket.setBlocking(true);
	//_socket.connect(sf::IpAddress(ServerIP.data()), ServerPort, sf::seconds(5));
	auto connectResult = _socket.connect("localhost", ServerPort, sf::seconds(5));
	if (connectResult == sf::Socket::Status::Done)
		printf("NetworkComponent: Connected to the server!\n");
	else
		printf("NetworkComponent: Connection to server failed! Code %u\n", static_cast<unsigned int>(connectResult));
	_socket.setBlocking(false);
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
				_connectionStatus = ConnectionStatus::Connected;
				string s;
				packet >> s;
				json j = json::parse(s);
				string message = j["message"];

				// Determine which type of message to decode
				if (message == "hello-player")
				{
					const Entity::UID uid = j["uid"];
					_client->component_gameState->thisPlayersUID = uid;
					printf("NetworkComponent: You have been assigned uid %u\n", uid);
					break;
				}
				else if (message == "entity-update")
				{
					const Entity::UID uid = j["uid"];
					const float x = j["x"];
					const float y = j["y"];
					//printf("NetworkComponent: Entity %u moved to (%f, %f)\n", uid, x, y);
					auto& entity = _client->component_entity->getEntity(uid);
					entity.position = { x, y };
					printf("%u\n", uid);

					break;
				}
				else
				{
					printf("%s\n", message.c_str());
					break;
				}
				/*else if (message == "entity-removed")
				{
					const Entity::UID uid = j["uid"];
					printf("NetworkComponent: Entity %u removed\n", uid);
					_client->component_entity->removeEntity(uid);
					break;
				}
				else
					break;*/
			}

			default:
				break;
		}
	}

}

void NetworkComponent::postTick()
{

}
