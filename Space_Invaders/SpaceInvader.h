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

private:
    InGameState&             m_Game;
    int                      m_InvaderID = 0;
    string                   m_Name;
    int                      m_PointsForInvader = 0;
    shared_ptr<Gun>          m_Gun;
    Vec2Rect                 m_MovementRect;
    float                    m_TextureTimer = 0.0f;
    float                    m_ShootingTimer = GetRandFloat(1.f, 2.f);
    bool                     m_ChangeDirectionY = false;

    static eInvaderDirection s_DirectionX;
};

