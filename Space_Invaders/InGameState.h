#pragma once
#include "GameState.h"

class InGameState : public GameState
{
public:
    InGameState(shared_ptr<Font> MyFont, SDL_Renderer* pRenderer);
    ~InGameState();
    void Update(float DeltaTime)override;
    void Render()override;
    void OnEnter()override;
    void CreateObject();
    void DisplayTexture(const string& FileName, vec2i Position, optional<vec2i> Size = nullopt);
    void DisplayTexture(const string& FileName, SDL_Rect dstrect, SDL_Rect srcrect);
    void FreeResources();

private:
    vector<shared_ptr<GameObject>> m_AllGameObjects;
    SDL_Texture*                   m_GunIconTexture = nullptr;
    float                          m_DyingTimer = 100.0f;
};

