#include "SpaceInvader.h"
#include "Engine.h"

bool SpaceInvader::m_ChangeDirectionX = false;

SpaceInvader::SpaceInvader(vec2 Position, shared_ptr<Gun> MyGun, InGameState& Game) : m_Game(Game)
{
    m_Gun = MyGun;

    m_Game.SetSpaceInvadersNum(m_Game.GetSpaceInvadersNum() + 1);
    m_InvaderID = m_Game.GetSpaceInvadersNum();

    m_Name = GetName();
    m_Position = Position;
    m_Size = vec2i(OBJECT_WIDTH, OBJECT_HEIGHT);
    m_Speed = INVADER_SPEED;
}

void SpaceInvader::Update(float DeltaTime)
{
    if (SDL_IsKeyPressed(SDL_SCANCODE_0))
    {
        m_IsAlive = false;
        m_Game.SetSpaceInvadersNum(0);
    }


    float FrameDistance = m_Speed * DeltaTime;
    vec2 ObjectTopLeftCorner = m_Position;
    vec2 ObjectBottomRightCorner = m_Position + m_Size;
    vec2 tempPos = m_Position;

    vec2 ObjectTopLeftCorner = m_Position - m_Size/2;
    vec2 ObjectBottomRightCorner = m_Position + m_Size/2;

    // przemieszczanie sie invaderow
    if (!m_ChangeDirectionX)
    {
        if (m_ChangeDirectionY)
        {
            SetPosition( { m_Position.x , m_Position.y + OBJECT_HEIGHT } );
            
            if (m_Position.y >= tempPos.y)
            {
                tempPos = m_Position;
                m_ChangeDirectionY = false;
            }
        }
        SetPosition({ m_Position.x + FrameDistance , m_Position.y  });

        if (ObjectBottomRightCorner.x >= SCREEN_WIDTH)
        {
            m_ChangeDirectionX = true;
        }
    }

    if (m_ChangeDirectionX)
    {
        if (!m_ChangeDirectionY)
        {
            SetPosition({ m_Position.x , m_Position.y + OBJECT_HEIGHT });
            if (m_Position.y >= tempPos.y)
            {
                tempPos = m_Position;
                m_ChangeDirectionY = true;
            }
        }
        SetPosition({ m_Position.x - FrameDistance , m_Position.y });
        if (ObjectTopLeftCorner.x <= 0)
        {
            m_ChangeDirectionX = false;
        }
    }

    // inwazja invaderow
    if (ObjectBottomRightCorner.y >= SCREEN_HEIGHT)
    {
        m_Game.GetPlayer()->SetLivesCount(m_Game.GetPlayer()->GetLivesCount() - 1);
    }

    // strzelanie do invaderow
    for (int i = 0; i < m_Gun->GetShots().size() ; ++i)
    {
        if (m_Gun->GetShots()[i]->GetTeamID() == eTeamID::PLAYER)
        {
            if (m_Gun->GetShots()[i]->GetPosition().x >= ObjectTopLeftCorner.x && m_Gun->GetShots()[i]->GetPosition().x <= ObjectBottomRightCorner.x)
            {
                if (m_Gun->GetShots()[i]->GetPosition().y <= ObjectBottomRightCorner.y && m_Gun->GetShots()[i]->GetPosition().y >= ObjectTopLeftCorner.y)
                {
                    Engine::GetSingleton()->PlaySound("ShootingSpaceInvaderSound.wav");
                    m_IsDying = true;
                    m_Gun->GetShots()[i]->SetStatus(false);
                    m_Game.SetNumOfPoints(m_Game.GetNumOfPoints() + m_PointsForInvader);
                    ///m_NumOfPoints = m_NumOfPoints + m_PointsForInvader;
                }
            }
        }
    }

    // zmiana tekstury umierajacych invaderow
    if (m_IsDying)
    {
        m_MovementRect = srcrect1;

        m_DyingTimer--;

        if (m_DyingTimer <= 0)
        {
            m_IsAlive = false;
            m_Game.SetSpaceInvadersNum(m_Game.GetSpaceInvadersNum() - 1);
        }
    }

    // strzelaja tylko najwyzej umieszczone invadery
    if (m_InvaderID <= 12)
    {
        m_ShootingTimer--;

        if (m_ShootingTimer <= 0)
        {
            m_ShootingTimer = 50.0f;

            if (m_InvaderID == m_Game.GetRandomValue(13))
            {
                m_Gun->Shoot(vec2(m_Position.x, ObjectBottomRightCorner.y), vec2i(SHOT_WIDTH, SHOT_HEIGHT), SHOT_SPEED, eTeamID::INVADER);
            }
        }
    }

    // zmiana tekstury poruszania sie invaderow
    if (!m_IsDying)
    {
        m_TextureTimer--;

        if (m_TextureTimer == 50.0f)
        {
            Engine::GetSingleton()->PlaySound("MovementSound.wav",0.125f);
            m_MovementRect = srcrect1;
        }
        if (m_TextureTimer <= 0)
        {
            Engine::GetSingleton()->PlaySound("MovementSound.wav",0.125f);
            m_MovementRect = srcrect2;
            m_TextureTimer = 100.0f;
        }
    }
}

void SpaceInvader::Render(SDL_Renderer* pRenderer)
{
    SDL_Rect dstrect = { int(m_Position.x), int(m_Position.y), int(m_Size.x), int(m_Size.y) };
 
    if (m_IsDying)
    {
        DisplayTexture("puf.png", (vec2i)m_Position, m_Size);
    }
    else DisplayTexture(m_Name + ".png", m_MovementRect, dstrect);
}

string SpaceInvader::GetName()
{
    if (m_InvaderID <= 12)
    {
        m_Name = "SpaceInvaders1";
        m_PointsForInvader = 30;
    }
    if (m_InvaderID >= 13 && m_InvaderID <= 26)
    {
        m_Name = "SpaceInvaders2";
        m_PointsForInvader = 20;
    }
    if (m_InvaderID >= 26 && m_InvaderID <= 39)
    {
        m_Name = "SpaceInvaders3";
        m_PointsForInvader = 10;
    }
    return m_Name;
}