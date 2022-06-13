#pragma once
#include "PowerUp.h"

class PUp_Shield : public PowerUp
{
public:
    using PowerUp::PowerUp;
    void Activate(shared_ptr<Player> MyPlayer)override;
};