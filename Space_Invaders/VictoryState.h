#pragma once
#include "GameState.h"
#include "PlayerData.h"

class VictoryState : public GameState
{
public:
    VictoryState(shared_ptr<Font> MyFont, shared_ptr<PlayerData> MyPlayerData);
    ~VictoryState();
    void Update(float DeltaTime)override;
    void Render(SDL_Renderer* pRenderer)override;
    void OnEnter()override;
    void OnKeyDown(SDL_Scancode KeyCode)override;
    void FreeResources();

private:
    float                  m_TextureTimer = 0.f;
    Vec2Rect               m_MovementRect;
    shared_ptr<PlayerData> m_PlayerData;
};

