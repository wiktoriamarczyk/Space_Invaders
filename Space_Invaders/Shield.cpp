#include "Shield.h"
#include "Engine.h"

SDL_Texture* Shield::m_pTexture = nullptr;

Shield::Shield(float PosX, float PosY, shared_ptr<Gun> MyGun)
{
    m_Gun = MyGun;
    m_StartingPointPosition.x = PosX;
    m_StartingPointPosition.y = PosY;
    m_ObjectSize.x = 1.2 * OBJECT_WIDTH;
    m_ObjectSize.y = OBJECT_HEIGHT;
}

void Shield::DestroyTexture()
{
    SDL_DestroyTexture(m_pTexture);
    m_pTexture = nullptr;
}

void Shield::InitializeShieldTexture(SDL_Renderer* pRenderer)
{
    SDL_Surface* m_pImage = IMG_Load("../Data/Shields.png");
    m_pTexture = SDL_CreateTextureFromSurface(pRenderer, m_pImage);
    SDL_FreeSurface(m_pImage);
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

    vec2 ObjectTopLeftCorner = m_StartingPointPosition;
    vec2 ObjectBottomRightCorner = m_StartingPointPosition + m_ObjectSize;

    for (int i = 0; i < m_Gun->GetShots().size(); ++i)
    {
        if (m_Gun->GetShots()[i]->GetObjectPosition().x >= ObjectTopLeftCorner.x && m_Gun->GetShots()[i]->GetObjectPosition().x <= ObjectBottomRightCorner.x)
        {
            if (m_Gun->GetShots()[i]->GetObjectPosition().y <= ObjectBottomRightCorner.y && m_Gun->GetShots()[i]->GetObjectPosition().y >= ObjectTopLeftCorner.y)
            {
                m_DestructionLevel++;
                m_Gun->GetShots()[i]->SetObjectStatus(false);
            }
        }
    }

    if (m_DestructionLevel >= 4)
    {
        m_ObjectIsAlive = false;
    }
}

void Shield::Render(SDL_Renderer* pRenderer)
{
    SDL_Rect dstrect = { m_StartingPointPosition.x, m_StartingPointPosition.y, m_ObjectSize.x, m_ObjectSize.y };
    // SDL_SetRenderDrawColor(pRenderer, 255, 255, 255, 255);
    // SDL_RenderFillRect(pRenderer, &dstrect);
    SDL_RenderCopy(pRenderer, m_pTexture, &m_TextureDestructionLevel, &dstrect);
}

void Shield::SetShotStatus(vec2 &BulletPosition)
{
    vec2 ObjectTopLeftCorner = m_StartingPointPosition;
    vec2 ObjectBottomRightCorner = m_StartingPointPosition + m_ObjectSize;
}