#include "Player.h"
#include "Engine.h"

Player::Player(vec2 Position, shared_ptr<Gun> MyGun, InGameState& Game) : m_Game(Game)
{
    m_Gun = MyGun;
    m_Position = Position;
    m_Size = vec2i(OBJECT_WIDTH, OBJECT_HEIGHT);
    m_Color = Color(1, 255, 1);
}

void Player::Update(float DeltaTime)
{
    if (SDL_IsKeyPressed(SDL_SCANCODE_2))
    {
        m_Game.SetPlayerLivesCount(0);
        m_IsAlive = false;
    }

    float FrameDistance = m_Gun->GetSpeed() * DeltaTime;
    vec2 ObjectTopLeftCorner = m_Position - m_Size/2;
    vec2 ObjectBottomRightCorner = m_Position + m_Size/2;

    if ((SDL_IsKeyPressed(SDL_SCANCODE_A) || (SDL_IsKeyPressed(SDL_SCANCODE_LEFT))) && ObjectTopLeftCorner.x >= 0 && m_Game.GetPlayerLivesCount() > 0)
    {
        m_Position.x -= FrameDistance;
    }
    
    vec2 PaddleBottomRightCorner = m_Position + m_Size / 2;
    if ((SDL_IsKeyPressed(SDL_SCANCODE_D) || (SDL_IsKeyPressed(SDL_SCANCODE_RIGHT))) && ObjectBottomRightCorner.x <= SCREEN_WIDTH && m_Game.GetPlayerLivesCount() > 0)
    {
        m_Position.x += FrameDistance;
    }

    // strzelanie przez gracza
    m_ShootingTimer -= DeltaTime;
    m_SpecialShootingTimer -= DeltaTime;
    m_ShieldTimer -= DeltaTime;

    if (SDL_IsKeyPressed(SDL_SCANCODE_SPACE) && (!m_IsHurt))
    {
        if (m_ShootingTimer <= 0)
        {
            m_Gun->Shoot(m_Position, eTeamID::PLAYER);
            Engine::GetSingleton()->PlaySound("Shot.wav");

            if (m_SpecialShootingTimer >= 0)
            {
                m_Gun->InitializeShotParams(vec2i(2 * SHOT_WIDTH, 2 * SHOT_HEIGHT), Color{1.f, 255.f, 1.f}, 2500);
                m_ShootingTimer = 0.25f;
            }
            else 
            {
                m_Gun->InitializeShotParams(vec2i(SHOT_WIDTH, SHOT_HEIGHT), Color{ 255.f, 255.f, 255.f }, 1500);
                m_ShootingTimer = 0.4f;
            }
        }
    }

    auto& Shots = m_Gun->GetShots();

    // strzelanie do gracza przez inavderow
    for (int i = 0; i < Shots.size(); ++i)
    {
        if (Shots[i]->GetTeamID() != eTeamID::INVADER)
        {
            continue;
        }

        if (Shots[i]->GetPosition().x >= ObjectTopLeftCorner.x && Shots[i]->GetPosition().x <= ObjectBottomRightCorner.x)
        {
            if (Shots[i]->GetPosition().y <= ObjectBottomRightCorner.y && Shots[i]->GetPosition().y >= ObjectTopLeftCorner.y)
            {
                if (!m_IsHurt)
                {
                    if (m_ShieldTimer < 0)
                    {
                        Engine::GetSingleton()->PlaySound("Bum.wav");
                        m_Game.SetPlayerLivesCount(m_Game.GetPlayerLivesCount() - 1);
                        m_IsHurt = true;
                        Shots[i]->SetStatus(false);
                    }
                    else
                    {
                        Shots[i]->SetTeamID(eTeamID::SUICIDE);
                    }
                }
            }
        }
    }

    // zranienie gracza
    if (m_IsHurt)
    {
        m_Timer -= DeltaTime;
        if (m_Timer <= 0)
        {
            m_IsHurt = false;
            m_Timer = 1.0f;
        }
    }

    // smierc gracza
    if (m_Game.GetPlayerLivesCount() <= 0)
    {
        m_IsHurt = true;
        auto pParticle = m_Game.CreateParticle(m_Position, 12, 1.75f, 0.5f);
        pParticle->SetColor(m_Color);
        m_IsAlive = false;
    }
}

void Player::Render(SDL_Renderer* pRenderer)
{
    vec2 ObjectTopLeftCorner = m_Position - m_Size / 2;

    if (m_IsHurt && m_Game.GetPlayerLivesCount() > 0 && m_ShieldTimer <= 0)
    {
        DisplayTexture("Gun_Damaged.png", ObjectTopLeftCorner, DisplayParameters{ .DisplaySize = m_Size });
    }
    else if (m_Game.GetPlayerLivesCount() > 0 && m_ShieldTimer > 0)
    {
        DisplayTexture("Gun_Shield.png", ObjectTopLeftCorner, DisplayParameters{ .DisplaySize = m_Size });
    }
    else if (!m_IsHurt && m_Game.GetPlayerLivesCount() > 0 && m_ShieldTimer <= 0)
    {
        DisplayTexture("Gun.png", ObjectTopLeftCorner, DisplayParameters{ .DisplaySize = m_Size });
    }
}

void Player::SetSpecialShootingTimer(float Timer)
{
    m_SpecialShootingTimer = Timer;
}

void Player::SetShieldTimer(float ShieldTimer)
{
    m_ShieldTimer = ShieldTimer;
}
