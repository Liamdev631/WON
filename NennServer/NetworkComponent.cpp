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
		printf("NetworkComponent: Client connected! uid=%u\n", newPlayerUID);

		json msg;
		msg["message"] = "hello-player";
		msg["uid"] = newPlayerUID;
		connections.sendJson(msg, newPlayerUID);
		_server->component_entity->setupNewEntity(newPlayerUID);

		newPlayerUID = getNextSocket(connections);
	}

	// Recieve packets from all connected users
	sf::Packet packet;
	string messageType;
	for (Entity::UID uid = 0; uid < NumberOfPlayers; uid++)
	{
		if (connections.status[uid] == ConnectionStatus::Disconnected)
			continue;

		// Grab the packet
		auto status = connections.socket[uid].receive(packet);
		if (status == sf::Socket::Status::Disconnected)
		{
			printf("NetworkComponent: Client disconnected uid=%u.\n", uid);
			connections.status[uid] = ConnectionStatus::Disconnected;
			_server->component_entity->removeEntity(uid);
			continue;
		}
		else if (status == sf::Socket::Status::Done)
		{
			// Convert the packet to json
			string packetString;
			packet >> packetString;
			json j = json::parse(packetString);
			string message = j["message"];
			if (message == "move-to-position")
			{
				auto& entity = _server->component_entity->getEntity(uid);
				entity.position.x = j["x"];
				entity.position.y = j["y"];
			}
		}
	}
}

void NetworkComponent::tick()
{

}

void NetworkComponent::postTick()
{

}

Connections::Connections()
	: status({})
{
	for (int i = 0; i < NumberOfPlayers; i++)
	{
		status[i] = ConnectionStatus::Disconnected;
		socket[i].setBlocking(false);
	}
}

void Connections::sendJson(const json& j, const Entity::UID receiver)
{
	if (status[receiver] == ConnectionStatus::Disconnected)
		return;

	// send json through packet
	sf::Packet packet;
	packet << j.dump(-1, ' ', true);
		socket[receiver].send(packet);
	return;
}

void Connections::sendJson(const json& j, const set<Entity::UID> receivers)
{
	// send json through packet
	sf::Packet packet;
	packet << j.dump(-1, ' ', true);
	for (const Entity::UID player : receivers)
		socket[player].send(packet);
	return;
}

