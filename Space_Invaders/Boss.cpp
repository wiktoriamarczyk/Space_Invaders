#include "Boss.h"
#include "SpaceInvader.h"
#include "Engine.h"


Boss::Boss(shared_ptr<Gun> MyGun, InGameState& Game) : m_Game(Game)
{
    m_Gun = MyGun;
    m_Position = vec2(-200, 100);
    m_Size = vec2i(BOSS_WIDTH, BOSS_HEIGHT);
}

void Boss::Update(float DeltaTime)
{
    if (GetNumOfLives() <= 0)
    {
        if (m_PlayDeathSound)
        {
            Engine::GetSingleton()->PlaySound("Boss_death.wav");
            m_PlayDeathSound = false;
        }

        m_DyingTimer--;

        if (m_DyingTimer <= 0)
        {
            m_Game.SetBossStatus(true);
        }
    }

    if (m_Game.GetBossStatus())
    {
        m_IsAlive = false;
    }

    if (m_Game.GetSpaceInvadersNum() <= 0)
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
                        m_NumOfLives--;
                        ///SpaceInvader::m_NumOfPoints = SpaceInvader::m_NumOfPoints + 100;
                        m_Game.SetNumOfPoints(m_Game.GetNumOfPoints() + m_PointsForKill);
                    }
                }
            }
        }

        // strzelanie przez bossa
        m_ShootingTimer--;

        vec2i BossShots = { 2 * SHOT_WIDTH, 2 * SHOT_HEIGHT };

        if (GetNumOfLives() > 0)
        {
            if (m_ShootingTimer <= 0)
            {
                m_ShootingTimer = 40.0f;

                if (GetRandInt(0, 2) == 0)
                {
                    m_Gun->Shoot(vec2(ObjectTopLeftCorner.x - 2, ObjectBottomRightCorner.y), BossShots, SHOT_SPEED, eTeamID::INVADER);
                }
                else if (GetRandInt(0, 2) == 1)
                {
                    m_Gun->Shoot(vec2(m_Position.x + 50, ObjectBottomRightCorner.y - 30), BossShots, SHOT_SPEED, eTeamID::INVADER);
                }
                else if (GetRandInt(0, 2) == 2)
                {
                    m_Gun->Shoot(vec2(ObjectBottomRightCorner.x - 90, ObjectBottomRightCorner.y), BossShots, SHOT_SPEED, eTeamID::INVADER);
                }
            }
        }
    }
}
  
void Boss::Render(SDL_Renderer* pRenderer)
{
    if (m_Game.GetSpaceInvadersNum() <= 0)
    {
        if (GetNumOfLives() <= 0)
        {
            //DisplayTexture("puf.png", (vec2i)m_Position, vec2i(BOSS_WIDTH, BOSS_WIDTH));
        }
        else DisplayTexture("Boss.png", m_Position, DisplayParameters{ .DisplaySize = m_Size});

        SDL_SetRenderDrawColor(pRenderer, 255, 255, 255, 255);
        SDL_Rect LifeRect = { 200, 10, 340, 50 };
        SDL_RenderDrawRect(pRenderer, &LifeRect);

        SDL_SetRenderDrawColor(pRenderer, 255, 0, 0, 255);

        int Rect_width = 5;
        int Rect_height = 45;

        for (int i = 0; i < GetNumOfLives(); ++i)
        {
            SDL_Rect BlocksOfLife = { 202 + i * Rect_width + i * 1.25f * Rect_width, 12, 2 * Rect_width, Rect_height };
            SDL_RenderFillRect(pRenderer, &BlocksOfLife);
        }
    }
}

void Boss::SetNumOfLives(int Value)
{
    m_NumOfLives = Value;
}

int Boss::GetNumOfLives() const
{
    return m_NumOfLives;
}
