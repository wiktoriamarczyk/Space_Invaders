#pragma once
#include "GameObject.h"
#include "Font.h"

class Game
{
public:
    Game()=default;
    ~Game();
    void Update(float DeltaTime);
    void Render();
    void CreateObject();
    bool Initialize();
    void Loop();
    void ExitGame();
    
private:
    bool m_IsRunning = true;
    bool m_GameOver = false;
    SDL_Renderer* m_pRenderer = nullptr;
    SDL_Window* m_pWindow = nullptr;
    vector<shared_ptr<GameObject>> m_AllGameObjects;
    shared_ptr<Font> m_Font;

    SDL_Texture* m_GunIconTexture = nullptr;
    SDL_Texture* m_GameOverTexture = nullptr;
};