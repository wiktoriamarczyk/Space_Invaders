#pragma once
#include "GameObject.h"

class Shot : public GameObject
{
public:
    Shot(vec2 Position, vec2i Size, int Speed);
    void Update(float DeltaTime)override;
    void Render(SDL_Renderer* pRenderer)override;
    bool GetDealingDamageStatus();
    void SetDealingDamage(bool DealingDamage);

private:
    vec2  m_GunPosition;
    float m_LivingTimer = 100.0f;
    bool  m_DealingDamage = true;
    int   m_Speed = 0;
};