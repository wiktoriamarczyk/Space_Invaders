#include "Gun.h"

Gun::~Gun()
{
    SDL_DestroyTexture(m_pTexture);
}

void Gun::InitializeGun(SDL_Renderer* pRenderer, float PosX, float PosY)
{
    m_StartingPointPosition.x = PosX;
    m_StartingPointPosition.y = PosY;

    m_ObjectSize.x = OBJECT_WIDTH;
    m_ObjectSize.y = OBJECT_HEIGHT;

    SDL_Surface* m_pImage = IMG_Load("../Data/Gun.png");
    m_pTexture = SDL_CreateTextureFromSurface(pRenderer, m_pImage);
    SDL_FreeSurface(m_pImage);
}

void Gun::Update(float DeltaTime)
{
    float FrameDistance = GUN_SPEED * DeltaTime;
    vec2 ObjectTopLeftCorner = m_StartingPointPosition;
    vec2 ObjectBottomRightCorner = m_StartingPointPosition + m_ObjectSize;

    if (SDL_IsKeyPressed(SDL_SCANCODE_A) && ObjectTopLeftCorner.x >= 0)
    {
        m_StartingPointPosition.x -= FrameDistance;
    }

    vec2 PaddleBottomRightCorner = m_StartingPointPosition + m_ObjectSize / 2;
    if (SDL_IsKeyPressed(SDL_SCANCODE_D) && ObjectBottomRightCorner.x <= SCREEN_WIDTH)
    {
        m_StartingPointPosition.x += FrameDistance;
    }

    // szczelanie
    m_ShootingTimer--;

    if (SDL_IsKeyPressed(SDL_SCANCODE_SPACE))
    {
        if (m_ShootingTimer <= 0)
        {
            m_Shots.push_back(make_shared<Shot>(m_StartingPointPosition));
            m_ShootingTimer = 30.0f;
        }
    }

    if (!m_Shots.empty())
    {
        for (int i = 0; i < m_Shots.size();)
        {
            m_Shots[i]->Update(DeltaTime);
            if (m_Shots[i]->GetObjectStatus() == false)
            {
                m_Shots.erase(m_Shots.begin() + i);
            }
            else
            {
                ++i;
            }
        }
    }
}

void Gun::Render(SDL_Renderer* pRenderer)
{
    SDL_Rect dstrect = { m_StartingPointPosition.x, m_StartingPointPosition.y, m_ObjectSize.x, m_ObjectSize.y };
    //SDL_SetRenderDrawColor(pRenderer, 255, 255, 255, 255);
    //SDL_RenderFillRect(pRenderer, &dstrect);
    SDL_RenderCopy(pRenderer, m_pTexture, NULL, &dstrect);

    if (!m_Shots.empty())
    {
        for (int i = 0; i < m_Shots.size(); ++i)
        {
            m_Shots[i]->Render(pRenderer);
        }
    }
}

vector<shared_ptr<Shot>> Gun::GetShots()
{
    return m_Shots;
}

void Gun::SetShotStatus(bool ShotStatus)
{
    m_ShootYourShot = ShotStatus;
}
