#include "PUp_Shield.h"
#include "InGameState.h"
#include "Player.h"

void PUp_Shield::Activate(shared_ptr<Player> MyPlayer)
{
    auto pParticle = m_Game.CreateParticle(MyPlayer->GetPosition(), 10, 1.75f, 0.5);
    pParticle->SetColor(Color{ 50, 1, 255 });
    MyPlayer->SetShieldTimer(5.f);
    m_IsAlive = false;
}