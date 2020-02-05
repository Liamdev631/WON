#pragma once

class GameServer;

class ServerComponent
{
protected:
	const GameServer* _server;

public:
	ServerComponent(const GameServer* server)
		: _server(server)
	{

	}

	virtual void preTick() = 0;
	virtual void tick() = 0;
	virtual void postTick() = 0;
};
