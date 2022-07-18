#include "InGameState.h"
#include "Engine.h"
#include "SpaceInvader.h"
#include "Gun.h"
#include "Shield.h"
#include "Boss.h"

InGameState::InGameState(shared_ptr<Font> MyFont, SDL_Renderer* pRenderer) : GameState(eStateID::INGAME)
{
    m_Font = MyFont;
    m_pRenderer = pRenderer;
}

InGameState::~InGameState()
{
    FreeResources();
}

void InGameState::Update(float DeltaTime)
{
    if (SDL_IsKeyPressed(SDL_SCANCODE_ESCAPE))
    {
        Mix_HaltChannel(-1);
        FreeResources();
        m_NextStateID = eStateID::MAINMENU;
    }

    if (m_Player->GetLivesCount() <= 0)
    {
        m_DyingTimer--;
        if (m_DyingTimer <= 0)
        {
            Boss::m_BossIsDead = true;
            m_GameOver = true;
            FreeResources();
            m_NextStateID = eStateID::VICTORY;
        }
    }

    if (Boss::m_BossIsDead)
    {
        FreeResources();
        m_NextStateID = eStateID::VICTORY;
    }

    for (int i = 0; i < m_AllGameObjects.size();)
    {
        m_AllGameObjects[i]->Update(DeltaTime);
    
        if (m_AllGameObjects[i]->GetStatus() == false)
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

    switch (m_Player->GetLivesCount())
    {
    case 3:
        dstrect = { 600, 40, 115, 30 };
        srcrect = { 0, 0, 100, 30 };
        break;
    case 2:
        dstrect = { 600, 40, 75, 30 };
        srcrect = { 0, 0, 68, 30 };
        break;
    case 1:
        dstrect = { 600, 40, 35, 30 };
        srcrect = { 0, 0, 32, 30 };
        break;
    case 0:
        dstrect = { 0, 0, 0, 0 };
        break;
    }

    DisplayTexture("Life_Banner.png", srcrect, dstrect);

    m_Font->DrawText(m_pRenderer, 3, 30, 10, "SCORE:");
    m_Font->DrawText(m_pRenderer, 3, 30, 40, ToString(SpaceInvader::m_NumOfPoints).c_str());
    m_Font->DrawText(m_pRenderer, 3, 600, 10, "LIVES:");

    SDL_RenderPresent(m_pRenderer);
}

void InGameState::CreateObject()
{
    SpaceInvader::m_NumOfPoints = 0;
    SpaceInvader::m_NumOfInvaders = 0;
    SpaceInvader::m_Speed = INVADER_SPEED;
    Boss::m_LifeStatus = 30;
    Boss::m_BossIsDead = false;

    // inicjalizacja broni
    shared_ptr<Gun> MyGun = make_shared<Gun>();

    // inicjalizacja gracza
    m_Player = make_shared<Player>(MyGun, vec2(SCREEN_WIDTH / 2, SCREEN_HEIGHT - OBJECT_HEIGHT));

    // inicjalizacja bossa
    shared_ptr<Boss> MyBoss = make_shared<Boss>(m_pRenderer, MyGun, *this);

    float PosX = 0.0f, PosY = 0.0f;

    // inicjalizacja tarcz
    for (int ROW = 0; ROW < 4; ++ROW)
    {
        PosX = ROW * 4.2f * OBJECT_WIDTH + OBJECT_WIDTH;
        PosY = SCREEN_HEIGHT - 3 * OBJECT_HEIGHT;
        m_AllGameObjects.push_back(make_shared<Shield>(PosX, PosY, MyGun));
    }

    //inicjalizacja invaderow
    for (int COLUMN = 0; COLUMN < 3; ++COLUMN)
    {
        for (int ROW = 0; ROW < SCREEN_WIDTH / OBJECT_WIDTH - 3; ++ROW)
        {
            PosX = float(ROW * OBJECT_WIDTH + OBJECT_WIDTH / 2 + ROW * (SCREEN_WIDTH / 100));
            PosY = float(SCREEN_HEIGHT / 6 + COLUMN * OBJECT_HEIGHT);
            m_AllGameObjects.push_back(make_shared<SpaceInvader>(vec2(PosX, PosY), MyGun, *this));
        }
    }

    m_AllGameObjects.push_back(move(MyGun));
    m_AllGameObjects.push_back(move(MyBoss));
    m_AllGameObjects.push_back(m_Player);
}

shared_ptr<Player> InGameState::GetPlayer()const
{
    return m_Player;
}

// SCREEN_WIDTH / INVADER_WIDTH - 3: 12 invaderow po 50 pikseli (lacznie zajmuja 600 pikseli)
// ROW * (SCREEN_WIDTH / 100): z odstepami po 8 pikseli miedzy kazdym (lacznie 100 pikseli)
// z 50 pikselowymi przerwami na poczatku i koncu ekranu (100 pikseli)
// 800 pikseli szerokosci ekranu

void InGameState::OnEnter()
{
    m_GameOver = false;
    GameState::OnEnter();
    // inicjalizacja zasobow
    CreateObject();
}

void InGameState::DisplayTexture(const string& FileName, vec2i Position, optional<vec2i> Size)
{
    Engine::GetSingleton()->DisplayTexture(("../Data/" + FileName).c_str(), Position, Size);
}

void InGameState::DisplayTexture(const string& FileName, SDL_Rect srcrect, SDL_Rect dstrect)
{
    Engine::GetSingleton()->DisplayTexture(("../Data/" + FileName).c_str(), srcrect, dstrect);
}

void InGameState::FreeResources()
{
    Engine::GetSingleton()->DestroyTextures();
    Engine::GetSingleton()->FreeSounds();
    m_AllGameObjects.clear();
}