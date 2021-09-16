#pragma once
#include "GameObject.h"
#include "Shot.h"

class Gun : public GameObject
{
public:
    Gun()=default;
    ~Gun();
    void InitializeGun(SDL_Renderer* pRenderer, float PosX, float PosY);
    void Update(float DeltaTime)override;
    void Render(SDL_Renderer* pRenderer)override;
    vector<shared_ptr<Shot>> GetShots();
    void Shoot(float PosX, float PosY);
    static int NumOfLives();

private:
    SDL_Texture* m_pTexture = nullptr;
    SDL_Texture* m_pNormalTexture = nullptr;
    SDL_Texture* m_pDyingTexture = nullptr;
    vector<shared_ptr<Shot>> m_Shots;
    float m_ShootingTimer = 20.0f;
    float m_TextureTimer = 25.0f;
    bool m_IsDying = false;
    static int m_NumOfLives;
};

