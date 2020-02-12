#pragma once
#include "ServerComponent.h"
#include "Entity.h"
#include "Settings.h"
#include "SFML\Network.hpp"
#include <array>
#include <json.hpp>
#include <set>

using namespace std;
using namespace nlohmann;

enum struct ConnectionStatus
{
	Disconnected = 0,
	Connected = 1,
	Reconnecting = 2,
};

struct Connections
{
public:
	array<ConnectionStatus, NumberOfPlayers> status;
	array<sf::TcpSocket, NumberOfPlayers> socket;

	Connections();

	// Sends a json message to the given receiver
	void sendJson(const json& j, const Entity::UID receiver);

	// Sends a json message to all the players in the list of receivers
	void sendJson(const json& j, const set<Entity::UID> receivers);
};

class NetworkComponent : public ServerComponent
{
private:
	sf::TcpListener _listener;

public:
	Connections connections;

	NetworkComponent(const GameServer* server);
	~NetworkComponent();

	void preTick() override;
	sf::Socket::Status readMessageFromConnection(const Entity::UID& uid);
	void tick() override;
	void postTick() override;
};
