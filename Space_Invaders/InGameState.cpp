#include "InGameState.h"
#include "Engine.h"
#include "SpaceInvader.h"
#include "Gun.h"
#include "Shield.h"
#include "Boss.h"

InGameState::InGameState(shared_ptr<Font> MyFont) : GameState(eStateID::INGAME)
{
    m_Font = MyFont;
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
            m_GameOver = true;
            FreeResources();
            m_NextStateID = eStateID::VICTORY;
        }
    }

    if (GetBossStatus())
    {
        m_GameOver = false;
        FreeResources();
        SetBossStatus(false);
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

void InGameState::Render(SDL_Renderer* pRenderer)
{
    SDL_SetRenderDrawColor(pRenderer, 0, 0, 0, 255);
    SDL_RenderClear(pRenderer);

    // render wszystkich obiektow
     for (int i = 0; i < m_AllGameObjects.size(); ++i)
     {
         m_AllGameObjects[i]->Render(pRenderer);
     }

    vec2 Size{};

    switch (m_Player->GetLivesCount())
    {
    case 3:
        Size = vec2(1, 1);
        break;
    case 2:
        Size = vec2(2.f/3.f, 1);
        break;
    case 1:
        Size = vec2(1.0f/3.0f, 1);
        break;
    case 0:
        Size = vec2(0, 0);
        break;
    }

    DisplayTexture("Life_Banner.png", vec2(600, 40), DisplayParameters{.DrawScale = Size, .SrcSize = Size});

    m_Font->DrawText(pRenderer, 3, 30, 10, "SCORE:");
    m_Font->DrawText(pRenderer, 3, 30, 40, ToString(GetNumOfPoints()).c_str());
    m_Font->DrawText(pRenderer, 3, 600, 10, "LIVES:");

    SDL_RenderPresent(pRenderer);
}

void InGameState::CreateObject()
{
    SetNumOfPoints(0);
    SetSpaceInvadersNum(0);

    // inicjalizacja broni
    shared_ptr<Gun> MyGun = make_shared<Gun>();

    // inicjalizacja gracza
    m_Player = make_shared<Player>(MyGun, vec2(SCREEN_WIDTH / 2, SCREEN_HEIGHT - OBJECT_HEIGHT));

    // inicjalizacja bossa
    shared_ptr<Boss> MyBoss = make_shared<Boss>(MyGun, *this);

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
        for (int ROW = 0; ROW < 13; ++ROW)
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

void InGameState::SetSpaceInvadersNum(int Value)
{
    m_NumOfSpaceInvaders = Value;
}

int InGameState::GetSpaceInvadersNum()const
{
    return m_NumOfSpaceInvaders;
}

void InGameState::SetBossStatus(bool BossStatus)
{
    m_BossIsDead = BossStatus;
}

int InGameState::GetBossStatus() const
{
    return m_BossIsDead;
}

void InGameState::SetNumOfPoints(int Value)
{
    m_NumOfPoints = Value;
}

int InGameState::GetNumOfPoints() const
{
    return m_NumOfPoints;
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

void InGameState::FreeResources()
{
    Engine::GetSingleton()->DestroyTextures();
    Engine::GetSingleton()->FreeSounds();
    m_AllGameObjects.clear();
}

shared_ptr<ParticleEmiter> InGameState::CreateParticle(vec2 Position)
{
    shared_ptr<ParticleEmiter> pEmiter = make_shared<ParticleEmiter>();
    pEmiter->SetPosition(Position);
    m_AllGameObjects.push_back(pEmiter);

    return pEmiter;
}
