#include "pch.h"
#include "CppUnitTest.h"
#include "../NennServer/GameServer.h"
#include "../NennClient/GameClient.h"

using namespace Microsoft::VisualStudio::CppUnitTestFramework;

namespace NennTesting
{
	TEST_CLASS(NennTesting)
	{
	private:


	public:
		
		TEST_METHOD(TestCreateNetwork)
		{
			GameServer server;
			server.tick();

			GameClient client;
			client.tick();
		}
	};
}
