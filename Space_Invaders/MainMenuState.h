#pragma once
#include "GameState.h"

class MainMenuState : public GameState
{
public:
    MainMenuState(shared_ptr<Font> MyFont, SDL_Renderer* pRenderer);
    ~MainMenuState();
    void InitializeMainMenuStateTextures();
    void Update(float DeltaTime)override;
    void Render()override;
    void OnKeyDown(SDL_Scancode KeyCode)override;
    void OnEnter()override;
private:
    int m_Option = 0;
    SDL_Texture* m_WelcomeInvaderTexture = nullptr;
    bool m_PlayMusicAgain = true;
};

