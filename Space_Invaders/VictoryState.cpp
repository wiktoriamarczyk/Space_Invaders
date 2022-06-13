#include "VictoryState.h"
#include "Engine.h"

VictoryState::VictoryState(shared_ptr<Font> MyFont, shared_ptr<PlayerData> MyPlayerData) : GameState(eStateID::VICTORY)
{
    m_Font = MyFont;
    m_PlayerData = MyPlayerData;
}

VictoryState::~VictoryState()
{
    FreeResources();
}

void VictoryState::Update(float DeltaTime) 
{
    m_TextureTimer -= DeltaTime;

    if (m_TextureTimer <= 0.5f)
    {
        m_MovementRect = { {0, 0}, {0.5, 1} };
    }
    if (m_TextureTimer <= 0)
    {
        m_MovementRect = { {0.5, 0}, {0.5, 1} };
        m_TextureTimer = 1.0f;
    }
}

void VictoryState::Render(SDL_Renderer* pRenderer)
{
    SDL_SetRenderDrawColor(pRenderer, 0, 0, 0, 255);
    SDL_RenderClear(pRenderer);

    if (m_GameOver)
    {
        m_Font->DrawText(pRenderer, 7, 140, 200, "GAME OVER!", Color{255, 1, 1});
        m_Font->DrawText(pRenderer, 2, 240, 330,  (m_PlayerData->GetName() + "'S SCORE: " + ToString(m_PlayerData->GetScore())).c_str());

        DisplayTexture("Boss.png", vec2i(60, 525), DisplayParameters{ .DisplaySize = vec2i(200, 100) });
        DisplayTexture("SpaceInvaders1.png", vec2i(300, 525), { .DisplaySize = vec2i(100,100) , .SrcTopLeft = m_MovementRect.TopLeft , .SrcSize = m_MovementRect.Size });
        DisplayTexture("SpaceInvaders2.png", vec2i(400, 525), { .DisplaySize = vec2i(100,100) , .SrcTopLeft = m_MovementRect.TopLeft , .SrcSize = m_MovementRect.Size });
        DisplayTexture("SpaceInvaders3.png", vec2i(500, 525), { .DisplaySize = vec2i(100,100) , .SrcTopLeft = m_MovementRect.TopLeft , .SrcSize = m_MovementRect.Size });
        DisplayTexture("SpaceInvaders4.png", vec2i(600, 525), { .DisplaySize = vec2i(100,100) , .SrcTopLeft = m_MovementRect.TopLeft , .SrcSize = m_MovementRect.Size });

        SDL_Rect TextRect = { 290, 430, 430, 75 };
        SDL_RenderDrawRect(pRenderer, &TextRect);

        m_Font->DrawText(pRenderer, 2, 300, 440, "WE HAVE WON, LOSER! ");
        m_Font->DrawText(pRenderer, 2, 300, 480, "PEACE WAS NEVER AN OPTION! ");

        m_Font->DrawText(pRenderer, 1, 290, 700, "CLICK ESC TO RETURN TO MENU");
    }
    else
    {
        m_Font->DrawText(pRenderer, 7, 170, 200, "VICTORY!");
        m_Font->DrawText(pRenderer, 2, 190, 330, (m_PlayerData->GetName() + "'S SCORE: " + ToString(m_PlayerData->GetScore())).c_str());

        DisplayTexture("Boss.png", vec2i(60, 525), DisplayParameters{ .DisplaySize = vec2i(200, 100) });
        DisplayTexture("Aureole.png", vec2i(85, 500), DisplayParameters{ .DisplaySize = vec2i(150, 50) });

        m_Font->DrawText(pRenderer, 2, 300, 500, "SORRY FOR THE INVASION.");
        m_Font->DrawText(pRenderer, 2, 300, 530, "IT WON'T HAPPEN AGAIN,");
        m_Font->DrawText(pRenderer, 2, 300, 560, "I PROMISE! :(");

        SDL_Rect TextRect = { 290, 490, 380, 100 };
        SDL_RenderDrawRect(pRenderer, &TextRect);

        m_Font->DrawText(pRenderer, 1, 290, 700, "CLICK ESC TO RETURN TO MENU");
    }

    SDL_RenderPresent(pRenderer);
}

void VictoryState::OnEnter()
{
    Mix_HaltChannel(-1);
    GameState::OnEnter();
    Engine::GetSingleton()->PlaySound("EndingMusic.wav");
}

void VictoryState::OnKeyDown(SDL_Scancode KeyCode)
{
    if (KeyCode == SDL_SCANCODE_ESCAPE)
    {
        Mix_HaltChannel(-1);
        FreeResources();
        Engine::GetSingleton()->PlaySound("8-bit_music.wav");
        m_NextStateID = eStateID::MAINMENU;
    }
}

void VictoryState::FreeResources()
{
    Engine::GetSingleton()->FreeSounds();
}
