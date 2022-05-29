#include "PUp_GunSpeed.h"
#include "InGameState.h"
#include "Player.h"

void PUp_GunSpeed::Activate(shared_ptr<Player> MyPlayer)
{
    auto pParticle = m_Game.CreateParticle(MyPlayer->GetPosition(), 10, 1.75f, 0.5);
    pParticle->SetColor(Color{ 1, 255, 1 });

    MyPlayer->SetSpecialShootingTimer(5.f);
    m_IsAlive = false;
}
