#pragma once
#include "GameState.h"

class HowToPlayState : public GameState
{
public:
    HowToPlayState(shared_ptr<Font> MyFont, SDL_Renderer* pRenderer);
    ~HowToPlayState();
    void InitializeTextures();
    void DestroyTextures();
    void Update(float DeltaTime)override;
    void Render()override;
    void OnKeyDown(SDL_Scancode KeyCode)override;
    void OnEnter()override;
private:
    int m_Option = 0;
    SDL_Texture* m_FirstInvader = nullptr;
    SDL_Texture* m_SecondInvader = nullptr;
    SDL_Texture* m_ThirdInvader = nullptr;
    SDL_Texture* m_Boss = nullptr;
};

