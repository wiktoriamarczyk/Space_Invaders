#include "PUp_Health.h"
#include "InGameState.h"

void PUp_Health::Activate(shared_ptr<Player> MyPlayer)
{
    if (m_Game.GetPlayerLivesCount() < 3)
    {
        m_Game.SetPlayerLivesCount(m_Game.GetPlayerLivesCount() + 1);
        m_IsAlive = false;
    }
}
