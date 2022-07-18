#pragma once
#include "GameObject.h"
#include "Shot.h"

class Gun : public GameObject
{
public:
    Gun();
    void Update(float DeltaTime)override;
    void Render(SDL_Renderer* pRenderer)override;
    vector<shared_ptr<Shot>>& GetShots();
    void Shoot(vec2 Pos, vec2i Size, int Speed, eTeamID Team);

private:
    vector<shared_ptr<Shot>> m_Shots;
};