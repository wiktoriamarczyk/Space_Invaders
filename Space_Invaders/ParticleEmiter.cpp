#include "ParticleEmiter.h"

#include "Engine.h"

ParticleEmiter::ParticleEmiter(int ParticleCount, float Scale, float MaxLifeTime)
{    
    // ParticleCount - liczba partikli jak¹ stworzymy


    // k¹t pomiêdzy poszczególnymi partiklami -> pe³ne ko³o / liczba partikli
    float AngleDistance = 3.14f * 2 / ParticleCount;

    // tworzymy poszczególne partikle
    for (int i = 0; i < ParticleCount; ++i)
    {
        ParticleData tmp;

        // k¹t pod jakim leci ten partikiel
        float Angle = AngleDistance * i;
        // uwtwórz wektor jednostkowy kierunku z k¹ta u¿ywaj¹c:
        //
        //         /|
        //        / |
        //    Z  /  |
        //      /   | X
        //     /    |
        //    / a)  |
        //    -------
        //      Y
        //
        // a - k¹t
        // Z = 1 -> wektor ma d³ugoœæ 1
        // sin(a) = X/Z ->  X = sin(a)
        // cos(a) = Y/Z ->  Y = cos(a)

        vec2 Vec2Dir(sin(Angle), cos(Angle));

        // losujemy prêdkoœæ pomiêdzy 80 a 130 pixeli na sekundê
        float ParticleSpeed = GetRandFloat(80.0f, 130.0f);

        // wektor kierunku, ktorego dlugosc wyznacza predkosc poruszania particla na sekunde (dlatego przemnazamy przez particlespeed)
        tmp.m_DirectionVector = Vec2Dir * ParticleSpeed;
        // losujemy czas ¿ycia w sekundach
        tmp.m_LifeTime = GetRandFloat(MaxLifeTime / 2.f, MaxLifeTime);
        // losujemy czas "opóŸnienia" - czas na pocz¹tku w którym partikle nic nie robi i siê nie renderuje
        tmp.m_StartDelayTime = GetRandFloat(0.0f, 0.15f);
        // losujemy skalê
        tmp.m_Scale = GetRandFloat(Scale/2.f, Scale);
           
        // wrzucamy dane partikla do wektora
        m_Particles.push_back(tmp);
    }
}

void ParticleEmiter::Update(float DeltaTime)
{
    for (size_t i = 0; i < m_Particles.size(); ++i)
    {
        // póki mamy jakiœ czas "opóŸnienia" to go zmiejszammy i nie robimy nic innego
        if (m_Particles[i].m_StartDelayTime > 0)
        {
            m_Particles[i].m_StartDelayTime -= DeltaTime;
            continue;
        }

        m_Particles[i].m_ParticlePosition += m_Particles[i].m_DirectionVector * DeltaTime;

        m_Particles[i].m_LifeTime-=DeltaTime;

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
    vec2 Scale = vec2(2, 2);
    vec2i Size = vec2i(32, 32);

    for (size_t i = 0; i < m_Particles.size(); ++i)
    {
        // póki mamy jakiœ czas "opóŸnienia" to siê nie rysujemy
        if (m_Particles[i].m_StartDelayTime > 0)
            continue;

        const auto FinalScale = Scale * m_Particles[i].m_Scale;

        vec2 Pos = m_Particles[i].m_ParticlePosition + m_Position - ((FinalScale*Size)/2);

        DisplayTexture("Particle3.jpg", Pos, { .DisplaySize = Size , .DrawMode = eDrawMode::ADDITIVE , .DrawScale = FinalScale , .SrcTopLeft = vec2(0.0f,0.0f) , .SrcSize = vec2(1.0f,1.0f), .DrawColor = m_Color } );
    }
}