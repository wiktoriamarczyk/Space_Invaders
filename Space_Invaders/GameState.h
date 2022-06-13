#pragma once
import Module_Common;
#include "Font.h"
#include "vec2.h" 

class Engine;

class GameState
{
public:
    GameState(eStateID StateID);
    virtual void Update(float DeltaTime) = 0;
    virtual void Render(SDL_Renderer* pRenderer) = 0;
    virtual void OnEnter();
    virtual void OnKeyDown(SDL_Scancode KeyCode) {};
    virtual void OnMouseButtonDown(int Button) {};
    eStateID GetStateID()const;
    eStateID GetNextStateID()const;
    void DisplayTexture(const string& FileName, vec2 Position, DisplayParameters Param = {});

protected:
    eStateID           m_NextStateID = eStateID::UNKNOWN;
    shared_ptr<Font>   m_Font;
    static bool        m_GameOver;

private:
    const eStateID     m_StateID = eStateID::UNKNOWN;
};

