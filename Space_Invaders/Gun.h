#pragma once
#include "GameObject.h"
#include "Shot.h"

class Gun : public GameObject
{
public:
    Gun()=default;
    ~Gun() {};
    void InitializeGun(SDL_Renderer* pRenderer, float PosX, float PosY);
    void Update(float DeltaTime)override;
    void Render(SDL_Renderer* pRenderer)override;
    vector<shared_ptr<Shot>> GetShots();
    void Shoot(vec2 Pos, vec2i Size, int Speed);
    static int m_NumOfLives;

private:
    vector<shared_ptr<Shot>> m_Shots;
    float                    m_ShootingTimer = 30.0f; //30.0f
    //float                    m_TextureTimer = 25.0f;
    float                    m_Timer = 25.0f;
    bool                     m_IsHurt = false;
};

