#pragma once
#include "GameState.h"

class MainMenuState : public GameState
{
public:
    MainMenuState(shared_ptr<Font> MyFont);
    void Update(float DeltaTime)override;
    void Render(SDL_Renderer* pRenderer)override;
    void OnKeyDown(SDL_Scancode KeyCode)override;
    void OnEnter()override;
private:
    int                  m_Option = 0;
    bool                 m_PlayMusicAgain = true;
};

