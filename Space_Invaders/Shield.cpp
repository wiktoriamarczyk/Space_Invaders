#include "Shield.h"
#include "Engine.h"


Shield::Shield(float PosX, float PosY, shared_ptr<Gun> MyGun)
{
    m_Gun = MyGun;
    m_Position.x = PosX;
    m_Position.y = PosY;
    m_Size.x = int(1.2f * float(OBJECT_WIDTH));
    m_Size.y = OBJECT_HEIGHT;

    m_TextureDestructionLevel.Size = vec2(0.5f, 0.5f);
}

void Shield::Update(float DeltaTime)
{
    switch (m_DestructionLevel)
    {
    case 0:
        m_TextureDestructionLevel.TopLeft = vec2(0,0);
        break;
    case 1:
        m_TextureDestructionLevel.TopLeft = vec2(0.5f, 0);
        break;
    case 2:
        m_TextureDestructionLevel.TopLeft = vec2(0, 0.5f);
        break;
    case 3:
        m_TextureDestructionLevel.TopLeft = vec2(0.5f, 0.5f);
        break;
    }

    vec2 ObjectTopLeftCorner = m_Position;
    vec2 ObjectBottomRightCorner = m_Position + m_Size;

    for (size_t i = 0; i < m_Gun->GetShots().size(); ++i)
    {
        if (m_Gun->GetShots()[i]->GetPosition().x >= ObjectTopLeftCorner.x && m_Gun->GetShots()[i]->GetPosition().x <= ObjectBottomRightCorner.x)
        {
            if (m_Gun->GetShots()[i]->GetPosition().y <= ObjectBottomRightCorner.y && m_Gun->GetShots()[i]->GetPosition().y >= ObjectTopLeftCorner.y)
            {
                m_DestructionLevel++;
                m_Gun->GetShots()[i]->SetStatus(false);
            }
        }
    }

    if (m_DestructionLevel >= 4)
    {
        m_IsAlive = false;
    }
}

void Shield::Render(SDL_Renderer* pRenderer)
{
    DisplayTexture("Shields.png", m_Position, DisplayParameters{ .DisplaySize = m_Size, .SrcTopLeft = m_TextureDestructionLevel.TopLeft, .SrcSize = m_TextureDestructionLevel.Size });
}

void Shield::SetShotStatus(vec2 &BulletPosition)
{
    vec2 ObjectTopLeftCorner = m_Position;
    vec2 ObjectBottomRightCorner = m_Position + m_Size;
}