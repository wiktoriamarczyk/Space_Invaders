#pragma once
#include "GameState.h"

class VictoryState : public GameState
{
public:
    VictoryState(shared_ptr<Font> MyFont);
    void Update(float DeltaTime)override;
    void Render(SDL_Renderer* pRenderer)override;
    void OnEnter()override;
    void OnKeyDown(SDL_Scancode KeyCode)override;

private:
};

