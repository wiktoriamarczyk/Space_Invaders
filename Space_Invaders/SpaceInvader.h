#pragma once
#include "GameObject.h"

class SpaceInvader : public GameObject
{
public:
    SpaceInvader(SDL_Renderer* pRenderer, float PosX, float PosY);
    ~SpaceInvader();
    void Update(float DeltaTime)override;
    void Render(SDL_Renderer* pRenderer)override;
    SDL_Texture* GetTexture(SDL_Renderer* pRenderer);

    static void LoadTexture();
private:
    SDL_Texture* m_pTexture = nullptr;
    SDL_Rect m_MovementRect;
    int m_InvaderID = 0;
    float m_Timer = 100.0f;

    static SDL_Surface* m_pImage1;
    static SDL_Surface* m_pImage2;
    static SDL_Surface* m_pImage3;
    static int m_NumOfInvaders;
    static bool m_ChangeDirection;
};

