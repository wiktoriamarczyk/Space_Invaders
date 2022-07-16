#include "InGameState.h"
#include "Engine.h"
#include "SpaceInvader.h"
#include "Gun.h"
#include "Shield.h"

InGameState::InGameState(shared_ptr<Font> MyFont, SDL_Renderer* pRenderer) : GameState(eStateID::INGAME)
{
    m_Font = MyFont;
    m_pRenderer = pRenderer;
    // przy kazdym tworzeniu InGameState wywoluj tworzenie obiektow gry

}

InGameState::~InGameState()
{
    SDL_DestroyTexture(m_GunIconTexture);
    m_GunIconTexture = nullptr;
    SpaceInvader::DestroyTextures();
    Shield::DestroyTexture();
}

void InGameState::InitializeInGameStateTextures()
{
    SDL_Surface* m_pImage = IMG_Load("../Data/Icon.png");
    m_GunIconTexture = SDL_CreateTextureFromSurface(m_pRenderer, m_pImage);
    SDL_FreeSurface(m_pImage);

    // inicjalizacja tarcz
    Shield::InitializeShieldTexture(m_pRenderer);

    // inicjalizacja Space Invaderow
    SpaceInvader::InitializeSpaceInvaderTexture(m_pRenderer);
}

void InGameState::Update(float DeltaTime)
{
    if (SDL_IsKeyPressed(SDL_SCANCODE_ESCAPE))
    {
        m_NextStateID = eStateID::MAINMENU;
    }

    if (Gun::m_NumOfLives <= 0)
    {
        //==TODO==
        Engine::GetSingleton()->ExitGame();
    }

    for (int i = 0; i < m_AllGameObjects.size();)
    {
        m_AllGameObjects[i]->Update(DeltaTime);
    
        if (m_AllGameObjects[i]->GetObjectStatus() == false)
        {
            m_AllGameObjects.erase(m_AllGameObjects.begin() + i);
        }
        else
        {
            ++i;
        }
    }
}

void InGameState::Render()
{
    SDL_SetRenderDrawColor(m_pRenderer, 0, 0, 0, 255);
    SDL_RenderClear(m_pRenderer);

    // render wszystkich obiektow
     for (int i = 0; i < m_AllGameObjects.size(); ++i)
     {
         m_AllGameObjects[i]->Render(m_pRenderer);
     }
    
    SDL_Rect dstrect = {};
    SDL_Rect srcrect = {};

    switch (Gun::m_NumOfLives)
    {
    case 3:
        dstrect = { 600, 40, 100, 25 };
        srcrect = { 0, 0, 1500, 300 };
        break;
    case 2:
        dstrect = { 600, 40, 75, 25 };
        srcrect = { 0, 0, 960, 300 };
        break;
    case 1:
        dstrect = { 600, 40, 50, 25 };
        srcrect = { 0, 0, 480, 300 };
        break;
    case 0:
        dstrect = { 0, 0, 0, 0 };
        break;
    }

    SDL_RenderCopy(m_pRenderer, m_GunIconTexture, &srcrect, &dstrect);

    m_Font->DrawText(m_pRenderer, 3, 10, 10, "SCORE:");
    m_Font->DrawText(m_pRenderer, 3, 10, 40, ToString(SpaceInvader::m_NumOfPoints).c_str());
    m_Font->DrawText(m_pRenderer, 3, 250, 10, "HI-SCORE:");
    m_Font->DrawText(m_pRenderer, 3, 600, 10, "LIVES:");

    SDL_RenderPresent(m_pRenderer);
}

void InGameState::CreateObject()
{
    m_AllGameObjects.clear();
    SpaceInvader::m_NumOfPoints = 0;
    SpaceInvader::m_NumOfInvaders = 0;
    Gun::m_NumOfLives = 3;

    // inicjalizacja broni
    shared_ptr<Gun> MyGun = make_shared<Gun>();
    MyGun->InitializeGun(m_pRenderer, SCREEN_WIDTH / 2, SCREEN_HEIGHT - OBJECT_HEIGHT);

    float PosX = 0.0f, PosY = 0.0f;

    for (int ROW = 0; ROW < 4; ++ROW)
    {
        PosX = ROW * 4.2f * OBJECT_WIDTH + OBJECT_WIDTH;
        PosY = SCREEN_HEIGHT - 3 * OBJECT_HEIGHT;
        m_AllGameObjects.push_back(make_shared<Shield>(PosX, PosY, MyGun));
    }

    for (int COLUMN = 0; COLUMN < 5; ++COLUMN)
    {
        for (int ROW = 0; ROW < SCREEN_WIDTH / OBJECT_WIDTH - 3; ++ROW)
        {
            PosX = float(ROW * OBJECT_WIDTH + OBJECT_WIDTH / 2 + ROW * (SCREEN_WIDTH / 100));
            PosY = float(SCREEN_HEIGHT / 6 + COLUMN * OBJECT_HEIGHT);
            m_AllGameObjects.push_back(make_shared<SpaceInvader>(PosX, PosY, MyGun));
        }
    }

    m_AllGameObjects.push_back(move(MyGun));
}

// SCREEN_WIDTH / INVADER_WIDTH - 3: 12 invaderow po 50 pikseli (lacznie zajmuja 600 pikseli)
// ROW * (SCREEN_WIDTH / 100): z odstepami po 8 pikseli miedzy kazdym (lacznie 100 pikseli)
// z 50 pikselowymi przerwami na poczatku i koncu ekranu (100 pikseli)
// 800 pikseli szerokosci ekranu

void InGameState::OnEnter()
{
    GameState::OnEnter();
    InitializeInGameStateTextures();
    CreateObject();
}