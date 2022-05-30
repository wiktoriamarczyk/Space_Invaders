#pragma once
#include "GameState.h"
#include "GameObject.h"
#include "ParticleEmiter.h"
#include "PowerUp.h"

class InGameState : public GameState
{
public:
    InGameState(shared_ptr<Font> MyFont);
    ~InGameState();
    void Update(float DeltaTime)override;
    void Render(SDL_Renderer* pRenderer)override;
    void OnEnter()override;
    void CreateObject();
    void FreeResources();

    template<typename T>
    vector<shared_ptr<T>> GetObjects();

    shared_ptr<ParticleEmiter> CreateParticle(vec2 Position, int ParticleCount, int ParticleScale, float MaxLifeTime);
    shared_ptr<PowerUp> CreatePowerUp(string Name, vec2 Position, ePowerUpType Type);

    void SetPointsInfoTimer(float Value);
    void SetSpaceInvadersNum(int Value);
    int GetSpaceInvadersNum()const;
    void SetBossStatus(bool BossStatus);
    int GetBossStatus()const;
    void SetNumOfPoints(int Value);
    int GetNumOfPoints()const;
    void SetPlayerLivesCount(int Value);
    int GetPlayerLivesCount()const;


private:
    vector<shared_ptr<GameObject>> m_AllGameObjects;
    int                            m_PlayerLives = 3;
    SDL_Texture*                   m_GunIconTexture = nullptr;
    float                          m_DyingTimer = 2.0f;
    int                            m_NumOfSpaceInvaders = 0;
    bool                           m_BossIsDead = false;
    int                            m_NumOfPoints = 0;

    float                          m_PointsInfoTimer = 0.f;
};

template<typename T>
vector<shared_ptr<T>> InGameState::GetObjects()
{
    vector<shared_ptr<T>> specific_objects;

    for (int i = 0; i < m_AllGameObjects.size(); ++i)
    {
        shared_ptr<T> object = dynamic_pointer_cast<T>(m_AllGameObjects[i]);

        if (object)
        {
            specific_objects.push_back(object);
        }
    }

    return specific_objects;
}