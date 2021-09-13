#pragma once
#include "GameObject.h"
#include "Gun.h"

class Shield : public GameObject
{
public:
    Shield(float PosX, float PosY, shared_ptr<Gun> MyGun);
    void Update(float DeltaTime)override;
    void Render(SDL_Renderer* pRenderer)override;
    void SetShotStatus(vec2 &BulletPosition);
    static void InitializeShieldTexture(SDL_Renderer* pRenderer);
    static void DestroyTexture();

private:
    shared_ptr<Gun> m_Gun;
    SDL_Rect m_TextureDestructionLevel;
    static SDL_Texture* m_pTexture;
    int m_DestructionLevel = 0;
};
