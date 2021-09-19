#include "Boss.h"
#include "SpaceInvader.h"
#include "Engine.h"

bool Boss::m_BossIsDead = false;
int Boss::m_LifeStatus = 30;

Boss::Boss(SDL_Renderer* pRenderer, shared_ptr<Gun> MyGun)
{
    m_pRenderer = pRenderer;
    m_Gun = MyGun;

    m_StartingPointPosition.x = -200;
    m_StartingPointPosition.y = 100;

    m_ObjectSize.x = BOSS_WIDTH;
    m_ObjectSize.y = BOSS_HEIGHT;

    InitializeBossTexture();
}

void Boss::InitializeBossTexture()
{
    SDL_Surface* m_pImage = IMG_Load("../Data/Boss.png");
    m_pNormalTexture = SDL_CreateTextureFromSurface(m_pRenderer, m_pImage);
    SDL_FreeSurface(m_pImage);

    m_pImage = IMG_Load("../Data/puf.png");
    m_pDyingTexture = SDL_CreateTextureFromSurface(m_pRenderer, m_pImage);
    SDL_FreeSurface(m_pImage);
    m_pImage = nullptr;

    m_pTexture = m_pNormalTexture;
}

Boss::~Boss()
{
    SDL_DestroyTexture(m_pTexture);
    m_pTexture = nullptr;
    SDL_DestroyTexture(m_pNormalTexture);
    m_pNormalTexture = nullptr;
    SDL_DestroyTexture(m_pDyingTexture);
    m_pDyingTexture = nullptr;
}

void Boss::Update(float DeltaTime)
{
    if (m_LifeStatus <= 0)
    {
        if (m_PlayDeathSound)
        {
            Engine::GetSingleton()->PlaySound("Boss_death.wav");
            m_PlayDeathSound = false;
        }

        m_ObjectSize.x = BOSS_WIDTH;
        m_ObjectSize.y = BOSS_WIDTH;
        m_pTexture = m_pDyingTexture;

        m_DyingTimer--;

        if (m_DyingTimer <= 0)
        {
            m_BossIsDead = true;
        }
    }

    if (m_BossIsDead)
    {
        m_ObjectIsAlive = false;
    }

    if (SpaceInvader::m_NumOfInvaders <= 0)
    {
        if (m_PlayMusic)
        {
            Engine::GetSingleton()->PlaySound("Boss_fight.wav");
            m_PlayMusic = false;
        }

        float FrameDistance = BOSS_SPEED * DeltaTime;
        vec2 ObjectTopLeftCorner = m_StartingPointPosition;
        vec2 ObjectBottomRightCorner = m_StartingPointPosition + m_ObjectSize;
        vec2 tempPos = m_StartingPointPosition;

        if (ObjectTopLeftCorner.x <= SCREEN_WIDTH / 2 - 100)
        {
            m_StartingPointPosition.x += FrameDistance;
        }

        // strzelanie do bossa
        for (int i = 0; i < m_Gun->GetShots().size(); ++i)
        {
            if (m_Gun->GetShots()[i]->GetDealingDamageStatus() == true)
            {
                if (m_Gun->GetShots()[i]->GetObjectPosition().x >= ObjectTopLeftCorner.x && m_Gun->GetShots()[i]->GetObjectPosition().x <= ObjectBottomRightCorner.x)
                {
                    if (m_Gun->GetShots()[i]->GetObjectPosition().y <= ObjectBottomRightCorner.y && m_Gun->GetShots()[i]->GetObjectPosition().y >= ObjectTopLeftCorner.y)
                    {
                        Engine::GetSingleton()->PlaySound("ShootingSpaceInvaderSound.wav");
                        m_Gun->GetShots()[i]->SetObjectStatus(false);
                        m_LifeStatus--;
                        SpaceInvader::m_NumOfPoints = SpaceInvader::m_NumOfPoints + 100;
                    }
                }
            }
        }

        // strzelanie przez bossa
        m_ShootingTimer--;

        vec2 BossShots = { 2 * SHOT_WIDTH, 2 * SHOT_HEIGHT };

        if (!m_BossIsDead)
        {
            if (m_ShootingTimer <= 0)
            {
                m_ShootingTimer = 40.0f;

                if (GetRandNumber() == 0)
                {
                    m_Gun->Shoot(ObjectTopLeftCorner.x - 2, ObjectBottomRightCorner.y, BossShots);
                }
                else if (GetRandNumber() == 1)
                {
                    m_Gun->Shoot(m_StartingPointPosition.x + 50, ObjectBottomRightCorner.y - 30, BossShots);
                }
                else if (GetRandNumber() == 2)
                {
                    m_Gun->Shoot(ObjectBottomRightCorner.x - 90, ObjectBottomRightCorner.y, BossShots);
                }
            }
        }
    }
}

void Boss::Render(SDL_Renderer* pRenderer)
{
    if (SpaceInvader::m_NumOfInvaders <= 0)
    {
        SDL_Rect dstrect = { int(m_StartingPointPosition.x), int(m_StartingPointPosition.y), m_ObjectSize.x, m_ObjectSize.y };
        //SDL_SetRenderDrawColor(pRenderer, 255, 255, 255, 255);
        //SDL_RenderFillRect(pRenderer, &dstrect);
        SDL_RenderCopy(m_pRenderer, m_pTexture, NULL, &dstrect);

        SDL_SetRenderDrawColor(m_pRenderer, 255, 255, 255, 255);

        SDL_Rect LifeRect = { 200, 10, 340, 50 };
        SDL_RenderDrawRect(m_pRenderer, &LifeRect);

        SDL_SetRenderDrawColor(m_pRenderer, 255, 0, 0, 255);

        int Rect_width = 5;
        int Rect_height = 45;

        for (int i = 0; i < m_LifeStatus; ++i)
        {
            SDL_Rect BlocksOfLife = { 202 + i * Rect_width + i * 1.25f * Rect_width, 12, 2 * Rect_width, Rect_height };
            SDL_RenderFillRect(m_pRenderer, &BlocksOfLife);
        }
    }
}

int Boss::GetRandNumber()
{
    return rand() % 3;
}
