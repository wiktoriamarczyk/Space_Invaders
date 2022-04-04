#pragma once
#include "GameObject.h"

class Shot : public GameObject
{
public:
    Shot(vec2 Position, vec2i Size, int Speed, eTeamID Team);
    void Update(float DeltaTime)override;
    void Render(SDL_Renderer* pRenderer)override;
    eTeamID GetTeamID()const;

private:
    float   m_LivingTimer = 10.0f;
    int     m_Speed = 0;
    eTeamID m_TeamID = eTeamID::UNKNOWN;
};