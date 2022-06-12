#include "PowerUp.h"
#include "InGameState.h"
#include "Player.h"

PowerUp::PowerUp(string Name, InGameState& Game) : m_Game(Game)
{
    m_Name = Name;
    m_Speed = 100;
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

    // jesli nastapi kolizja z graczem, uaktywnij konkretnego PowerUpa
    vector<shared_ptr<Player>> MyPlayer = m_Game.GetObjects<Player>();
    if (!MyPlayer.empty())
    {
        vec2 ObjectTopLeftCornerPlayer = MyPlayer[0]->GetPosition() - MyPlayer[0]->GetSize() / 2;
        vec2 ObjectBottomRightCornerPlayer = MyPlayer[0]->GetPosition() + MyPlayer[0]->GetSize() / 2;

        if (ObjectBottomRightCorner.x >= ObjectTopLeftCornerPlayer.x && ObjectTopLeftCorner.x <= ObjectBottomRightCornerPlayer.x)
        {
            if (ObjectTopLeftCorner.y <= ObjectBottomRightCornerPlayer.y && ObjectBottomRightCorner.y >= ObjectTopLeftCornerPlayer.y)
            {
                Activate(MyPlayer[0]);
            }
        }
    }
}

void PowerUp::Render(SDL_Renderer* pRenderer)
{
    if (m_DisplayTexture)
    {
        DisplayTexture(m_Name + ".png", m_Position, { .DrawMode = eDrawMode::NORMAL , .DrawScale = m_Scale , .SrcTopLeft = vec2(0.0f,0.0f) , .DrawColor = m_Color });
    }

}

void PowerUp::SetScale(vec2 Scale)
{
    m_Scale = Scale;
}
