#pragma once
#include "Common.h"

class Game
{
public:
    Game();
    ~Game();
    void Update(float DeltaTime);
    void Render(SDL_Renderer* pRenderer);
    void CreateObject();
    bool Initialize();
    void Loop();
    void ExitGame();
private:
    bool m_IsRunning = true;
    SDL_Renderer* m_pRenderer = nullptr;
    SDL_Window* m_pWindow = nullptr;
    //Font m_Font;
    // vector<shared_ptr<GameObject>> m_AllGameObjects;
};

