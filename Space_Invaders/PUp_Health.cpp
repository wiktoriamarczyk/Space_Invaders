#include "PUp_Health.h"
#include "InGameState.h"
#include "Player.h"

void PUp_Health::Activate(shared_ptr<Player> MyPlayer)
{
    if (m_Game.GetPlayerLivesCount() < 3)
    {
        auto pParticle = m_Game.CreateParticle(MyPlayer->GetPosition(), 10, 1.75f, 0.5);
        pParticle->SetColor(Color{ 255,1,1 });

        m_Game.SetPlayerLivesCount(m_Game.GetPlayerLivesCount() + 1);
        m_IsAlive = false;
    }
}
