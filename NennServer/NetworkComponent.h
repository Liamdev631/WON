#pragma once
#include "ServerComponent.h"
#include "Entity.h"
#include "Settings.h"
#include "SFML\Network.hpp"
#include <array>

using namespace std;

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

	Connections()
		: status({})
	{
		for (int i = 0; i < NumberOfPlayers; i++)
		{
			status[i] = ConnectionStatus::Disconnected;
			socket[i].setBlocking(false);
		}
	}
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
	void tick() override;
	void postTick() override;
};
