#pragma once
#include "GameObject.h"
#include "Gun.h"

class SpaceInvader : public GameObject
{
public:
    SpaceInvader(float PosX, float PosY, shared_ptr<Gun> MyGun);
    void Update(float DeltaTime)override;
    void Render(SDL_Renderer* pRenderer)override;
    SDL_Texture* GetTexture();
    static void InitializeSpaceInvaderTexture(SDL_Renderer* pRenderer);
    static void DestroyTextures();
    static bool ExitGame;

private:
    shared_ptr<Gun> m_Gun;
    SDL_Texture* m_pTexture = nullptr;
    SDL_Rect m_MovementRect;
    int m_InvaderID = 0;
    float m_TextureTimer = 100.0f;
    float m_Speed;
    static int m_NumOfInvaders;
    static bool m_ChangeDirectionX;
    bool m_ChangeDirectionY = false;

    static SDL_Surface* m_pImage;
    static SDL_Texture* m_pTexture1;
    static SDL_Texture* m_pTexture2;
    static SDL_Texture* m_pTexture3;
};

