#pragma once
#include "Common.h"
#include "GameObject.h"
#include "Font.h"

class Engine;

class GameState
{
public:
    GameState(eStateID StateID);
    virtual void Update(float DeltaTime) = 0;
    virtual void Render(SDL_Renderer* pRenderer) = 0;
    virtual void OnKeyDown(SDL_Scancode KeyCode) {};
    eStateID GetStateID()const;
    eStateID GetNextStateID()const;
    virtual void OnEnter();

protected:
    eStateID m_NextStateID = eStateID::UNKNOWN;
    shared_ptr<Font> m_Font;

private:
    const eStateID m_StateID = eStateID::UNKNOWN;
};

