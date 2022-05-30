#include "SetupState.h"

SetupState::SetupState(shared_ptr<Font> MyFont, shared_ptr<PlayerData> MyPlayerData) : GameState(eStateID::SETUP)
{
    m_Font = MyFont;
    m_PlayerData = MyPlayerData;
}

void SetupState::Update(float DeltaTime) {}

void SetupState::Render(SDL_Renderer* pRenderer)
{
    SDL_SetRenderDrawColor(pRenderer, 0, 0, 0, 255);
    SDL_RenderClear(pRenderer);

    DisplayTexture("SpaceInvader.png", vec2(300, 140), DisplayParameters{ .DisplaySize = vec2i(200, 200) });

    m_Font->DrawText(pRenderer, 4, 150, 350, "ENTER YOUR NAME:");
    m_Font->DrawText(pRenderer, 4, 220, 450, m_PlayerData->GetName().c_str());
    m_Font->DrawText(pRenderer, 1, 230, 600, "CLICK ENTER TO PLAY     ESC TO RETURN TO MENU");

    SDL_Rect TextRect = { 150, 430, 500, 75 };
    SDL_RenderDrawRect(pRenderer, &TextRect);

    SDL_RenderPresent(pRenderer);
}

void SetupState::OnEnter()
{
    m_PlayerData->SetName({});
    GameState::OnEnter();
}

void SetupState::OnKeyDown(SDL_Scancode KeyCode)
{
    string PlayerName = m_PlayerData->GetName();

    if (KeyCode == SDL_SCANCODE_BACKSPACE && PlayerName.size() > 0)
    {
        PlayerName.erase(PlayerName.size() - 1);
    }
    else if (KeyCode >= SDL_SCANCODE_A && KeyCode <= SDL_SCANCODE_Z)
    {
        UpdatePlayerName(PlayerName, KeyCode + 61);
    }
    else if (KeyCode >= SDL_SCANCODE_1 && KeyCode <= SDL_SCANCODE_9)
    {
        UpdatePlayerName(PlayerName, KeyCode + 19);
    }
    else if (KeyCode == SDL_SCANCODE_0)
    {
        UpdatePlayerName(PlayerName, KeyCode + 9);
    }

    m_PlayerData->SetName(PlayerName);

    if (!PlayerName.empty() && KeyCode == SDL_SCANCODE_RETURN)
    {
        m_NextStateID = eStateID::INGAME;
        Mix_HaltChannel(-1);
    }
    else if (KeyCode == SDL_SCANCODE_ESCAPE)
    {
        m_NextStateID = eStateID::MAINMENU;
    }
}

void SetupState::OnMouseButtonDown(int Button) {}

void SetupState::UpdatePlayerName(string& PlayerName, char Character)
{
    regex RegexTest("[A-Z]{1,8}[0-9]{0,3}");

    if (regex_match(PlayerName + Character, RegexTest))
    {
        PlayerName += Character;
    }
}
