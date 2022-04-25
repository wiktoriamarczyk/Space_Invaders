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
        m_Font->DrawText(pRenderer, 7, 180, 100, "GAME OVER!");
        DisplayTexture("Boss.png", vec2i(30, 300), DisplayParameters{.DisplaySize = vec2i(200, 100) });

        m_Font->DrawText(pRenderer, 2, 260, 300, "BUT THERE'S NO SENSE CRYING.");
        m_Font->DrawText(pRenderer, 2, 260, 320, "OVER EVERY MISTAKE.");
        m_Font->DrawText(pRenderer, 2, 260, 340, "YOU JUST KEEP ON TRYING.");
        m_Font->DrawText(pRenderer, 2, 260, 360, "TILL YOU RUN OUT OF CAKE.");
        m_Font->DrawText(pRenderer, 2, 260, 380, "^_^");
        m_Font->DrawText(pRenderer, 1, 290, 550, "CLICK ESC TO RETURN TO MENU");

        SDL_Rect TextRect = { 250, 290, 510, 130};
        SDL_RenderDrawRect(pRenderer, &TextRect);
    }
    else
    {
        m_Font->DrawText(pRenderer, 7, 180, 100, "VICTORY!");
        DisplayTexture("Boss.png", vec2i(30, 300), DisplayParameters{ .DisplaySize = vec2i(200, 100) });

        m_Font->DrawText(pRenderer, 2, 260, 300, "I'M NOT EVEN ANGRY.");
        m_Font->DrawText(pRenderer, 2, 260, 320, "I'M BEING SO SINCERE RIGHT NOW.");
        m_Font->DrawText(pRenderer, 2, 260, 340, "EVEN THOUGH YOU BROKE MY HEART.");
        m_Font->DrawText(pRenderer, 2, 260, 360, "AND KILLED ME.");
        m_Font->DrawText(pRenderer, 1, 260, 400, "OH, BY THE WAY, THE CAKE IS GREAT ^_^");
        m_Font->DrawText(pRenderer, 1, 290, 550, "CLICK ESC TO RETURN TO MENU");

        SDL_Rect TextRect = { 250, 290, 510, 130 };
        SDL_RenderDrawRect(pRenderer, &TextRect);
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
