#include "SpaceInvader.h"

bool SpaceInvader::m_ChangeDirectionX = false;
int SpaceInvader::m_NumOfInvaders = 0;
float SpaceInvader::m_Speed = INVADER_SPEED;

SDL_Surface* SpaceInvader::m_pImage = nullptr;

SDL_Texture* SpaceInvader::m_pTexture1 = nullptr;
SDL_Texture* SpaceInvader::m_pTexture2 = nullptr;
SDL_Texture* SpaceInvader::m_pTexture3 = nullptr;

bool SpaceInvader::ExitGame = false;

SpaceInvader::SpaceInvader(float PosX, float PosY)
{
    m_InvaderID = m_NumOfInvaders;
    m_NumOfInvaders++;

    m_pTexture = GetTexture();

    m_StartingPointPosition.x = PosX;
    m_StartingPointPosition.y = PosY;

    m_ObjectSize.x = INVADER_WIDTH;
    m_ObjectSize.y = INVADER_HEIGHT;
}

void SpaceInvader::Update(float DeltaTime)
{
    float FrameDistance = m_Speed * DeltaTime;
    vec2 ObjectTopLeftCorner = m_StartingPointPosition;
    vec2 ObjectBottomRightCorner = m_StartingPointPosition + m_ObjectSize;
    vec2 tempPos = m_StartingPointPosition;

    if (!m_ChangeDirectionX)
    {
        if (m_ChangeDirectionY)
        {
            m_StartingPointPosition.y += INVADER_HEIGHT;
            if (m_StartingPointPosition.y >= tempPos.y)
            {
                tempPos = m_StartingPointPosition;
                m_ChangeDirectionY = false;
            }
        }
        m_StartingPointPosition.x += FrameDistance;
        if (ObjectBottomRightCorner.x >= SCREEN_WIDTH)
        {
            m_ChangeDirectionX = true;
        }
    }
    if (m_ChangeDirectionX)
    {
        if (!m_ChangeDirectionY)
        {
            m_StartingPointPosition.y += INVADER_HEIGHT;
            if (m_StartingPointPosition.y >= tempPos.y)
            {
                tempPos = m_StartingPointPosition;
                m_ChangeDirectionY = true;
            }
        }
        m_StartingPointPosition.x -= FrameDistance;
        if (ObjectTopLeftCorner.x <= 0)
        {
            m_ChangeDirectionX = false;
        }
    }

    SDL_Rect srcrect1 = { 0, 0, 820, 820 };
    SDL_Rect srcrect2 = { 820, 0, 820, 820 };

    // DO POPRAWY - POWINNY ZMIENIAC TEKSTURE, KIEDY WYKONAJA RUCH
    m_TextureTimer--;

    if (m_TextureTimer == 50.0f)
    {
        m_MovementRect = srcrect1;
    }
    if (m_TextureTimer <= 0)
    {
        m_MovementRect = srcrect2;
        m_TextureTimer = 100.0f;
    }
    
    // =TODO= jesli Invader zostanie postrzelony -> m_Speed++
}

void SpaceInvader::Render(SDL_Renderer* pRenderer)
{
    SDL_Rect dstrect = { int(m_StartingPointPosition.x), int(m_StartingPointPosition.y), int(m_ObjectSize.x), int(m_ObjectSize.y) };
    //SDL_SetRenderDrawColor(pRenderer, 255, 255, 255, 255);
    // SDL_RenderFillRect(pRenderer, &dstrect);
    SDL_RenderCopy(pRenderer, m_pTexture, &m_MovementRect, &dstrect);
}

SDL_Texture* SpaceInvader::GetTexture()
{
    // to trza zrobic jakos matematycznie, bo sie patrzec na to nie da ¯\_(ツ)_/¯
    if (m_InvaderID <= 12)
    {
        m_pTexture = m_pTexture1;
    }
    if (m_InvaderID >= 13 && m_InvaderID <= 38)
    {
        m_pTexture = m_pTexture2;
    }
    if (m_InvaderID >= 39 && m_InvaderID <= 64)
    {
        m_pTexture = m_pTexture3;
    }
    return m_pTexture;
}

void SpaceInvader::InitializeSpaceInvaderTexture(SDL_Renderer* pRenderer)
{
    m_pImage = IMG_Load("../Data/SpaceInvaders1.png");
    m_pTexture1 = SDL_CreateTextureFromSurface(pRenderer, m_pImage);
    m_pImage = IMG_Load("../Data/SpaceInvaders2.png");
    m_pTexture2 = SDL_CreateTextureFromSurface(pRenderer, m_pImage);
    m_pImage = IMG_Load("../Data/SpaceInvaders3.png");
    m_pTexture3 = SDL_CreateTextureFromSurface(pRenderer, m_pImage);
    SDL_FreeSurface(m_pImage);
}

void SpaceInvader::DestroyTextures()
{
    SDL_DestroyTexture(m_pTexture1);
    SDL_DestroyTexture(m_pTexture2);
    SDL_DestroyTexture(m_pTexture3);
}