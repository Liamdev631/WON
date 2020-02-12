#pragma once
#include "ClientComponent.h"
#include <SFML\Network.hpp>
#include <json.hpp>

using namespace nlohmann;

enum struct ConnectionStatus
{
	Disconnected = 0,
	Connected = 1,
	Reconnecting = 2,
};

class NetworkComponent : public ClientComponent
{
private:
	sf::TcpSocket _socket;
	ConnectionStatus _connectionStatus;

public:
	NetworkComponent(const GameClient* server);
	~NetworkComponent();

	void preTick() override;
	void tick() override;
	void postTick() override;

	void sendJson(json& j);
};

