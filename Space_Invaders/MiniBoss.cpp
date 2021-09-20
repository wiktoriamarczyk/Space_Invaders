#include "MiniBoss.h"

MiniBoss::MiniBoss(SDL_Renderer* pRenderer)
{
    m_pRenderer = pRenderer;

    m_StartingPointPosition.x = -100;
    m_StartingPointPosition.y = 30;

    m_ObjectSize.x = 0.5f*BOSS_WIDTH;
    m_ObjectSize.y = 0.5f*BOSS_HEIGHT;

    InitializeMiniBossTexture();
}

MiniBoss::~MiniBoss()
{
    DestroyMiniBossTextures();
}

void MiniBoss::InitializeMiniBossTexture()
{
    SDL_Surface* m_pImage = IMG_Load("../Data/Boss.png");
    m_pTexture = SDL_CreateTextureFromSurface(m_pRenderer, m_pImage);
    SDL_FreeSurface(m_pImage);
}

void MiniBoss::DestroyMiniBossTextures()
{
    SDL_DestroyTexture(m_pTexture);
    m_pTexture = nullptr;
}

void MiniBoss::Update(float DeltaTime)
{
    float FrameDistance = BOSS_SPEED * DeltaTime;
    vec2 ObjectTopLeftCorner = m_StartingPointPosition;
    vec2 ObjectBottomRightCorner = m_StartingPointPosition + m_ObjectSize;
    vec2 tempPos = m_StartingPointPosition;

    if (!m_ChangeDirectionX)
    {
        m_StartingPointPosition.x += FrameDistance;
        if (ObjectBottomRightCorner.x >= SCREEN_WIDTH + 100)
        {
            m_ChangeDirectionX = true;
        }
    }
    if (m_ChangeDirectionX)
    {
        m_StartingPointPosition.x -= FrameDistance;
        if (ObjectTopLeftCorner.x <= -100)
        {
            m_ChangeDirectionX = false;
        }
    }
}

void MiniBoss::Render(SDL_Renderer* pRenderer)
{
    SDL_Rect dstrect = { int(m_StartingPointPosition.x), int(m_StartingPointPosition.y), m_ObjectSize.x, m_ObjectSize.y };
    //SDL_SetRenderDrawColor(pRenderer, 255, 255, 255, 255);
    //SDL_RenderFillRect(pRenderer, &dstrect);
    SDL_RenderCopy(m_pRenderer, m_pTexture, NULL, &dstrect);
}


