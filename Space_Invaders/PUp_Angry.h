#pragma once
#include "PowerUp.h"
#include "Player.h"

class PUp_Angry : public PowerUp
{
public:
    using PowerUp::PowerUp;
    void Activate(shared_ptr<Player> MyPlayer)override;
};

