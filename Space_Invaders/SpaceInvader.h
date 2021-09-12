#pragma once
#include "GameObject.h"

class SpaceInvader : public GameObject
{
public:
    SpaceInvader(float PosX, float PosY);
    void Update(float DeltaTime)override;
    void Render(SDL_Renderer* pRenderer)override;
    SDL_Texture* GetTexture();
    static void InitializeSpaceInvaderTexture(SDL_Renderer* pRenderer);
    static void DestroyTextures();
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

    static SDL_Surface* m_pImage;
    static SDL_Texture* m_pTexture1;
    static SDL_Texture* m_pTexture2;
    static SDL_Texture* m_pTexture3;

};

