#include "Boss.h"
#include "SpaceInvader.h"
#include "Engine.h"

bool Boss::m_BossIsDead = false;
int Boss::m_LifeStatus = 30;

Boss::Boss(SDL_Renderer* pRenderer, shared_ptr<Gun> MyGun, InGameState& Game) : m_Game(Game)
{
    m_pRenderer = pRenderer;
    m_Gun = MyGun;

    m_Position.x = -200;
    m_Position.y = 100;

    m_Size.x = BOSS_WIDTH;
    m_Size.y = BOSS_HEIGHT;

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

        m_DyingTimer--;

        if (m_DyingTimer <= 0)
        {
            m_BossIsDead = true;
        }
    }

    if (m_BossIsDead)
    {
        m_IsAlive = false;
    }

    if (SpaceInvader::m_NumOfInvaders <= 0)
    {
        if (m_PlayMusic)
        {
            Engine::GetSingleton()->PlaySound("Boss_fight.wav");
            m_PlayMusic = false;
        }

        float FrameDistance = BOSS_SPEED * DeltaTime;
        vec2 ObjectTopLeftCorner = m_Position;
        vec2 ObjectBottomRightCorner = m_Position + m_Size;
        vec2 tempPos = m_Position;

        if (ObjectTopLeftCorner.x <= SCREEN_WIDTH / 2 - 100)
        {
            m_Position.x += FrameDistance;
        }

        // strzelanie do bossa
        for (int i = 0; i < m_Gun->GetShots().size(); ++i)
        {
            if (m_Gun->GetShots()[i]->GetTeamID() == eTeamID::PLAYER)
            {
                if (m_Gun->GetShots()[i]->GetPosition().x >= ObjectTopLeftCorner.x && m_Gun->GetShots()[i]->GetPosition().x <= ObjectBottomRightCorner.x)
                {
                    if (m_Gun->GetShots()[i]->GetPosition().y <= ObjectBottomRightCorner.y && m_Gun->GetShots()[i]->GetPosition().y >= ObjectTopLeftCorner.y)
                    {
                        Engine::GetSingleton()->PlaySound("ShootingSpaceInvaderSound.wav");
                        m_Gun->GetShots()[i]->SetStatus(false);
                        m_LifeStatus--;
                        SpaceInvader::m_NumOfPoints = SpaceInvader::m_NumOfPoints + 100;
                    }
                }
            }
        }

        // strzelanie przez bossa
        m_ShootingTimer--;

        vec2i BossShots = { 2 * SHOT_WIDTH, 2 * SHOT_HEIGHT };

        if (!m_BossIsDead)
        {
            if (m_ShootingTimer <= 0)
            {
                m_ShootingTimer = 40.0f;

                if (GetRandNumber() == 0)
                {
                    m_Gun->Shoot(vec2(ObjectTopLeftCorner.x - 2, ObjectBottomRightCorner.y), BossShots, SHOT_SPEED, eTeamID::INVADER);
                }
                else if (GetRandNumber() == 1)
                {
                    m_Gun->Shoot(vec2(m_Position.x + 50, ObjectBottomRightCorner.y - 30), BossShots, SHOT_SPEED, eTeamID::INVADER);
                }
                else if (GetRandNumber() == 2)
                {
                    m_Gun->Shoot(vec2(ObjectBottomRightCorner.x - 90, ObjectBottomRightCorner.y), BossShots, SHOT_SPEED, eTeamID::INVADER);
                }
            }
        }
    }
}
  
void Boss::Render(SDL_Renderer* pRenderer)
{
    if (SpaceInvader::m_NumOfInvaders <= 0)
    {
        //SDL_Rect dstrect = { int(m_Position.x), int(m_Position.y), m_Size.x, m_Size.y };
        //SDL_SetRenderDrawColor(pRenderer, 255, 255, 255, 255);
        //SDL_RenderFillRect(pRenderer, &dstrect);
        //SDL_RenderCopy(m_pRenderer, m_pTexture, NULL, &dstrect);
        if (m_BossIsDead)
        {
            DisplayTexture("puf.png", (vec2i)m_Position, m_Size);
        }
        else DisplayTexture("Boss.png", (vec2i)m_Position, m_Size);

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
