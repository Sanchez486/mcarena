#pragma once

#include "effect.h"

class IncreaseDamage : public Effect
{
private:
    double rate;  // increase rate

public:
    IncreaseDamage(int _duration, double _rate);

    virtual void onAdd(Hero *hero);
    virtual void onRemove(Hero *hero);
};
