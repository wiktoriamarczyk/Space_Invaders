#pragma once
#include "GameState.h"

class InGameState : public GameState
{
public:
    InGameState(shared_ptr<Font> MyFont, SDL_Renderer* pRenderer);
    ~InGameState();
    void InitializeInGameStateTextures();
    void Update(float DeltaTime)override;
    void Render(SDL_Renderer* pRenderer)override;
    void OnEnter()override;
    void CreateObject();

private:
    SDL_Renderer* m_pRenderer = nullptr;
    vector<shared_ptr<GameObject>> m_AllGameObjects;
    SDL_Texture* m_GunIconTexture = nullptr;

};

