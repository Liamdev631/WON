#include "Input.h"
#include "GameClient.h"
#include "GameStateComponent.h"
#include "EntityModel.h"
#include "EntityComponent.h"
#include "ClientComponent.h"
#include "GraphicsComponent.h"
#include "CameraComponent.h"

Input::Input(const GameClient* client)
    : IEventReceiver(), _client(client)
{
    for (u32 i = 0; i < KEY_KEY_CODES_COUNT; ++i)
        _keyIsDown[i] = false;
}

bool Input::OnEvent(const SEvent& event)
{
    switch (event.EventType)
    {
        case irr::EET_KEY_INPUT_EVENT:
        {
            _keyIsDown[event.KeyInput.Key] = event.KeyInput.PressedDown;

            switch (event.KeyInput.Key)
            {
                case KEY_ESCAPE:
                    exit(0);
                    break;
            }

            break;
        }

        case irr::EET_MOUSE_INPUT_EVENT:
        {
            switch (event.MouseInput.Event)
            {
                case EMIE_LMOUSE_PRESSED_DOWN:
                    MouseState.LeftButtonDown = true;
                    break;

                case EMIE_LMOUSE_LEFT_UP:
                    MouseState.LeftButtonDown = false;
                    break;

                case EMIE_MOUSE_MOVED:
                    MouseState.Position.X = event.MouseInput.X;
                    MouseState.Position.Y = event.MouseInput.Y;
                    break;

                default:
                    break;
            }
            break;
        }

        default:
            break;
    }

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
    auto thisPlayersEntity = _client->component_gameState->thisPlayersEntity;
    if (thisPlayersEntity)
    {
        // Move the player model with user input
        float moveSpeed = 0.02f;
        float dt = 1;

        auto thisPlayersModel = _client->component_gameState->thisPlayersModel;
        if (thisPlayersModel)
        {
            vec2f moveAmount = { 0, 0 };
            if (input.IsKeyDown(KEY_KEY_D))
                moveAmount.x += 1;
            if (input.IsKeyDown(KEY_KEY_A))
                moveAmount.x -= 1;
            if (input.IsKeyDown(KEY_KEY_W))
                moveAmount.y += 1;
            if (input.IsKeyDown(KEY_KEY_S))
                moveAmount.y -= 1;
            moveAmount = moveAmount * moveSpeed * dt;
            float theta = (_client->component_camera->Direction + 90) * PI / 180;
            vec2f rotatedMove;
            rotatedMove.x = (moveAmount.x * cos(theta)) + (moveAmount.y * sin(theta));
            rotatedMove.y = (moveAmount.x * -sin(theta)) + (moveAmount.y * cos(theta));
            thisPlayersModel->move(rotatedMove);
        }
    }
}

void InputComponent::postTick()
{

}

MousePos Input::getMouseCenter()
{
    auto size = _client->component_graphics->getDriver()->getScreenSize();
    MousePos pos;
    pos.X = size.Width / 2;
    pos.Y = size.Height / 2;
    return pos;
}

void Input::recenterMouse()
{
    auto cursor = _client->component_graphics->getDevice()->getCursorControl();
    cursor->setPosition(getMouseCenter());
}
