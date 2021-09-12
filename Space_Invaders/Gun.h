#pragma once
#include "GameObject.h"

class Gun : public GameObject
{
public:
    Gun()=default;
    ~Gun();
    void InitializeGun(SDL_Renderer* pRenderer, float PosX, float PosY);
    void Update(float DeltaTime)override;
    void Render(SDL_Renderer* pRenderer)override;

private:
    SDL_Texture* m_pTexture = nullptr;
};

