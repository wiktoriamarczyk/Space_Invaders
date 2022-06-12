#include "SpaceInvader.h"
#include "Engine.h"

eInvaderDirection SpaceInvader::s_DirectionX = eInvaderDirection::RIGHT;

SpaceInvader::SpaceInvader(vec2 Position, shared_ptr<Gun> MyGun, InGameState& Game) : m_Game(Game)
{
    m_Gun = MyGun;
    m_InvaderID = m_Game.GetSpaceInvadersNum();
    m_Game.SetSpaceInvadersNum(m_Game.GetSpaceInvadersNum() + 1);

    if (m_InvaderID <= 12)
    {
        m_Name = "SpaceInvaders1";
        m_PointsForInvader = 30;
        m_Color = Color(255, 106, 0);
    }
    if (m_InvaderID >= 13 && m_InvaderID <= 25)
    {
        m_Name = "SpaceInvaders2";
        m_PointsForInvader = 20;
        m_Color = Color(87, 0, 127);
    }
    if (m_InvaderID >= 26 && m_InvaderID <= 38)
    {
        m_Name = "SpaceInvaders3";
        m_PointsForInvader = 15;
        m_Color = Color(31, 73, 135);
    }
    if (m_InvaderID >= 39)
    {
        m_Name = "SpaceInvaders4";
        m_PointsForInvader = 10;
        m_Color = Color(255, 251, 58);
    }

    m_Position = Position;
    m_Size = vec2i(OBJECT_WIDTH, OBJECT_HEIGHT);
    m_Speed = 10;
}

