#include "HowToPlayState.h"
#include "Engine.h"

HowToPlayState::HowToPlayState(shared_ptr<Font> MyFont) : GameState(eStateID::HOWTOPLAY)
{
    m_Font = MyFont;
}

void HowToPlayState::OnEnter()
{
    GameState::OnEnter();
}

void HowToPlayState::Update(float DeltaTime) {}

void HowToPlayState::Render(SDL_Renderer* pRenderer)
{
    SDL_SetRenderDrawColor(pRenderer, 0, 0, 0, 255);
    SDL_RenderClear(pRenderer);

    m_Font->DrawText(pRenderer, 3, 40, 50, "KILL ALL SPACE INVADERS BEFORE");
    m_Font->DrawText(pRenderer, 3, 40, 90, "THEY KILL YOU!");

    m_Font->DrawText(pRenderer, 3, 300, 200, "CONTROLS:");
    m_Font->DrawText(pRenderer, 2, 110, 250, "<- / A - MOVE LEFT");
    m_Font->DrawText(pRenderer, 2, 110, 280, "-> / D - MOVE RIGHT");
    m_Font->DrawText(pRenderer, 2, 450, 250, "SPACE - SHOOT");
    m_Font->DrawText(pRenderer, 2, 450, 280, "ESC   - EXIT");

    m_Font->DrawText(pRenderer, 2, 350, 370, "= 10 POINTS");
    m_Font->DrawText(pRenderer, 2, 350, 420, "= 15 POINTS");
    m_Font->DrawText(pRenderer, 2, 350, 470, "= 20 POINTS");
    m_Font->DrawText(pRenderer, 2, 350, 520, "= 30 POINTS");
    m_Font->DrawText(pRenderer, 2, 350, 570, "=? MYSTERY");


    vec2i Size(OBJECT_WIDTH, OBJECT_HEIGHT);
    DisplayTexture("SpaceInvaders4.png", vec2(280, 350), DisplayParameters{.DisplaySize = Size, .SrcSize = vec2(0.5f, 1.0f)});
    DisplayTexture("SpaceInvaders3.png", vec2(280, 400), DisplayParameters{.DisplaySize = Size, .SrcSize = vec2(0.5f, 1.0f)});
    DisplayTexture("SpaceInvaders2.png", vec2(280, 450), DisplayParameters{.DisplaySize = Size, .SrcSize = vec2(0.5f, 1.0f)});
    DisplayTexture("SpaceInvaders1.png", vec2(280, 500), DisplayParameters{ .DisplaySize = Size, .SrcSize = vec2(0.5f, 1.0f) });
    DisplayTexture("Boss.png", vec2i(280, 560));

    m_Font->DrawText(pRenderer, 2, 40, 660, "COLLECT POWER UPS FROM INVADERS BUT DON'T BE ");
    m_Font->DrawText(pRenderer, 2, 40, 700, "TOO GREEDY, IT'S DANGEROUS! ;)");

    SDL_RenderPresent(pRenderer);
}

void HowToPlayState::OnKeyDown(SDL_Scancode KeyCode)
{
    // jesli gracz wciska esc, wywolaj zamkniecie programu
    if (KeyCode == SDL_SCANCODE_ESCAPE)
    {
        m_NextStateID = eStateID::MAINMENU;
    }
}