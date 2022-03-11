#include "HowToPlayState.h"
#include "Engine.h"

HowToPlayState::HowToPlayState(shared_ptr<Font> MyFont, SDL_Renderer* pRenderer) : GameState(eStateID::HOWTOPLAY)
{
    m_Font = MyFont;
    m_pRenderer = pRenderer;
}

void HowToPlayState::OnEnter()
{
    GameState::OnEnter();
}

void HowToPlayState::Update(float DeltaTime) {}

void HowToPlayState::Render()
{
    SDL_SetRenderDrawColor(m_pRenderer, 0, 0, 0, 255);
    SDL_RenderClear(m_pRenderer);

    m_Font->DrawText(m_pRenderer, 3, 30, 50, "KILL ALL SPACE INVADERS BEFORE");
    m_Font->DrawText(m_pRenderer, 3, 30, 90, "THEY KILL YOU!");

    m_Font->DrawText(m_pRenderer, 3, 300, 200, "CONTROLS:");
    m_Font->DrawText(m_pRenderer, 2, 110, 250, "<- / A - MOVE LEFT");
    m_Font->DrawText(m_pRenderer, 2, 110, 280, "-> / D - MOVE RIGHT");
    m_Font->DrawText(m_pRenderer, 2, 450, 250, "SPACE - SHOOT");
    m_Font->DrawText(m_pRenderer, 2, 450, 280, "ESC   - EXIT");

    m_Font->DrawText(m_pRenderer, 2, 350, 370, "= 10 POINTS");
    m_Font->DrawText(m_pRenderer, 2, 350, 420, "= 20 POINTS");
    m_Font->DrawText(m_pRenderer, 2, 350, 470, "= 30 POINTS");
    m_Font->DrawText(m_pRenderer, 2, 350, 520, "=? MYSTERY");

    SDL_Rect srcrect = { 0, 0, 26, 26 };

    SDL_Rect dstrect = { 280, 350, OBJECT_WIDTH, OBJECT_HEIGHT};
    DisplayTexture("SpaceInvaders1.png", srcrect, dstrect);

    dstrect = { 280, 400, OBJECT_WIDTH, OBJECT_HEIGHT };
    DisplayTexture("SpaceInvaders2.png", srcrect, dstrect);

    dstrect = { 280, 450, OBJECT_WIDTH, OBJECT_HEIGHT };
    DisplayTexture("SpaceInvaders3.png", srcrect, dstrect);

    DisplayTexture("Boss.png", vec2i(280, 510));

    SDL_RenderPresent(m_pRenderer);
}

void HowToPlayState::OnKeyDown(SDL_Scancode KeyCode)
{
    // jesli gracz wciska esc, wywolaj zamkniecie programu
    if (KeyCode == SDL_SCANCODE_ESCAPE)
    {
        m_NextStateID = eStateID::MAINMENU;
    }
}