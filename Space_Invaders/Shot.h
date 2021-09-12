#pragma once
#include "GameObject.h"

class Shot : public GameObject
{
public:
    Shot(vec2 Position);
    void Update(float DeltaTime)override;
    void Render(SDL_Renderer* pRenderer)override;

private:
    vec2 m_GunPosition;
    bool m_ShootYourShot = false; // fajny 80s utwor
    float m_LivingTimer = 100.0f;
};