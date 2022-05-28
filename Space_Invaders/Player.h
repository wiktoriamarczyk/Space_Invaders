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

private:
    InGameState&             m_Game;
    bool                     m_IsHurt = false;
    float                    m_ShootingTimer = 30.0f;
    shared_ptr<Gun>          m_Gun;
    float                    m_Timer = 100.0f;
    float                    m_TextureTimer = 50.0f;
    int                      m_NumOfPoints = 0;

};

