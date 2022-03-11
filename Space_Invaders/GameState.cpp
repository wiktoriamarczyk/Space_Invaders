#include "GameState.h"
#include "Engine.h"

bool GameState::m_GameOver = false;

GameState::GameState(eStateID StateID) : m_StateID(StateID) {}


eStateID GameState::GetStateID()const
{
    return m_StateID;
}

eStateID GameState::GetNextStateID()const
{
    return m_NextStateID;
}

void GameState::OnEnter()
{
    m_NextStateID = eStateID::UNKNOWN;
}

void GameState::DisplayTexture(const string& FileName, vec2i Position, optional<vec2i> Size)
{
    Engine::GetSingleton()->DisplayTexture(("../Data/" + FileName).c_str(), Position, Size);
}

void GameState::DisplayTexture(const string& FileName, SDL_Rect srcrect, SDL_Rect dstrect)
{
    Engine::GetSingleton()->DisplayTexture(("../Data/" + FileName).c_str(), srcrect, dstrect);
}
