#pragma once
#include "GameObject.h"

class Player;
class InGameState;

class PowerUp : public GameObject
{
public:
    PowerUp(string Name, InGameState& Game);
    void Update(float DeltaTime)override;
    void Render(SDL_Renderer* pRenderer)override;
    virtual void Activate(shared_ptr<Player> MyPlayer) = 0;
    void SetScale(vec2 Scale);
    
protected:
    InGameState& m_Game;
    string       m_Name;
    vec2         m_Scale{1, 1};
    bool         m_DisplayTexture = true;
};