void SpaceInvader::Update(float DeltaTime)
{
    if (SDL_IsKeyPressed(SDL_SCANCODE_0))
    {
        m_IsAlive = false;
        m_Game.SetSpaceInvadersNum(0);
    }

    float FrameDistance = m_Speed * DeltaTime;

    vec2 ObjectCenter = m_Position;
    vec2 ObjectTopLeftCorner = m_Position - m_Size/2;
    vec2 ObjectBottomRightCorner = m_Position + m_Size/2;

    Vec2Rect srcrect1 = { { 0   , 0} , {0.5, 1} };
    Vec2Rect srcrect2 = { { 0.5 , 0} , {0.5, 1} };

    m_AngryTimer -= DeltaTime;
     
    if (m_AngryTimer > 0)
    {
        m_Speed = 50;
    }
    else m_Speed = 10 + 250 / (m_Game.GetSpaceInvadersNum() + 1);

    // przemieszczanie sie invaderow
    if (s_DirectionX == eInvaderDirection::RIGHT)
    {
        if (m_ChangeDirectionY)
        {
            SetPosition( { m_Position.x , m_Position.y + OBJECT_HEIGHT } );
            m_ChangeDirectionY = false;
        }

        SetPosition({ m_Position.x + FrameDistance , m_Position.y  });

        if (ObjectBottomRightCorner.x >= SCREEN_WIDTH)
        {
            s_DirectionX = eInvaderDirection::LEFT;
        }
    }

    if (s_DirectionX == eInvaderDirection::LEFT)
    {
        if (!m_ChangeDirectionY)
        {
            SetPosition({ m_Position.x , m_Position.y + OBJECT_HEIGHT });
            m_ChangeDirectionY = true;
        }

        SetPosition({ m_Position.x - FrameDistance , m_Position.y });

        if (ObjectTopLeftCorner.x <= 0)
        {
            s_DirectionX = eInvaderDirection::RIGHT;
        }
    }

    // inwazja invaderow
    if (ObjectBottomRightCorner.y >= SCREEN_HEIGHT)
    {
        m_Game.SetPlayerLivesCount(m_Game.GetPlayerLivesCount() - 1);
    }

    // strzelanie do invaderow
    for (int i = 0; i < m_Gun->GetShots().size() ; ++i)
    {
        if (m_Gun->GetShots()[i]->GetTeamID() != eTeamID::INVADER)
        {
            if (m_Gun->GetShots()[i]->GetPosition().x >= ObjectTopLeftCorner.x && m_Gun->GetShots()[i]->GetPosition().x <= ObjectBottomRightCorner.x)
            {
                if (m_Gun->GetShots()[i]->GetPosition().y <= ObjectBottomRightCorner.y && m_Gun->GetShots()[i]->GetPosition().y >= ObjectTopLeftCorner.y)
                {
                    Engine::GetSingleton()->PlaySound("ShootingSpaceInvaderSound.wav");
                    m_IsAlive = false;
                    m_Gun->GetShots()[i]->SetStatus(false);

                    if (m_Gun->GetShots()[i]->GetTeamID() == eTeamID::SUICIDE)
                    {
                        m_Game.SetPointsInfoTimer(2.f);
                        m_Game.SetNumOfPoints(m_Game.GetNumOfPoints() + 200);
                    }
                    else m_Game.SetNumOfPoints(m_Game.GetNumOfPoints() + m_PointsForInvader);
                }
            }
        }
    }

    // smierc invader'a
    if (!m_IsAlive)
    {
        // tworzenie particle'a
        auto pParticle = m_Game.CreateParticle(m_Position, 128, 1.75f, 0.5f);
        // ustawianie koloru particle'a
        Color color = m_Color;
        if (m_AngryTimer > 0)
        {
            //color = Color::RED;
            color = Color(255, 0, 0);
        }
        pParticle->SetColor(color);
        // losowanie powerup'a
        int PowerUpType = GetRandInt(1, 10);

        if (PowerUpType == (int)ePowerUpType::GUN_IMPROVMENT)
        {
            auto pPowerUp = m_Game.CreatePowerUp("PowerUp_Gun", m_Position, ePowerUpType::GUN_IMPROVMENT);
        }
        else if (PowerUpType == (int)ePowerUpType::HEALTH)
        {
            auto pPowerUp = m_Game.CreatePowerUp("PowerUp_Health", m_Position, ePowerUpType::HEALTH);
        }
        else if (PowerUpType == (int)ePowerUpType::SHIELD)
        {
            auto pPowerUp = m_Game.CreatePowerUp("PowerUp_Shield", m_Position, ePowerUpType::SHIELD);
            pPowerUp->SetScale(vec2{1.5f, 1.5f});
        }
        else if (PowerUpType == 4 || PowerUpType == 5)
        {
            PowerUpType = GetRandInt(1, 4);
            auto pPowerUp = m_Game.CreatePowerUp("PowerUp_QuestionMark", m_Position, (ePowerUpType)PowerUpType);
        }

        // zmniejszenie liczby invaderow o jednego
        m_Game.SetSpaceInvadersNum(m_Game.GetSpaceInvadersNum() - 1);
    }

    // strzelaja tylko najwyzej umieszczone invadery
    if (m_InvaderID <= 12)
    {
        m_ShootingTimer -= DeltaTime;

        if (m_ShootingTimer <= 0)
        {
            m_ShootingTimer = GetRandFloat(0.25f, 0.5f);

            if (m_InvaderID == GetRandInt(0, 12))
            {
                m_Gun->Shoot(vec2(m_Position.x, ObjectBottomRightCorner.y), eTeamID::INVADER);

                if (m_AngryTimer > 0)
                {
                    m_Gun->InitializeShotParams(vec2i(SHOT_WIDTH, SHOT_HEIGHT), Color{ 255.f, 255.f, 255.f }, 3 * SHOT_SPEED);
                }
                else m_Gun->InitializeShotParams(vec2i(SHOT_WIDTH, SHOT_HEIGHT), Color{ 255.f, 255.f, 255.f }, SHOT_SPEED);
            }
        }
    }

    // zmiana tekstury poruszania sie invaderow
    if (m_IsAlive)
    {
        m_TextureTimer -= DeltaTime;

        if (m_TextureTimer <= 0.5f)
        {
           // Engine::GetSingleton()->PlaySound("MovementSound.wav",0.125f);
            m_MovementRect = srcrect1;
        }
        if (m_TextureTimer <= 0)
        {
          //  Engine::GetSingleton()->PlaySound("MovementSound.wav",0.125f);
            m_MovementRect = srcrect2;
            m_TextureTimer = 1.0f;
        }
    }
}

void SpaceInvader::Render(SDL_Renderer* pRenderer)
{
    vec2 ObjectTopLeftCorner = m_Position - m_Size / 2;
    
   // Color color = Color::WHITE;
    Color color = Color(255, 255, 255);

    if (m_AngryTimer > 0)
    {
       // color = Color::RED;
        color = Color(255, 0, 0);
    }

    DisplayTexture(m_Name + ".png", ObjectTopLeftCorner, { .DisplaySize = vec2i(m_Size) , .SrcTopLeft = m_MovementRect.TopLeft , .SrcSize = m_MovementRect.Size, .DrawColor = color });
}

void SpaceInvader::SetAngryTimer(float Timer)
{
    m_AngryTimer = Timer;
}

string SpaceInvader::GetName()
{
    return m_Name;
}