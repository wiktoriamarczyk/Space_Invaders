#include "PUp_Angry.h"
#include "InGameState.h"

void PUp_Angry::Activate(shared_ptr<Player> MyPlayer)
{
    auto pParticle = m_Game.CreateParticle(MyPlayer->GetPosition(), 10, 1.75f, 0.5);
    pParticle->SetColor(Color::RED);

    m_Game.MakeInvaderAngry(3.f);
    m_IsAlive = false;
}
