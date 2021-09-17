#include "SpaceInvader.h"
#include "Engine.h"

bool SpaceInvader::m_ChangeDirectionX = false;
int SpaceInvader::m_NumOfInvaders = 0;
int SpaceInvader::m_NumOfPoints = 0;
//float SpaceInvader::m_Speed = INVADER_SPEED;

SDL_Surface* SpaceInvader::m_pImage = nullptr;

SDL_Texture* SpaceInvader::m_pTexture1 = nullptr;
SDL_Texture* SpaceInvader::m_pTexture2 = nullptr;
SDL_Texture* SpaceInvader::m_pTexture3 = nullptr;
SDL_Texture* SpaceInvader::m_pTexture4 = nullptr;

bool SpaceInvader::ExitGame = false;

SpaceInvader::SpaceInvader(float PosX, float PosY, shared_ptr<Gun> MyGun)
{
    m_Gun = MyGun;

    m_InvaderID = m_NumOfInvaders;
    m_NumOfInvaders++;

    m_pTexture = GetTexture();

    m_StartingPointPosition.x = PosX;
    m_StartingPointPosition.y = PosY;

    m_ObjectSize.x = OBJECT_WIDTH;
    m_ObjectSize.y = OBJECT_HEIGHT;
    
    m_Speed = INVADER_SPEED;
}

void SpaceInvader::Update(float DeltaTime)
{
    float FrameDistance = m_Speed * DeltaTime;
    vec2 ObjectTopLeftCorner = m_StartingPointPosition;
    vec2 ObjectBottomRightCorner = m_StartingPointPosition + m_ObjectSize;
    vec2 tempPos = m_StartingPointPosition;

    SDL_Rect srcrect1 = { 0, 0, 26, 26 };
    SDL_Rect srcrect2 = { 26, 0, 26, 26 };

    if (!m_ChangeDirectionX)
    {
        if (m_ChangeDirectionY)
        {
            m_StartingPointPosition.y += OBJECT_HEIGHT;
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
            m_StartingPointPosition.y += OBJECT_HEIGHT;
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

    // strzelanie do invaderow
    for (int i = 0; i < m_Gun->GetShots().size() ; ++i)
    {
        if (m_Gun->GetShots()[i]->GetDealingDamageStatus() == true)
        {
            if (m_Gun->GetShots()[i]->GetObjectPosition().x >= ObjectTopLeftCorner.x && m_Gun->GetShots()[i]->GetObjectPosition().x <= ObjectBottomRightCorner.x)
            {
                if (m_Gun->GetShots()[i]->GetObjectPosition().y <= ObjectBottomRightCorner.y && m_Gun->GetShots()[i]->GetObjectPosition().y >= ObjectTopLeftCorner.y)
                {
                    Engine::GetSingleton()->PlaySound("ShootingSpaceInvaderSound.wav");
                    m_IsDying = true;
                    m_Gun->GetShots()[i]->SetObjectStatus(false);
                    m_NumOfPoints = m_NumOfPoints + m_PointsForInvader;
                }
            }
        }
    }

    if (m_IsDying)
    {
        m_MovementRect = srcrect1;
        m_pTexture = m_pTexture4;

        m_DyingTimer--;

        if (m_DyingTimer <= 0)
        {
            m_ObjectIsAlive = false;
        }
    }

    // strzelaja tylko invadery na samej gorze
    if (m_InvaderID <= 12)
    {
        m_ShootingTimer--;

        if (m_ShootingTimer <= 0)
        {
            m_ShootingTimer = 50.0f;

            if (m_InvaderID == RandNumber())
            {
                m_Gun->Shoot(m_StartingPointPosition.x, ObjectBottomRightCorner.y);
            }
        }
    }

    // DO POPRAWY - POWINNY ZMIENIAC TEKSTURE, KIEDY WYKONAJA RUCH
    if (!m_IsDying)
    {
        m_TextureTimer--;

        if (m_TextureTimer == 50.0f)
        {
            Engine::GetSingleton()->PlaySound("MovementSound.wav");
            m_MovementRect = srcrect1;
        }
        if (m_TextureTimer <= 0)
        {
            Engine::GetSingleton()->PlaySound("MovementSound.wav");
            m_MovementRect = srcrect2;
            m_TextureTimer = 100.0f;
        }
    }

    // =============TEST==========
    if (SDL_IsKeyPressed(SDL_SCANCODE_W))
    {
        m_Speed = 0; 
    }
    if (SDL_IsKeyPressed(SDL_SCANCODE_S))
    {
        m_Speed = INVADER_SPEED;
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
        m_PointsForInvader = 30;
    }
    if (m_InvaderID >= 13 && m_InvaderID <= 38)
    {
        m_pTexture = m_pTexture2;
        m_PointsForInvader = 20;
    }
    if (m_InvaderID >= 39 && m_InvaderID <= 64)
    {
        m_pTexture = m_pTexture3;
        m_PointsForInvader = 10;
    }
    return m_pTexture;
}

void SpaceInvader::InitializeSpaceInvaderTexture(SDL_Renderer* pRenderer)
{
    // ===================TEST======================================
    std::cout << "W -> STOP INVADERS\nS -> START INVADERS AGAIN\n";

    m_pImage = IMG_Load("../Data/SpaceInvaders1.png");
    m_pTexture1 = SDL_CreateTextureFromSurface(pRenderer, m_pImage);
    m_pImage = IMG_Load("../Data/SpaceInvaders2.png");
    m_pTexture2 = SDL_CreateTextureFromSurface(pRenderer, m_pImage);
    m_pImage = IMG_Load("../Data/SpaceInvaders3.png");
    m_pTexture3 = SDL_CreateTextureFromSurface(pRenderer, m_pImage);
    m_pImage = IMG_Load("../Data/puf.png");
    m_pTexture4 = SDL_CreateTextureFromSurface(pRenderer, m_pImage);
    SDL_FreeSurface(m_pImage);
}

void SpaceInvader::DestroyTextures()
{
    SDL_DestroyTexture(m_pTexture1);
    SDL_DestroyTexture(m_pTexture2);
    SDL_DestroyTexture(m_pTexture3);
}

int SpaceInvader::RandNumber()
{
    return rand() % 13;
}
