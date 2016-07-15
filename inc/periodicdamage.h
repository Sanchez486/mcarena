#pragma once

#include "effect.h"
#include "damage.h"

class PeriodicDamage : public Effect
{
private:
    Damage damage;

public:
    PeriodicDamage(int _duration, const Damage &_damage);

    virtual bool onTurn(Hero *hero);

private:
    int getRandom(int from, int to) const;  // random int from range [min, max]
};
