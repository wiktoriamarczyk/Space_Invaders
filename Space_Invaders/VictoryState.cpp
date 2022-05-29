#include "VictoryState.h"
#include "Engine.h"

VictoryState::VictoryState(shared_ptr<Font> MyFont) : GameState(eStateID::VICTORY)
{
    m_Font = MyFont;
}

void VictoryState::Update(float DeltaTime) {}

void VictoryState::Render(SDL_Renderer* pRenderer)
{
    SDL_SetRenderDrawColor(pRenderer, 0, 0, 0, 255);
    SDL_RenderClear(pRenderer);

    if (m_GameOver)
    {
        m_Font->DrawText(pRenderer, 7, 140, 200, "GAME OVER!", Color{255.f, 1.f, 1.f});
    }
    else
    {
        m_Font->DrawText(pRenderer, 7, 170, 200, "VICTORY!");
        m_Font->DrawText(pRenderer, 3, 170, 350, "YOUR SCORE: " );

        DisplayTexture("Boss.png", vec2i(60, 525), DisplayParameters{ .DisplaySize = vec2i(200, 100) });
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
        m_NextStateID = eStateID::MAINMENU;
    }
}
