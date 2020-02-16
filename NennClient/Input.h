#pragma once
#include "Irrlicht\irrlicht.h"
#include "ClientComponent.h"

using namespace irr;

class GameClient;

typedef core::position2di MousePos;

class Input : public IEventReceiver
{
private:
    const GameClient* _client;

    // We use this array to store the current state of each key
    bool _keyIsDown[KEY_KEY_CODES_COUNT];

public:
    struct SMouseState
    {
        MousePos Position;
        bool LeftButtonDown;
        SMouseState() : LeftButtonDown(false) { }
    } MouseState, PreviousMouseState;

    Input(const GameClient* client);

    // This is the one method that we have to implement
    bool OnEvent(const SEvent& event) override;

    // This is used to check whether a key is being held down
    virtual bool IsKeyDown(EKEY_CODE keyCode) const;

    MousePos getMouseCenter();
    void recenterMouse();
};

class InputComponent : public ClientComponent
{
public:
    Input input;

    InputComponent(const GameClient* client);

    void preTick() override;
    void tick() override;
    void postTick() override;

};