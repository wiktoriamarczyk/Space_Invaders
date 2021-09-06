#pragma once
#include "Common.h"

class Game;

class Engine
{
    static Engine* pSingleton;
    bool m_IsRunning = true;
    SDL_Renderer* m_pRenderer = nullptr;
    SDL_Window* m_pWindow = nullptr;
    SDL_Surface* m_pImage = nullptr;
    SDL_Texture* m_pTexture = nullptr;
    Game* GameState = nullptr;
    //void PlaySound(const string& fileName) ==TODO==
public:
    Engine();
    ~Engine();
    static Engine* GetSingleton();
    bool Initialize();
    void Loop();
    void ExitGame();
    // vector<shared_ptr<Sound>> m_LoadedSounds;
};

