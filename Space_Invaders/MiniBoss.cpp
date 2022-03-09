#include "MiniBoss.h"

MiniBoss::MiniBoss(SDL_Renderer* pRenderer)
{
    m_pRenderer = pRenderer;

    m_Position.x = -100;
    m_Position.y = 30;

    m_Size.x = 0.5f*BOSS_WIDTH;
    m_Size.y = 0.5f*BOSS_HEIGHT;

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
    vec2 ObjectTopLeftCorner = m_Position;
    vec2 ObjectBottomRightCorner = m_Position + m_Size;
    vec2 tempPos = m_Position;

    if (!m_ChangeDirectionX)
    {
        m_Position.x += FrameDistance;
        if (ObjectBottomRightCorner.x >= SCREEN_WIDTH + 100)
        {
            m_ChangeDirectionX = true;
        }
    }
    if (m_ChangeDirectionX)
    {
        m_Position.x -= FrameDistance;
        if (ObjectTopLeftCorner.x <= -100)
        {
            m_ChangeDirectionX = false;
        }
    }
}

void MiniBoss::Render(SDL_Renderer* pRenderer)
{
    SDL_Rect dstrect = { int(m_Position.x), int(m_Position.y), m_Size.x, m_Size.y };
    //SDL_SetRenderDrawColor(pRenderer, 255, 255, 255, 255);
    //SDL_RenderFillRect(pRenderer, &dstrect);
    SDL_RenderCopy(m_pRenderer, m_pTexture, NULL, &dstrect);
}


