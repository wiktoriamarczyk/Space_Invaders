#include "Shot.h"

Shot::Shot(vec2 Position, eTeamID Team)
{
    m_Position = Position;
    m_TeamID = Team;
    m_Speed = SHOT_SPEED;
}

void Shot::Update(float DeltaTime)
{
    float FrameDistance = m_Speed * DeltaTime;

    if (m_TeamID == eTeamID::PLAYER || m_TeamID == eTeamID::SUICIDE)
    {
        m_Position.y -= FrameDistance;
    }
    else if (m_TeamID == eTeamID::INVADER)
    {
        m_Position.y += FrameDistance;
    }

    if (GetPosition().y <= 0)
    {
        m_IsAlive = false;
    }
}

void Shot::Render(SDL_Renderer* pRenderer)
{
    SDL_Rect ShotRect = {m_Position.x, m_Position.y, m_Size.x, m_Size.y };
    SDL_SetRenderDrawColor(pRenderer, m_Color.R, m_Color.G, m_Color.B, 255);
    SDL_RenderFillRect(pRenderer, &ShotRect);
}

eTeamID Shot::GetTeamID()const
{
    return m_TeamID;
}

void Shot::SetTeamID(eTeamID TeamID)
{
    m_TeamID = TeamID;
}

void Shot::InitializeParams(vec2i Size, Color MyColor, int Speed)
{
    m_Size = Size;
    m_Color = MyColor;
    m_Speed = Speed;
}
