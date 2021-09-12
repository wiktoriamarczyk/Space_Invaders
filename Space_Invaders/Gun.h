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
    void SetShotStatus(bool ShotStatus);

private:
    SDL_Texture* m_pTexture = nullptr;
    vector<shared_ptr<Shot>> m_Shots;
    float m_ShootingTimer = 30.0f;
    bool m_ShootYourShot = false;
};

