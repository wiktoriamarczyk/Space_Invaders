#include "Shot.h"

Shot::Shot(vec2 Position, vec2i Size, int Speed)
{
    m_GunPosition = Position;

    m_Size.x = Size.x;
    m_Size.y = Size.y;

    m_Position.x = m_GunPosition.x + 7.5 * m_Size.x;
    m_Position.y = m_GunPosition.y - m_Size.y;

    m_Speed = Speed;
}

void Shot::Update(float DeltaTime)
{
    float FrameDistance = m_Speed * DeltaTime;

    if (m_DealingDamage)
    {
        m_Position.y -= FrameDistance;
    }
    else
    {
        m_Position.y += FrameDistance;
    }

    m_LivingTimer--;

    if (m_LivingTimer <= 0)
    {
        m_IsAlive = false;
    }
}

void Shot::Render(SDL_Renderer* pRenderer)
{
    SDL_Rect ShotRect = {m_Position.x, m_Position.y, m_Size.x, m_Size.y };
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
