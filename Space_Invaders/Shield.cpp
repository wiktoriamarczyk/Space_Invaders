#include "Shield.h"
#include "Engine.h"


Shield::Shield(float PosX, float PosY, shared_ptr<Gun> MyGun)
{
    m_Gun = MyGun;
    m_Position.x = PosX;
    m_Position.y = PosY;
    m_Size.x = 1.2 * OBJECT_WIDTH;
    m_Size.y = OBJECT_HEIGHT;
}

void Shield::Update(float DeltaTime)
{
    switch (m_DestructionLevel)
    {
    case 0:
        m_TextureDestructionLevel = { 90, 43, 230, 190 };
        break;
    case 1:
        m_TextureDestructionLevel = { 440, 43, 230, 180 };
        break;
    case 2:
        m_TextureDestructionLevel = { 90, 329, 230, 180 };
        break;
    case 3:
        m_TextureDestructionLevel = { 435, 329, 230, 170 };
        break;
    }

    vec2 ObjectTopLeftCorner = m_Position;
    vec2 ObjectBottomRightCorner = m_Position + m_Size;

    for (int i = 0; i < m_Gun->GetShots().size(); ++i)
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
    SDL_Rect dstrect = { m_Position.x, m_Position.y, m_Size.x, m_Size.y };
    DisplayTexture("Shields.png", m_TextureDestructionLevel, dstrect);
}

void Shield::SetShotStatus(vec2 &BulletPosition)
{
    vec2 ObjectTopLeftCorner = m_Position;
    vec2 ObjectBottomRightCorner = m_Position + m_Size;
}