#pragma once
#include "GameObject.h"

struct ParticleData
{
    vec2 m_ParticlePosition;
    vec2 m_DirectionVector;
    float m_LifeTime;
};

class ParticleEmiter : public GameObject
{
public:
    ParticleEmiter();
    void Update(float DeltaTime)override;
    void Render(SDL_Renderer* Renderer)override;

private:
    vector<ParticleData> m_Particles;


};

