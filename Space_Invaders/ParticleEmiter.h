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
    float m_Scale = 1.0f;
    float m_Rotation = 0.0f;
    float m_RotationSpeed = 0.0f;

    Color m_Color = Color::WHITE;

    const char* m_Texture = "";
};

class ParticleEmiter : public GameObject
{
public:
    ParticleEmiter(int ParticleCount, float Scale, float MaxLifeTime, eParticleMode Mode);
    void Update(float DeltaTime)override;
    void Render(SDL_Renderer* Renderer)override;

private:
    void UpdateState(float DeltaTime);

    vector<ParticleData> m_Particles;
    eParticleMode        m_Mode;
    float                m_TimeToNextParticle = 0.f;
    float                m_Timer = 0.f;
    string               m_ParticleTexture = "Particle3.jpg";
};
