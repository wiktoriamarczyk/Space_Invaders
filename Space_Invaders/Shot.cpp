#include "Shot.h"

Shot::Shot(vec2 Position, vec2i Size, int Speed, eTeamID Team)
{
    m_Position = Position;
    m_Size = Size;
    m_Speed = Speed;
    m_TeamID = Team;
}

void Shot::Update(float DeltaTime)
{
    float FrameDistance = m_Speed * DeltaTime;

    if (m_TeamID == eTeamID::PLAYER)
    {
        m_Position.y -= FrameDistance;
    }
    else if (m_TeamID == eTeamID::INVADER)
    {
        m_Position.y += FrameDistance;
    }

    m_LivingTimer -= DeltaTime;

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

eTeamID Shot::GetTeamID()const
{
    return m_TeamID;
}