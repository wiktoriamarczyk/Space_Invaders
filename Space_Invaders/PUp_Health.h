#pragma once
#include "PowerUp.h"

class PUp_Health : public PowerUp
{
public:
    using PowerUp::PowerUp;
    void Activate(shared_ptr<Player> MyPlayer)override;
};

