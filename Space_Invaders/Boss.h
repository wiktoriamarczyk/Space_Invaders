#pragma once
#include "GameObject.h"
#include "Gun.h"
#include "InGameState.h"

class Boss : public GameObject
{
public:
    Boss(shared_ptr<Gun> MyGun, InGameState& Game);
    void Update(float DeltaTime)override;
    void Render(SDL_Renderer* pRenderer)override;

    void SetNumOfLives(int Value);
    int GetNumOfLives()const;

private:
    InGameState&    m_Game;
    shared_ptr<Gun> m_Gun;
    int             m_NumOfLives = 30;
    bool            m_PlayMusic = true;
    bool            m_PlayDeathSound = true;
    float           m_DyingTimer = 3.0f;
    float           m_ShootingTimer = 40.0f;
    int             m_PointsForKill = 100;
};

