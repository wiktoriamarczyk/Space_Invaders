#pragma once
#include "GameObject.h"

class Shot : public GameObject
{
public:
    Shot(vec2 Position, eTeamID Team);
    void Update(float DeltaTime)override;
    void Render(SDL_Renderer* pRenderer)override;
    eTeamID GetTeamID()const;
    void InitializeParams(vec2i Size, Color MyColor, int Speed);

private:
    int     m_Speed = 0;
    eTeamID m_TeamID = eTeamID::UNKNOWN;
};