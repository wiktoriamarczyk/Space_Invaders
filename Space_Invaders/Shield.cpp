#include "Shield.h"

SDL_Texture* Shield::m_pTexture = nullptr;

Shield::Shield( float PosX, float PosY)
{
    m_StartingPointPosition.x = PosX;
    m_StartingPointPosition.y = PosY;
    m_ObjectSize.x = INVADER_WIDTH;
    m_ObjectSize.y = INVADER_HEIGHT;

    m_TextureDestructionLevel = {9, 33, 230, 190};
    //m_TextureDestructionLevel = { 320, 33, 162, 190 };
    //m_TextureDestructionLevel = { 644, 33, 79, 190 };
    //m_TextureDestructionLevel = { 63, 258, 130, 150 };
    //m_TextureDestructionLevel = { 291, 235, 228, 170};
    //m_TextureDestructionLevel = { 657, 235, 73, 170 };
    //m_TextureDestructionLevel = { 44, 504, 180, 190 };
}

void Shield::DestroyTexture()
{
    SDL_DestroyTexture(m_pTexture);
}

void Shield::InitializeShieldTexture(SDL_Renderer* pRenderer)
{
    SDL_Surface* m_pImage = IMG_Load("../Data/Shields.png");
    m_pTexture = SDL_CreateTextureFromSurface(pRenderer, m_pImage);
    SDL_FreeSurface(m_pImage);
}

void Shield::Update(float DeltaTime)
{

  
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