#pragma once
#include "GameObject.h"

class Shield : public GameObject
{
public:
    Shield(float PosX, float PosY);
    void Update(float DeltaTime)override;
    void Render(SDL_Renderer* pRenderer)override;
    void SetShotStatus(vec2 &BulletPosition);
    static void InitializeShieldTexture(SDL_Renderer* pRenderer);
    static void DestroyTexture();

private:
    SDL_Rect m_TextureDestructionLevel;
    static SDL_Texture* m_pTexture;
};
