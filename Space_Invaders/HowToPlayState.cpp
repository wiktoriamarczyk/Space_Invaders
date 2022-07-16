#include "HowToPlayState.h"
#include "Engine.h"

HowToPlayState::HowToPlayState(shared_ptr<Font> MyFont, SDL_Renderer* pRenderer) : GameState(eStateID::HOWTOPLAY)
{
    m_Font = MyFont;
    m_pRenderer = pRenderer;
    InitializeTextures();
}

HowToPlayState::~HowToPlayState()
{
    DestroyTextures();
}

void HowToPlayState::InitializeTextures()
{
    SDL_Surface* pImage = IMG_Load("../Data/SpaceInvaders1.png");
    m_FirstInvader = SDL_CreateTextureFromSurface(m_pRenderer, pImage);
    SDL_FreeSurface(pImage);

    pImage = IMG_Load("../Data/SpaceInvaders2.png");
    m_SecondInvader = SDL_CreateTextureFromSurface(m_pRenderer, pImage);
    SDL_FreeSurface(pImage);

    pImage = IMG_Load("../Data/SpaceInvaders3.png");
    m_ThirdInvader = SDL_CreateTextureFromSurface(m_pRenderer, pImage);
    SDL_FreeSurface(pImage);

    pImage = IMG_Load("../Data/SpaceInvaders4.png");
    m_Boss = SDL_CreateTextureFromSurface(m_pRenderer, pImage);
    SDL_FreeSurface(pImage);
}

void HowToPlayState::DestroyTextures()
{
    SDL_DestroyTexture(m_FirstInvader);
    m_FirstInvader = nullptr;
    SDL_DestroyTexture(m_SecondInvader);
    m_SecondInvader = nullptr;
    SDL_DestroyTexture(m_ThirdInvader);
    m_ThirdInvader = nullptr;
    SDL_DestroyTexture(m_Boss);
    m_Boss = nullptr;
}

void HowToPlayState::Update(float DeltaTime)
{

}

void HowToPlayState::Render()
{
    SDL_SetRenderDrawColor(m_pRenderer, 0, 0, 0, 255);
    SDL_RenderClear(m_pRenderer);

    m_Font->DrawText(m_pRenderer, 3, 30, 50, "KILL ALL SPACE INVADERS BEFORE");
    m_Font->DrawText(m_pRenderer, 3, 30, 90, "THEY KILL YOU!");

    m_Font->DrawText(m_pRenderer, 3, 300, 200, "CONTROLS:");
    m_Font->DrawText(m_pRenderer, 2, 150, 250, "A - MOVE LEFT");
    m_Font->DrawText(m_pRenderer, 2, 150, 280, "D - MOVE RIGHT");
    m_Font->DrawText(m_pRenderer, 2, 450, 250, "SPACE - SHOOT");
    m_Font->DrawText(m_pRenderer, 2, 450, 280, "ESC   - EXIT");

    m_Font->DrawText(m_pRenderer, 2, 350, 370, "= 10 POINTS");
    m_Font->DrawText(m_pRenderer, 2, 350, 420, "= 20 POINTS");
    m_Font->DrawText(m_pRenderer, 2, 350, 470, "= 30 POINTS");
    m_Font->DrawText(m_pRenderer, 2, 350, 520, "=? MYSTERY");

    SDL_Rect srcrect1 = { 0, 0, 26, 26 };

    SDL_Rect dstrect = { 280, 350, OBJECT_WIDTH, OBJECT_HEIGHT};
    SDL_RenderCopy(m_pRenderer, m_FirstInvader, &srcrect1, &dstrect);

    dstrect = { 280, 400, OBJECT_WIDTH, OBJECT_HEIGHT };
    SDL_RenderCopy(m_pRenderer, m_SecondInvader, &srcrect1, &dstrect);

    dstrect = { 280, 450, OBJECT_WIDTH, OBJECT_HEIGHT };
    SDL_RenderCopy(m_pRenderer, m_ThirdInvader, &srcrect1, &dstrect);

    dstrect = { 280, 510, OBJECT_WIDTH, OBJECT_HEIGHT / 2 };
    SDL_RenderCopy(m_pRenderer, m_Boss, NULL, &dstrect);

    SDL_RenderPresent(m_pRenderer);
}

void HowToPlayState::OnKeyDown(SDL_Scancode KeyCode)
{
    // jesli gracz wciska esc, wywolaj zamkniecie programu
    if (KeyCode == SDL_SCANCODE_ESCAPE)
    {
        DestroyTextures();
        m_NextStateID = eStateID::MAINMENU;
    }
}

void HowToPlayState::OnEnter()
{
    GameState::OnEnter();
    // inicjalizacja zasobow
    InitializeTextures();
}