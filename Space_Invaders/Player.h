#pragma once
#include "GameObject.h"
#include "Gun.h"
#include "InGameState.h"

class Player : public GameObject
{
public:
    Player(vec2 Position, shared_ptr<Gun> MyGun, InGameState& Game);
    void Update(float DeltaTime)override;
    void Render(SDL_Renderer* pRenderer)override;
    void SetSpecialShootingTimer(float Timer);
    void SetShieldTimer(float ShieldTimer);

private:
    InGameState&             m_Game;
    bool                     m_IsHurt = false;
    float                    m_ShootingTimer = 0.4f;
    shared_ptr<Gun>          m_Gun;
    float                    m_Timer = 1.0f;
    float                    m_TextureTimer = 0.5f;
    int                      m_NumOfPoints = 0;
    float                    m_SpecialShootingTimer = 0.f;
    float                    m_ShieldTimer = 0.f;
};

