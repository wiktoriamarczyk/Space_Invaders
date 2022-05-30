#pragma once
#include "GameState.h"
#include "Font.h"
#include "PlayerData.h"

class SetupState : public GameState
{
public:
    SetupState(shared_ptr<Font> MyFont, shared_ptr<PlayerData> MyPlayerData);
    void Update(float DeltaTime);
    void Render(SDL_Renderer* pRenderer);
    void OnEnter();
    void OnKeyDown(SDL_Scancode KeyCode);
    void OnMouseButtonDown(int Button);

    void UpdatePlayerName(string& PlayerName, char Character);

private:
    shared_ptr<PlayerData> m_PlayerData;
};

