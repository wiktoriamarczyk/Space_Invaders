#include "SpaceInvader.h"

bool SpaceInvader::m_ChangeDirection = false;

SpaceInvader::SpaceInvader(SDL_Renderer* pRenderer, float CenterPosX, float CenterPosY)
{
    m_pImage = IMG_Load("../Data/x.png");
    m_pTexture = SDL_CreateTextureFromSurface(pRenderer, m_pImage);

    m_ObjectCenterPosition.x = CenterPosX;
    m_ObjectCenterPosition.y = CenterPosY;

    m_ObjectSize.x = INVADER_WIDTH;
    m_ObjectSize.y = INVADER_HEIGHT;
}

SpaceInvader::~SpaceInvader()
{
    SDL_DestroyTexture(m_pTexture);
    SDL_FreeSurface(m_pImage);
}

void SpaceInvader::Update(float DeltaTime)
{
    float FrameDistance = INVADER_SPEED * DeltaTime;
    vec2 ObjectTopLeftCorner = m_ObjectCenterPosition - m_ObjectSize / 2;
    vec2 ObjectBottomRightCorner = m_ObjectCenterPosition + m_ObjectSize / 2;

    if (!m_ChangeDirection)
    {
        m_ObjectCenterPosition.x += FrameDistance;
        if (ObjectBottomRightCorner.x >= SCREEN_WIDTH)
        {
            m_ChangeDirection = true;
        }
    }
    if (m_ChangeDirection)
    {
        m_ObjectCenterPosition.x -= FrameDistance;
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
        m_Rect = srcrect1;
    }
    if (m_Timer <= 0)
    {
        m_Rect = srcrect2;
        m_Timer = 100.0f;
    }
}

void SpaceInvader::Render(SDL_Renderer* pRenderer)
{
    SDL_Rect dstrect = { m_ObjectCenterPosition.x, m_ObjectCenterPosition.y, m_ObjectSize.x, m_ObjectSize.y };
    //SDL_SetRenderDrawColor(pRenderer, 255, 255, 255, 255);
   // SDL_RenderFillRect(pRenderer, &dstrect);
    SDL_RenderCopy(pRenderer, m_pTexture, &m_Rect, &dstrect);
    //SDL_RenderCopy(m_pRenderer, m_pTexture, NULL, NULL);
}
