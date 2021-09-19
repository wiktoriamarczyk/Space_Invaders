#pragma once
#include "GameObject.h"
#include "Gun.h"

class Boss : public GameObject
{
public:
    Boss(SDL_Renderer* pRenderer, shared_ptr<Gun> MyGun);
    ~Boss();
    void InitializeBossTexture();
    void Update(float DeltaTime)override;
    void Render(SDL_Renderer* pRenderer)override;
    int GetRandNumber();
    static int m_LifeStatus;
    static bool m_BossIsDead;

private:
    SDL_Renderer* m_pRenderer = nullptr;
    shared_ptr<Gun> m_Gun;
    SDL_Texture* m_pTexture = nullptr;
    SDL_Texture* m_pNormalTexture = nullptr;
    SDL_Texture* m_pDyingTexture = nullptr;
    bool m_PlayMusic = true;
    bool m_PlayDeathSound = true;
    float m_DyingTimer = 100.0f;
    float m_ShootingTimer = 40.0f;
};

