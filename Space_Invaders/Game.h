#pragma once
#include "Common.h"
#include "GameObject.h"

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
    SDL_Renderer* m_pRenderer = nullptr;
    SDL_Window* m_pWindow = nullptr;
    vector<shared_ptr<GameObject>> m_AllGameObjects;
    //Font m_Font;
};

