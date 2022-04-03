#include "Player.h"
#include "Engine.h"

Player::Player(shared_ptr<Gun> MyGun, vec2 Position)
{
    m_Gun = MyGun;
    m_Position = Position;
    m_Size = vec2i(OBJECT_WIDTH, OBJECT_HEIGHT);
}

void Player::Update(float DeltaTime)
{
    float FrameDistance = GUN_SPEED * DeltaTime;
    vec2 ObjectTopLeftCorner = m_Position - m_Size/2;
    vec2 ObjectBottomRightCorner = m_Position + m_Size/2;

    if ((SDL_IsKeyPressed(SDL_SCANCODE_A) || (SDL_IsKeyPressed(SDL_SCANCODE_LEFT))) && ObjectTopLeftCorner.x >= 0)
    {
        m_Position.x -= FrameDistance;
    }

    vec2 PaddleBottomRightCorner = m_Position + m_Size / 2;
    if ((SDL_IsKeyPressed(SDL_SCANCODE_D) || (SDL_IsKeyPressed(SDL_SCANCODE_RIGHT))) && ObjectBottomRightCorner.x <= SCREEN_WIDTH)
    {
        m_Position.x += FrameDistance;
    }

    // strzelanie przez gracza
    m_ShootingTimer--;

    if (SDL_IsKeyPressed(SDL_SCANCODE_SPACE) && (!m_IsHurt))
    {
        if (m_ShootingTimer <= 0)
        {
            m_Gun->Shoot(m_Position, vec2i(SHOT_WIDTH, SHOT_HEIGHT), 1500, eTeamID::PLAYER);
            Engine::GetSingleton()->PlaySound("Shot.wav");
            m_ShootingTimer = 30.0f;
        }
    }

    auto& Shots = m_Gun->GetShots();

    // strzelanie do gracza przez inavderow
    for (int i = 0; i < Shots.size(); ++i)
    {
        if (Shots[i]->GetTeamID() == eTeamID::PLAYER)
        {
            continue;
        }

        if (Shots[i]->GetPosition().x >= ObjectTopLeftCorner.x && Shots[i]->GetPosition().x <= ObjectBottomRightCorner.x)
        {
            if (Shots[i]->GetPosition().y <= ObjectBottomRightCorner.y && Shots[i]->GetPosition().y >= ObjectTopLeftCorner.y)
            {
                if (!m_IsHurt)
                {
                    Engine::GetSingleton()->PlaySound("Bum.wav");
                    m_NumOfLives--;
                    m_IsHurt = true;
                    Shots[i]->SetStatus(false);
                }
            }
        }
    }

    if (m_IsHurt)
    {
        m_Timer--;
        if (m_Timer <= 0)
        {
            m_IsHurt = false;
            m_Timer = 40.0f;
        }
    }

    if (m_NumOfLives <= 0)
    {
        m_Timer = 100.0f;
        m_IsHurt = true;
        m_Timer--;
        if (m_Timer <= 0)
        {
            m_IsAlive = false;
        }
    }
}

void Player::Render(SDL_Renderer* pRenderer)
{
    vec2 ObjectTopLeftCorner = m_Position - m_Size / 2;
    if (m_IsHurt)
    {
        //DisplayTexture("puf.png", (vec2i)m_Position, m_Size);
    }
    else DisplayTexture("Gun.png", m_Position, DisplayParameters{ .DisplaySize = m_Size });

}

void Player::SetLivesCount(int NumOfLives)
{
    m_NumOfLives = NumOfLives;
}

int Player::GetLivesCount()
{
    return m_NumOfLives;
}
