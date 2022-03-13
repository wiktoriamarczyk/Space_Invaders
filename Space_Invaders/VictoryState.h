#pragma once
#include "GameState.h"

class VictoryState : public GameState
{
public:
    VictoryState(shared_ptr<Font> MyFont, SDL_Renderer* pRenderer);
    void Update(float DeltaTime)override;
    void Render()override;
    void OnEnter()override;
    void OnKeyDown(SDL_Scancode KeyCode)override;

private:
};

