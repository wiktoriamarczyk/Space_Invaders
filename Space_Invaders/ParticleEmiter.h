#pragma once
#include "GameObject.h"

struct ParticleData
{
    // pozycja partikla w przestrzeni ParticleEmiter (pozycja partikla na ekranie to m_ParticlePosition + ParticleEmiter.m_Position)
    vec2 m_ParticlePosition;
    // kwektor ierunek ruchu - jego d�igo�c to dodatkowo pr�dko�� na sekund�
    vec2 m_DirectionVector;
    // pozosta�y czas �ycia (ile sekund mu zosta�o)
    float m_LifeTime;
    // pocz�tkowy czas "pauzy" - przez ten czas partikiel nic nie robi ani si� nie rysuje
    float m_StartDelayTime;
    // skala partikla
    float m_Scale;
};

class ParticleEmiter : public GameObject
{
public:
    ParticleEmiter(int ParticleCount, float Scale, float MaxLifeTime);
    void Update(float DeltaTime)override;
    void Render(SDL_Renderer* Renderer)override;

private:
    vector<ParticleData> m_Particles;
};
