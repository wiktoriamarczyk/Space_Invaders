#pragma once
#include "GameObject.h"

class SpaceInvader : public GameObject
{
public:
    SpaceInvader(SDL_Renderer* pRenderer, float CenterPosX, float CenterPosY);
    ~SpaceInvader();
    void Update(float DeltaTime)override;
    void Render(SDL_Renderer* pRenderer)override;
private:
    SDL_Texture* m_pTexture = nullptr;
    SDL_Surface* m_pImage = nullptr;
    SDL_Rect m_Rect;
    float m_Timer = 100.0f;
    static bool m_ChangeDirection;
};

