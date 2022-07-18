#pragma once
#include "GameState.h"
#include "GameObject.h"
#include "Player.h"

class InGameState : public GameState
{
public:
    InGameState(shared_ptr<Font> MyFont, SDL_Renderer* pRenderer);
    ~InGameState();
    void Update(float DeltaTime)override;
    void Render()override;
    void OnEnter()override;
    void CreateObject();
    shared_ptr<Player> GetPlayer()const;
    void DisplayTexture(const string& FileName, vec2i Position, optional<vec2i> Size = nullopt);
    void DisplayTexture(const string& FileName, SDL_Rect srcrect, SDL_Rect dstrect);
    void FreeResources();

private:
    vector<shared_ptr<GameObject>> m_AllGameObjects;
    shared_ptr<Player>             m_Player;
    SDL_Texture*                   m_GunIconTexture = nullptr;
    float                          m_DyingTimer = 100.0f;
};

