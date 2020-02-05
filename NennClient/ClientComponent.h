#pragma once

class GameClient;

class ClientComponent
{
protected:
	const GameClient* _client;

public:
	ClientComponent(const GameClient* client)
		: _client(client)
	{

	}

	virtual void preTick() = 0;
	virtual void tick() = 0;
	virtual void postTick() = 0;
};
