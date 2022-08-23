#include "ParticleEmiter.h"

#include "Engine.h"

ParticleEmiter::ParticleEmiter(int ParticleCount, float Scale, float MaxLifeTime, eParticleMode Mode)
{
    m_Mode = Mode;

    if (m_Mode == eParticleMode::STARS_BACKGROUND)
    {
        m_TimeToNextParticle = 1.f / ParticleCount;
        m_Timer = m_TimeToNextParticle;

        for (int i = 0; i < 180*8; ++i)
            UpdateState(1.0f / 60.0f);
        return;
    }
    // ParticleCount - liczba partikli jaką stworzymy

    // kąt pomiędzy poszczególnymi partiklami -> pełne koło / liczba partikli
    float AngleDistance = 3.14f * 2 / ParticleCount;

    // tworzymy poszczególne partikle
    for (int i = 0; i < ParticleCount; ++i)
    {
        ParticleData tmp;

        // kąt pod jakim leci ten partikiel
        float Angle = AngleDistance * i;
        // uwtwórz wektor jednostkowy kierunku z kąta używając:
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
        // a - kąt
        // Z = 1 -> wektor ma długość 1
        // sin(a) = X/Z ->  X = sin(a)
        // cos(a) = Y/Z ->  Y = cos(a)

        vec2 Vec2Dir(sin(Angle), cos(Angle));

        // losujemy prędkość pomiędzy 80 a 130 pixeli na sekundę
        float ParticleSpeed = GetRandFloat(80.0f, 130.0f);

        // wektor kierunku, ktorego dlugosc wyznacza predkosc poruszania particla na sekunde (dlatego przemnazamy przez particlespeed)
        tmp.m_DirectionVector = Vec2Dir * ParticleSpeed;
        // losujemy czas życia w sekundach
        tmp.m_LifeTime = GetRandFloat(MaxLifeTime / 2.f, MaxLifeTime);
        // losujemy czas "opóźnienia" - czas na początku w którym partikle nic nie robi i się nie renderuje
        tmp.m_StartDelayTime = GetRandFloat(0.0f, 0.15f);
        // losujemy skalę
        tmp.m_Scale = GetRandFloat(Scale/2.f, Scale);

        tmp.m_Texture = m_ParticleTexture.c_str();

        // wrzucamy dane partikla do wektora
        m_Particles.push_back(tmp);
    }
}

void ParticleEmiter::Update(float DeltaTime)
{
    UpdateState(DeltaTime);
}

