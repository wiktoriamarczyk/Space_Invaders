#include "Gun.h"
#include "Engine.h"

int Gun::m_NumOfLives = 3;

void Gun::InitializeGun(SDL_Renderer* pRenderer, float PosX, float PosY)
{
    m_Position.x = PosX;
    m_Position.y = PosY;

    m_Size.x = OBJECT_WIDTH;
    m_Size.y = OBJECT_HEIGHT;
}

void Gun::Update(float DeltaTime)
{
    float FrameDistance = GUN_SPEED * DeltaTime;
    vec2 ObjectTopLeftCorner = m_Position;
    vec2 ObjectBottomRightCorner = m_Position + m_Size;

    if ((SDL_IsKeyPressed(SDL_SCANCODE_A) || (SDL_IsKeyPressed(SDL_SCANCODE_LEFT)))&& ObjectTopLeftCorner.x >= 0)
    {
        m_Position.x -= FrameDistance;
    }

    vec2 PaddleBottomRightCorner = m_Position + m_Size / 2;
    if ((SDL_IsKeyPressed(SDL_SCANCODE_D) || (SDL_IsKeyPressed(SDL_SCANCODE_RIGHT)))&& ObjectBottomRightCorner.x <= SCREEN_WIDTH)
    {
        m_Position.x += FrameDistance;
    }

    // strzelanie
    m_ShootingTimer--;

    if (SDL_IsKeyPressed(SDL_SCANCODE_SPACE) && (!m_IsHurt))
    {
        if (m_ShootingTimer <= 0)
        {
            m_Shots.push_back(make_shared<Shot>(m_Position, vec2i(SHOT_WIDTH, SHOT_HEIGHT), 1500));
            Engine::GetSingleton()->PlaySound("Shot.wav");
            m_ShootingTimer = 30.0f;
        }
    }

    // update strzal i usuwanie tych, ktore zostaly juz wystrzelone
    for (int i = 0; i < m_Shots.size();)
    {
        m_Shots[i]->Update(DeltaTime);

        if (m_Shots[i]->GetStatus() == false)
        {
            m_Shots.erase(m_Shots.begin() + i);
        }
        else
        {
            ++i;
        }
    }
    
    // strzelanie do gracza przez inavderow
     for (int i = 0; i < m_Shots.size(); ++i)
     {
         if (m_Shots[i]->GetPosition().x >= ObjectTopLeftCorner.x && m_Shots[i]->GetPosition().x <= ObjectBottomRightCorner.x)
         {
             if (m_Shots[i]->GetPosition().y <= ObjectBottomRightCorner.y && m_Shots[i]->GetPosition().y >= ObjectTopLeftCorner.y)
             {
                 Engine::GetSingleton()->PlaySound("Bum.wav");
                 m_NumOfLives--;
                 m_IsHurt = true;
                 m_Shots[i]->SetStatus(false);
             }
         }
     }

    if (m_IsHurt)
    {
        m_Timer--;
        if (m_Timer <= 0)
        {
            m_IsHurt = false;
            m_Timer = 25.0f;
        }
    }

    if (m_NumOfLives <= 0)
    {
        m_IsHurt = true;
        m_Timer--;
        if (m_Timer <= 0)
        {
            m_IsAlive = false;
        }
    }
}

void Gun::Render(SDL_Renderer* pRenderer)
{
    if (m_IsHurt)
    {
        DisplayTexture("puf.png", m_Position, m_Size);
    }
    else  DisplayTexture("Gun.png", m_Position, m_Size);


   for (int i = 0; i < m_Shots.size(); ++i)
   {
       m_Shots[i]->Render(pRenderer);
   }
}

vector<shared_ptr<Shot>> Gun::GetShots()
{
    return m_Shots;
}

void Gun::Shoot(vec2 Pos, vec2i Size, int Speed)
{
    m_Shots.push_back(make_shared<Shot>(Pos, Size, Speed));
    m_Shots.back()->SetDealingDamage(false);
}