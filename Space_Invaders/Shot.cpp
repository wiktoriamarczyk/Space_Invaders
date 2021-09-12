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
    m_StartingPointPosition.y -= FrameDistance;

    m_LivingTimer--;
    if (m_LivingTimer <= 0)
    {
        m_ObjectIsAlive = false;
    }
}

void Shot::Render(SDL_Renderer* pRenderer)
{
    SDL_Rect ShotRect = {m_StartingPointPosition.x, m_StartingPointPosition.y, m_ObjectSize.x, m_ObjectSize.y };
    SDL_SetRenderDrawColor(pRenderer, 255, 255, 255, 255);
    SDL_RenderFillRect(pRenderer, &ShotRect);
}