#include "NetworkComponent.h"
#include "GameServer.h"
#include "EntityComponent.h"
#include "MovementComponent.h"
#include <json.hpp>

using namespace nlohmann;

NetworkComponent::NetworkComponent(const GameServer* server)
	: ServerComponent(server)
{
	_listener.listen(ServerPort);
	_listener.setBlocking(false);
	printf("NetworkComponent: Listening!\n");
}

NetworkComponent::~NetworkComponent()
{
	printf("NetworkComponent: Stopping listening.\n");
	_listener.setBlocking(true);
	_listener.close();
}

unsigned int getNextSocket(Connections& connections)
{
	unsigned int nextSocket = 0;
	while (connections.status[nextSocket] != ConnectionStatus::Disconnected)
		nextSocket++;
	return nextSocket;
}

void NetworkComponent::preTick()
{
	// Process new connections
	unsigned int newPlayerUID = getNextSocket(connections);
	while (_listener.accept(connections.socket[newPlayerUID]) == sf::TcpSocket::Status::Done)
	{
		// Setup a new connection
		_server->component_entity->grabNextAvailablePlayer(newPlayerUID);
		connections.status[newPlayerUID] = ConnectionStatus::Connected;

		//auto ip = connections.socket[uid].getRemoteAddress();
		printf("NetworkComponent: Client connected! uid=%u\n", newPlayerUID);

		_server->component_entity->onEntityAdded(newPlayerUID);

		newPlayerUID = getNextSocket(connections);
	}
}

void NetworkComponent::tick()
{
	// Recieve packets from all connected users
	sf::Packet packet;
	string messageType;
	for (unsigned int uid = 0; uid < NumberOfPlayers; uid++)
	{
		if (connections.status[uid] == ConnectionStatus::Disconnected)
			continue;
		
		auto status = connections.socket[uid].receive(packet);
		if (status == sf::Socket::Status::Disconnected)
		{
			printf("NetworkComponent: Client disconnected uid=%u.\n", uid);
			connections.status[uid] = ConnectionStatus::Disconnected;

			_server->component_entity->onEntityRemoved(uid);

			continue;
		}

		packet >> messageType;
		if (messageType == "move-to-pos")
		{

		}
	}
}

void NetworkComponent::postTick()
{

}
