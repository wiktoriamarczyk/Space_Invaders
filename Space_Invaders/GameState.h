#pragma once
#include "Common.h"
#include "Font.h"
#include "vec2.h" 

class Engine;

class GameState
{
public:
    GameState(eStateID StateID);
    virtual void Update(float DeltaTime) = 0;
    virtual void Render() = 0;
    virtual void OnEnter();
    virtual void OnKeyDown(SDL_Scancode KeyCode) {};
    virtual void OnMouseButtonDown(int Button) {};
    eStateID GetStateID()const;
    eStateID GetNextStateID()const;
    void DisplayTexture(const string& FileName, vec2i Position, optional<vec2i> Size = nullopt);
    void DisplayTexture(const string& FileName, SDL_Rect srcrect, SDL_Rect dstrect);

protected:
    SDL_Renderer*    m_pRenderer = nullptr;
    eStateID         m_NextStateID = eStateID::UNKNOWN;
    shared_ptr<Font> m_Font;
    static bool      m_GameOver;

private:
    const eStateID   m_StateID = eStateID::UNKNOWN;
};
