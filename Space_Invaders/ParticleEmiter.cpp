#include "ParticleEmiter.h"

ParticleEmiter::ParticleEmiter()
{
    const int ParticleCount = 5;

    float AngleDistance = 3.14f * 2 / ParticleCount;

    for (int i = 0; i < ParticleCount; ++i)
    {
        ParticleData tmp;
        
        //tmp.m_ParticlePosition.x = GetRandFloat(-100.0f, 100.0f);
        //tmp.m_ParticlePosition.y = GetRandFloat(-100.0f, 100.0f);

        float Angle = AngleDistance * i;// +GetRandFloat(-5.0f, 5.0f);
        vec2 Vec2Dir(sin(Angle), cos(Angle));

        float ParticleSpeed = GetRandFloat(90.0f, 100.0f);

        // wektor kierunku, ktorego dlugosc wyznacza predkosc poruszania particla na sekunde (dlatego przemnazamy przez particlespeed)
        tmp.m_DirectionVector = Vec2Dir * ParticleSpeed;
        tmp.m_LifeTime = GetRandFloat(20.0f, 35.0f);

        m_Particles.push_back(tmp);
    }
}

void ParticleEmiter::Update(float DeltaTime)
{
    for (int i = 0; i < m_Particles.size(); ++i)
    {
        m_Particles[i].m_ParticlePosition += m_Particles[i].m_DirectionVector * DeltaTime;

        m_Particles[i].m_LifeTime--;

        if (m_Particles[i].m_LifeTime <= 0)
        {
            m_Particles.erase(m_Particles.begin() + i);
            --i;
        }
    }

    if (m_Particles.empty())
    {
        SetStatus(false);
    }
}

void ParticleEmiter::Render(SDL_Renderer* Renderer)
{
    vec2 Scale = vec2(4, 4);
    vec2i Size = vec2i(32, 32);

    for (int i = 0; i < m_Particles.size(); ++i)
    {
        //SDL_Rect srcrect{0, 0, 345/2, 345/2};
        vec2 Pos = m_Particles[i].m_ParticlePosition + m_Position - ((Scale*Size)/2);
        //SDL_Rect dstrect{Pos.x, Pos.y, 345/8, 345/8};
        //DisplayTexture("Particle1.jpg", srcrect, dstrect);

        DisplayTexture("Particle3.jpg", Pos, { .DisplaySize = Size , .DrawMode = eDrawMode::ADDITIVE , .DrawScale = Scale , .SrcTopLeft = vec2(0.0f,0.0f) , .SrcSize = vec2(1.0f,1.0f), .DrawColor = m_Color } );
    }
}