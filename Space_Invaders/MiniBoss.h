#pragma once
#include "GameObject.h"

class MiniBoss : public GameObject
{
public:
    MiniBoss(SDL_Renderer* pRenderer);
    ~MiniBoss();
    void InitializeMiniBossTexture();
    void DestroyMiniBossTextures();
    void Update(float DeltaTime)override;
    void Render(SDL_Renderer* pRenderer)override;
private:
    SDL_Renderer* m_pRenderer = nullptr;
    SDL_Texture* m_pTexture = nullptr;
    bool m_ChangeDirectionX = false;
};

