#include "Gun.h"
#include "Engine.h"

int Gun::m_NumOfLives = 3;

Gun::~Gun()
{
    SDL_DestroyTexture(m_pDyingTexture);
    SDL_DestroyTexture(m_pNormalTexture);
}

void Gun::InitializeGun(SDL_Renderer* pRenderer, float PosX, float PosY)
{
    m_StartingPointPosition.x = PosX;
    m_StartingPointPosition.y = PosY;

    m_ObjectSize.x = OBJECT_WIDTH;
    m_ObjectSize.y = OBJECT_HEIGHT;

    SDL_Surface* m_pImage = IMG_Load("../Data/Gun.png");
    m_pNormalTexture = SDL_CreateTextureFromSurface(pRenderer, m_pImage);
    SDL_FreeSurface(m_pImage);

    m_pImage = IMG_Load("../Data/puf.png");
    m_pDyingTexture = SDL_CreateTextureFromSurface(pRenderer, m_pImage);
    SDL_FreeSurface(m_pImage);

    m_pTexture = m_pNormalTexture;
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

    if (SDL_IsKeyPressed(SDL_SCANCODE_SPACE) && (!m_IsDying))
    {
        if (m_ShootingTimer <= 0)
        {
            m_Shots.push_back(make_shared<Shot>(m_StartingPointPosition));
            Engine::GetSingleton()->PlaySound("Shot.wav");
            m_ShootingTimer = 15.0f;
        }
    }

    // update strzal i usuwanie strzal, ktorym zycie juz sie skonczylo
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
    
    // strzelanie do broni przez inavderow
     for (int i = 0; i < m_Shots.size(); ++i)
     {
         if (m_Shots[i]->GetObjectPosition().x >= ObjectTopLeftCorner.x && m_Shots[i]->GetObjectPosition().x <= ObjectBottomRightCorner.x)
         {
             if (m_Shots[i]->GetObjectPosition().y <= ObjectBottomRightCorner.y && m_Shots[i]->GetObjectPosition().y >= ObjectTopLeftCorner.y)
             {
                 Engine::GetSingleton()->PlaySound("Bum.wav");
                 m_NumOfLives--;
                 m_IsDying = true;
                 m_Shots[i]->SetObjectStatus(false);
             }
         }
     }

    if (m_IsDying)
    {
        m_pTexture = m_pDyingTexture;
        m_TextureTimer--;
        if (m_TextureTimer <= 0)
        {
            m_pTexture = m_pNormalTexture;
            m_IsDying = false;
            m_TextureTimer = 25.0f;
        }
    }

    if (m_NumOfLives <= 0)
    {
        m_pTexture = m_pDyingTexture;

        m_DyingTimer--;
        if (m_DyingTimer <= 0)
        {
            m_ObjectIsAlive = false;
        }
    }
}

void Gun::Render(SDL_Renderer* pRenderer)
{
    SDL_Rect dstrect = { int(m_StartingPointPosition.x), int(m_StartingPointPosition.y), int(m_ObjectSize.x), int(m_ObjectSize.y) };
    //SDL_SetRenderDrawColor(pRenderer, 255, 255, 255, 255);
    //SDL_RenderFillRect(pRenderer, &dstrect);
    SDL_RenderCopy(pRenderer, m_pTexture, NULL, &dstrect);


   for (int i = 0; i < m_Shots.size(); ++i)
   {
       m_Shots[i]->Render(pRenderer);
   }
}

vector<shared_ptr<Shot>> Gun::GetShots()
{
    return m_Shots;
}

void Gun::Shoot(float PosX, float PosY, vec2 Size)
{
    vec2 Tmp (PosX, PosY);
    m_Shots.push_back(make_shared<Shot>(Tmp, Size));
    m_Shots.back()->SetDealingDamage(false);
}