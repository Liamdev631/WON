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
		auto& playerEntity = _server->component_entity->initializePlayer(newPlayerUID);
		connections.status[newPlayerUID] = ConnectionStatus::Connected;
		connections.socket[newPlayerUID].setBlocking(false);
		printf("NetworkComponent: Client connected! uid=%u\n", newPlayerUID);
		_server->component_entity->broadcastEntityUpdate(newPlayerUID);

		json msg;
		msg["message"] = "hello-player";
		msg["uid"] = newPlayerUID;
		msg["x"] = playerEntity.position.x;
		msg["y"] = playerEntity.position.y;
		connections.sendJson(msg, newPlayerUID);

		newPlayerUID = getNextSocket(connections);
	}

	// Recieve packets from all connected users
	for (Entity::UID uid : _server->component_entity->getActivePlayers())
	{
		while (readMessageFromConnection(uid) == sf::Socket::Status::Done) {  }
	}
}

sf::Socket::Status NetworkComponent::readMessageFromConnection(const Entity::UID& uid)
{
	sf::Packet packet;
	auto status = connections.socket[uid].receive(packet);
	//printf("%u", status);
	switch (status)
	{
		case sf::Socket::Status::NotReady:
		{
			break;
		}

		case sf::Socket::Status::Disconnected:
		{
			// Disconnect signal received. Remove the player from the game.
			if (connections.status[uid] == ConnectionStatus::Disconnected)
				break;
			connections.status[uid] = ConnectionStatus::Disconnected;
			printf("NetworkComponent: Client disconnected uid=%u.\n", uid);
			_server->component_entity->removeEntity(uid);
			break;
		}

		case sf::Socket::Status::Done:
		{
			if (packet.getDataSize() > 0)
				connections.status[uid] = ConnectionStatus::Connected;
			else
				break;

			string s;
			packet >> s;
			json j = json::parse(s);

			string message = j["message"];
			if (message == "move-to-position")
			{
				auto& entity = _server->component_entity->getEntity(uid);
				const float x = j["x"];
				const float y = j["y"];
				entity.position = { x, y };
				_server->component_entity->setEntityUpdateFlag(uid);
			}
			else if (message == "login-info")
			{
				string username = j["username"];
				string password = j["password"];
				printf("uid: %u, user: %s, pass: %s.\n", uid, username.c_str(), password.c_str());
			}

			break;
		}

		default:
			break;
	}
	return status;
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

