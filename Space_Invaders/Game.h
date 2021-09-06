#pragma once
#include "Common.h"


class Game
{
public:
    Game();
    void Update(float DeltaTime);
    void Render(SDL_Renderer* pRenderer);
    void CreateObject();
private:
    //Font m_Font;
    // vector<shared_ptr<GameObject>> m_AllGameObjects;
};

