#pragma once
#include "GameObject.h"
#include "Gun.h"

class SpaceInvader : public GameObject
{
public:
    SpaceInvader(float PosX, float PosY, shared_ptr<Gun> MyGun);
    void Update(float DeltaTime)override;
    void Render(SDL_Renderer* pRenderer)override;
    string GetName();

    static int m_NumOfPoints;
    static int m_NumOfInvaders;
    static float m_Speed;
    static int RandNumber();

private:
public:
    int             m_InvaderID = 0;
    string          m_Name;
    shared_ptr<Gun> m_Gun;
    SDL_Rect        m_MovementRect;
    float           m_TextureTimer = 100.0f;
    float           m_ShootingTimer = 50.0f;
    float           m_DyingTimer = 25.0f;
    bool            m_IsDying = false;
    bool            m_ChangeDirectionY = false;
    int             m_PointsForInvader = 0;
    static bool     m_ChangeDirectionX;
};

