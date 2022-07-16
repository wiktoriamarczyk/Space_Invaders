#pragma once
#include "GameObject.h"
#include "Font.h"
#include "Sound.h"

class Game
{
public:
    Game()=default;
    ~Game();
    static Game* GetSingleton();
    void Update(float DeltaTime);
    void Render();
    void CreateObject();
    bool Initialize();
    void Loop();
    void ExitGame();
    void PlaySound(const string& FileName);
    
private:
    static Game* pSingleton;
    bool m_IsRunning = true;
    bool m_GameOver = false;
    SDL_Renderer* m_pRenderer = nullptr;
    SDL_Window* m_pWindow = nullptr;
    vector<shared_ptr<GameObject>> m_AllGameObjects;
    shared_ptr<Font> m_Font;
    vector<shared_ptr<Sound>> m_LoadedSounds;

    SDL_Texture* m_GunIconTexture = nullptr;
    SDL_Texture* m_GameOverTexture = nullptr;
};