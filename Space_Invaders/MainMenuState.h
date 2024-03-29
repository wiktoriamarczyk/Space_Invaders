#pragma once
#include "GameState.h"

class MainMenuState : public GameState
{
public:
    MainMenuState(shared_ptr<Font> MyFont);
    ~MainMenuState();
    void Update(float DeltaTime)override;
    void Render(SDL_Renderer* pRenderer)override;
    void OnKeyDown(SDL_Scancode KeyCode)override;
    void OnEnter()override;
    void FreeResources();

private:
    int                  m_Option = 0;
    bool                 m_PlayMusicAgain = true;
    float                m_ColorTimer = 0.0f;
    Color                m_TxtColor = Color::WHITE;
};