#pragma once
#include "GameObject.h"
#include "Gun.h"
#include "InGameState.h"

class SpaceInvader : public GameObject
{
public:
    SpaceInvader(vec2 Position, shared_ptr<Gun> MyGun, InGameState& Game);
    void Update(float DeltaTime)override;
    void Render(SDL_Renderer* pRenderer)override;
    string GetName();

    static int m_NumOfPoints;
    static int m_NumOfInvaders;
    static float m_Speed;
    static int RandNumber();

private:
public:
    InGameState&    m_Game;
    int             m_InvaderID = 0;
    string          m_Name;
    shared_ptr<Gun> m_Gun;
    SDL_Rect        m_MovementRect;
    float           m_TextureTimer = 0.0f;
    float           m_ShootingTimer = 50.0f;
    float           m_DyingTimer = 25.0f;
    bool            m_IsDying = false;
    bool            m_ChangeDirectionY = false;
    int             m_PointsForInvader = 0;
    static bool     m_ChangeDirectionX;
};

