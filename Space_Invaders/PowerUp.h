#pragma once
#include "GameObject.h"

class Player;

class PowerUp : public GameObject
{
public:
    PowerUp(string Name);
    void Update(float DeltaTime)override;
    void Render(SDL_Renderer* pRenderer)override;
    virtual void Activate(Player& player) = 0;
    void SetScale(vec2 Scale);
    
private:
    string m_Name;
    vec2 m_Scale;
};