void ParticleEmiter::UpdateState(float DeltaTime)
{
    if (m_Mode == eParticleMode::STARS_BACKGROUND)
    {
        m_Timer -= DeltaTime;

        if (m_Timer <= 0)
        {
            vec2 Vec2Dir(0, 1);

            ParticleData tmp;

            // losujemy prędkość pomiędzy 80 a 130 pixeli na sekundę
            float ParticleSpeed = GetRandFloat(120.0f, 180.0f)/3;
            // początkowa pozycja partikla na osi X
            tmp.m_ParticlePosition.x = GetRandFloat(0, SCREEN_WIDTH);
            // wektor kierunku, ktorego dlugosc wyznacza predkosc poruszania particla na sekunde (dlatego przemnazamy przez particlespeed)
            tmp.m_DirectionVector = Vec2Dir * ParticleSpeed;
            // losujemy czas "opóźnienia" - czas na początku w którym partikle nic nie robi i się nie renderuje
            tmp.m_StartDelayTime = 0.f;
            // losujemy skalę
            tmp.m_Scale = GetRandFloat(0.25f, 7.5f);
            // losujemy obrót
            tmp.m_Rotation = GetRandFloat(0.0f, 360.f);

            // losujemy jedna z 8 tekstur dla particla
            switch (GetRandInt(0, 7))
            {
            case 0: tmp.m_Texture = "Particle7.png"; break;
            case 1: tmp.m_Texture = "Particle8.png"; break;
            case 2: tmp.m_Texture = "Particle9.png"; break;
            case 3: tmp.m_Texture = "Particle10.png";break;
            case 4: tmp.m_Texture = "Particle11.png";break;
            case 5: tmp.m_Texture = "Particle12.png";break;
            case 6: tmp.m_Texture = "Particle13.png";break;
            case 7: tmp.m_Texture = "Particle14.png";break;
            }

            // losujemy odcień niebieskiego dla cząsteczki
            tmp.m_Color.R = tmp.m_Color.G = 96 +GetRandInt(0, 64);
            tmp.m_Color.R -= 15;
            tmp.m_Color.G += 15;
            tmp.m_Color.B  = 240;
            tmp.m_Color.A = 255;

            // uzależniamy predkosc od skali - male gwiazdki lecą wolniej żeby udawały że sa dalej
            tmp.m_DirectionVector = tmp.m_DirectionVector * ( 0.5f + tmp.m_Scale/5);

            // czas życia na tyle dlugi żeby zdążyć dolecieć za ekran
            tmp.m_LifeTime = (float(SCREEN_HEIGHT)*1.5f) / tmp.m_DirectionVector.GetLength();

            // wrzucamy dane partikla do wektora
            m_Particles.push_back(tmp);

            m_Timer = m_TimeToNextParticle;
        }
    }

    for (size_t i = 0; i < m_Particles.size(); ++i)
    {
        // póki mamy jakiś czas "opóźnienia" to go zmiejszammy i nie robimy nic innego
        if (m_Particles[i].m_StartDelayTime > 0)
        {
            m_Particles[i].m_StartDelayTime -= DeltaTime;
            continue;
        }

        m_Particles[i].m_ParticlePosition += m_Particles[i].m_DirectionVector * DeltaTime;
        m_Particles[i].m_Rotation         += m_Particles[i].m_RotationSpeed * DeltaTime;

        m_Particles[i].m_LifeTime-=DeltaTime;

        if (m_Particles[i].m_LifeTime <= 0)
        {
            m_Particles.erase(m_Particles.begin() + i);
            --i;
        }
    }

    if (m_Mode == eParticleMode::POINT_EXPLOSION && m_Particles.empty())
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
        // póki mamy jakiś czas "opóźnienia" to się nie rysujemy
        if (m_Particles[i].m_StartDelayTime > 0)
            continue;

        const vec2   ParticleScale   = Scale * m_Particles[i].m_Scale;
        const float  ParticleRotation= m_Particles[i].m_Rotation;
        const vec2   ParticlePos     = m_Particles[i].m_ParticlePosition + m_Position;
        const Color  ParticleColor   = m_Particles[i].m_Color * m_Color;
        const string ParticleName    = m_Particles[i].m_Texture;

        if (m_Mode == eParticleMode::POINT_EXPLOSION)
        {

            DisplayTexture(ParticleName, ParticlePos, { .DisplaySize = Size , .DrawMode = eDrawMode::ADDITIVE , .DrawScale = ParticleScale , .Pivot = vec2(0.5f,0.5f), .DrawColor = ParticleColor, .Rotation = ParticleRotation });

        }
        else if( m_Mode == eParticleMode::STARS_BACKGROUND )
        {
            // najpierw poświata 
            vec2  FinalScale = ParticleScale;
            Color FinalColor = ParticleColor * Color(255,255,255,8);
            DisplayTexture("Particle6.png", ParticlePos, { .DisplaySize = Size , .DrawMode = eDrawMode::ADDITIVE , .DrawScale = FinalScale , .Pivot = vec2(0.5f,0.5f), .DrawColor = FinalColor } );

            // teraz właściwy particle
            FinalScale = FinalScale / 4;
            FinalColor = ParticleColor;
            DisplayTexture(ParticleName, ParticlePos, { .DisplaySize = Size , .DrawMode = eDrawMode::ADDITIVE , .DrawScale = FinalScale , .Pivot = vec2(0.5f,0.5f), .DrawColor = FinalColor , .Rotation = ParticleRotation });

            // teraz pomniejszony particle dla efektu "przepalenia"
            FinalScale = FinalScale / 2;
            DisplayTexture(ParticleName, ParticlePos, { .DisplaySize = Size , .DrawMode = eDrawMode::ADDITIVE , .DrawScale = FinalScale , .Pivot = vec2(0.5f,0.5f), .DrawColor = FinalColor , .Rotation = ParticleRotation });
        }
    }
}