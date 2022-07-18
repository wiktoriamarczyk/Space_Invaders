#pragma once
#include "GameObject.h"

class PowerUp : public GameObject
{
public:
    PowerUp(ePowerUpType Type);
    void Update(float DeltaTime)override;
    void Render(SDL_Renderer* pRenderer)override;

    void SetName(string Name);
    void SetScale(vec2 Scale);
    
private:
    ePowerUpType m_Type = ePowerUpType::UNKNOWN;
    string       m_Name;
    vec2         m_Scale{1, 1};

};

