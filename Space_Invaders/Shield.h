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

private:
    shared_ptr<Gun>     m_Gun;
    SDL_Rect            m_TextureDestructionLevel;
    int                 m_DestructionLevel = 0;
};
