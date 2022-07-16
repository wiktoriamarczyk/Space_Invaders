#include "SpaceInvader.h"

bool SpaceInvader::m_ChangeDirection = false;
int SpaceInvader::m_NumOfInvaders = 0;

SDL_Surface* SpaceInvader::m_pImage1 = nullptr;
SDL_Surface* SpaceInvader::m_pImage2 = nullptr;
SDL_Surface* SpaceInvader::m_pImage3 = nullptr;

SpaceInvader::SpaceInvader(SDL_Renderer* pRenderer, float PosX, float PosY)
{
    m_InvaderID = m_NumOfInvaders;
    m_NumOfInvaders++;

    m_pTexture = GetTexture(pRenderer);

    m_StartingPointPosition.x = PosX;
    m_StartingPointPosition.y = PosY;

    m_ObjectSize.x = INVADER_WIDTH;
    m_ObjectSize.y = INVADER_HEIGHT;
}

SpaceInvader::~SpaceInvader()
{
    SDL_DestroyTexture(m_pTexture);
    SDL_FreeSurface(m_pImage1);
    SDL_FreeSurface(m_pImage2);
    SDL_FreeSurface(m_pImage3);
}

void SpaceInvader::Update(float DeltaTime)
{
    float FrameDistance = INVADER_SPEED * DeltaTime;
    vec2 ObjectTopLeftCorner = m_StartingPointPosition;
    vec2 ObjectBottomRightCorner = m_StartingPointPosition + m_ObjectSize;

    if (!m_ChangeDirection)
    {
        m_StartingPointPosition.x += FrameDistance;
        if (ObjectBottomRightCorner.x >= SCREEN_WIDTH)
        {
            m_ChangeDirection = true;
        }
    }
    if (m_ChangeDirection)
    {
        m_StartingPointPosition.x -= FrameDistance;
        if (ObjectTopLeftCorner.x <= 0)
        {
            m_ChangeDirection = false;
        }
    }

    SDL_Rect srcrect1 = { 0, 0, 820, 820 };
    SDL_Rect srcrect2 = { 820, 0, 820, 820 };

    m_Timer--;

    if (m_Timer == 50.0f)
    {
        m_MovementRect = srcrect1;
    }
    if (m_Timer <= 0)
    {
        m_MovementRect = srcrect2;
        m_Timer = 100.0f;
    }
}

void SpaceInvader::Render(SDL_Renderer* pRenderer)
{
    SDL_Rect dstrect = { m_StartingPointPosition.x, m_StartingPointPosition.y, m_ObjectSize.x, m_ObjectSize.y };
    //SDL_SetRenderDrawColor(pRenderer, 255, 255, 255, 255);
    // SDL_RenderFillRect(pRenderer, &dstrect);
    SDL_RenderCopy(pRenderer, m_pTexture, &m_MovementRect , &dstrect);
}

void SpaceInvader::LoadTexture()
{
    if (!m_pImage1)
    {
        m_pImage1 = IMG_Load("../Data/SpaceInvaders1.png");
    }
    if (!m_pImage2)
    {
        m_pImage2 = IMG_Load("../Data/SpaceInvaders2.png");
    }
    if (!m_pImage3)
    {
        m_pImage3 = IMG_Load("../Data/SpaceInvaders3.png");
    }
}

SDL_Texture* SpaceInvader::GetTexture(SDL_Renderer* pRenderer)
{
    if (m_InvaderID <= 12)
    {
        m_pTexture = SDL_CreateTextureFromSurface(pRenderer, m_pImage1);
    }
    if (m_InvaderID >= 13 && m_InvaderID <= 38)
    {
        m_pTexture = SDL_CreateTextureFromSurface(pRenderer, m_pImage2);
    }
    if (m_InvaderID >= 39 && m_InvaderID <= 64)
    {
        m_pTexture = SDL_CreateTextureFromSurface(pRenderer, m_pImage3);
    }
    return m_pTexture;
}
