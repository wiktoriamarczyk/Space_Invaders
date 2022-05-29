#include "PUp_GunSpeed.h"
#include "InGameState.h"
#include "Player.h"

void PUp_GunSpeed::Activate(shared_ptr<Player> MyPlayer)
{
    MyPlayer->SetSpecialShootingTimer(5.f);
    m_IsAlive = false;
}
