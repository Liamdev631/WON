#include "Input.h"
#include "GameClient.h"
#include "GameStateComponent.h"
#include "EntityModel.h"
#include "EntityComponent.h"
#include "ClientComponent.h"

Input::Input(const GameClient* client)
    : IEventReceiver(), _client(client)
{
    for (u32 i = 0; i < KEY_KEY_CODES_COUNT; ++i)
        _keyIsDown[i] = false;
}

bool Input::OnEvent(const SEvent& event)
{
    if (event.EventType == irr::EET_KEY_INPUT_EVENT)
        _keyIsDown[event.KeyInput.Key] = event.KeyInput.PressedDown;
    return false;
}

bool Input::IsKeyDown(EKEY_CODE keyCode) const
{
    return _keyIsDown[keyCode];
}

InputComponent::InputComponent(const GameClient* client)
    : ClientComponent(client), input(client)
{

}

void InputComponent::preTick()
{

}

void InputComponent::tick()
{
    float moveSpeed = 0.05f;
    float dt = 1;
    auto thisPlayersEntity = _client->component_gameState->thisPlayersEntity;
    if (thisPlayersEntity)
    {
        if (input.IsKeyDown(KEY_KEY_D))
            thisPlayersEntity->position.x += moveSpeed * dt;
        if (input.IsKeyDown(KEY_KEY_A))
            thisPlayersEntity->position.x -= moveSpeed * dt;
        if (input.IsKeyDown(KEY_KEY_W))
            thisPlayersEntity->position.y += moveSpeed * dt;
        if (input.IsKeyDown(KEY_KEY_S))
            thisPlayersEntity->position.y -= moveSpeed * dt;
    }
}

void InputComponent::postTick()
{

}
