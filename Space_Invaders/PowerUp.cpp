#include "PowerUp.h"

PowerUp::PowerUp(string Name)
{
    m_Name = Name;
}

void PowerUp::Update(float DeltaTime)
{
    float FrameDistance = m_Speed * DeltaTime;
    vec2 ObjectTopLeftCorner = m_Position - m_Size / 2;
    vec2 ObjectBottomRightCorner = m_Position + m_Size / 2;

    SetPosition({ m_Position.x , m_Position.y + FrameDistance });

    if (ObjectTopLeftCorner.y >= SCREEN_HEIGHT)
    {
        m_IsAlive = false;
    }
}

void PowerUp::Render(SDL_Renderer* pRenderer)
{
    DisplayTexture(m_Name + ".png", m_Position, {.DrawMode = eDrawMode::ADDITIVE , .DrawScale = m_Scale , .SrcTopLeft = vec2(0.0f,0.0f) , .SrcSize = vec2(1.0f,1.0f), .DrawColor = m_Color});
}

void PowerUp::SetScale(vec2 Scale)
{
    m_Scale = Scale;
}
