#pragma once
#include "GameObject.h"
#include "Gun.h"

class Player : public GameObject
{
public:
    Player(shared_ptr<Gun> MyGun, vec2 Position);
    void Update(float DeltaTime)override;
    void Render(SDL_Renderer* pRenderer)override;

    void SetLivesCount(int NumOfLives);
    int GetLivesCount();

private:

    bool                     m_IsHurt = false;
    float                    m_ShootingTimer = 30.0f;
    shared_ptr<Gun>          m_Gun;
    int                      m_NumOfLives = 3;
    float                    m_Timer = 40.0f;
    int                      m_NumOfPoints = 0;
};

