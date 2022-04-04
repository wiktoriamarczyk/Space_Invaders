#pragma once
#include "GameState.h"
#include "GameObject.h"
#include "Player.h"
#include "ParticleEmiter.h"

class InGameState : public GameState
{
public:
    InGameState(shared_ptr<Font> MyFont, SDL_Renderer* pRenderer);
    ~InGameState();
    void Update(float DeltaTime)override;
    void Render()override;
    void OnEnter()override;
    void CreateObject();
    shared_ptr<Player> GetPlayer()const;
    void FreeResources();
    shared_ptr<ParticleEmiter> CreateParticle(vec2 Position);

    void SetSpaceInvadersNum(int Value);
    int GetSpaceInvadersNum()const;
    void SetBossStatus(bool BossStatus);
    int GetBossStatus()const;
    void SetNumOfPoints(int Value);
    int GetNumOfPoints()const;


private:
    vector<shared_ptr<GameObject>> m_AllGameObjects;
    shared_ptr<Player>             m_Player;
    SDL_Texture*                   m_GunIconTexture = nullptr;
    float                          m_DyingTimer = 50.0f;
    int                            m_NumOfSpaceInvaders = 0;
    bool                           m_BossIsDead = false;
    int                            m_NumOfPoints = 0;
};

