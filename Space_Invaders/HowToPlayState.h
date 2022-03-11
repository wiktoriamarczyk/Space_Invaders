#pragma once
#include "GameState.h"

class HowToPlayState : public GameState
{
public:
    HowToPlayState(shared_ptr<Font> MyFont, SDL_Renderer* pRenderer);
    void Update(float DeltaTime)override;
    void Render()override;
    void OnKeyDown(SDL_Scancode KeyCode)override;
    void OnEnter()override;
private:
};

