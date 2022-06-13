#pragma once
#include "GameState.h"

class HowToPlayState : public GameState
{
public:
    HowToPlayState(shared_ptr<Font> MyFont);
    void Update(float DeltaTime)override;
    void Render(SDL_Renderer* pRenderer)override;
    void OnKeyDown(SDL_Scancode KeyCode)override;
    void OnEnter()override;
private:
};