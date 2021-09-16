#include "Shot.h"

Shot::Shot(vec2 Position)
{
    m_GunPosition = Position;

    m_ObjectSize.x = SHOT_WIDTH;
    m_ObjectSize.y = SHOT_HEIGHT;

    m_StartingPointPosition.x = m_GunPosition.x + 7.5 * m_ObjectSize.x;
    m_StartingPointPosition.y = m_GunPosition.y - m_ObjectSize.y;
}

void Shot::Update(float DeltaTime)
{
    float FrameDistance = SHOT_SPEED * DeltaTime;

    if (m_DealingDamage)
    {
        m_StartingPointPosition.y -= FrameDistance;
    }
    else
    {
        m_StartingPointPosition.y += FrameDistance;
    }

    m_LivingTimer--;

    if (m_LivingTimer <= 0)
    {
        m_ObjectIsAlive = false;
        m_LivingTimer = 60.0f;
    }
}

void Shot::Render(SDL_Renderer* pRenderer)
{
    SDL_Rect ShotRect = {m_StartingPointPosition.x, m_StartingPointPosition.y, m_ObjectSize.x, m_ObjectSize.y };
    SDL_SetRenderDrawColor(pRenderer, 255, 255, 255, 255);
    SDL_RenderFillRect(pRenderer, &ShotRect);
}

bool Shot::GetDealingDamageStatus()
{
    return m_DealingDamage;
}

void Shot::SetDealingDamage(bool DealingDamage)
{
    m_DealingDamage = DealingDamage;
}
