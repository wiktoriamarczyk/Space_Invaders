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
    static void FreeSurfaces();
    static bool ExitGame;

private:
    SDL_Texture* m_pTexture = nullptr;
    SDL_Rect m_MovementRect;
    int m_InvaderID = 0;
    float m_TextureTimer = 100.0f;
    static float m_Speed;
    static int m_NumOfInvaders;
    static bool m_ChangeDirectionX;
    bool m_ChangeDirectionY = false;
    static SDL_Surface* m_pImage1;
    static SDL_Surface* m_pImage2;
    static SDL_Surface* m_pImage3;
};

