#include "UserInputComponent.h"
#include "GameClient.h"

UserInputComponent::UserInputComponent(const GameClient* client)
	: ClientComponent(client)
{

}

UserInputComponent::~UserInputComponent()
{

}

void UserInputComponent::preTick()
{

}

void UserInputComponent::tick()
{

}

void UserInputComponent::postTick()
{

}

bool UserInputComponent::OnEvent(const SEvent& event)
{


    return false;
}
