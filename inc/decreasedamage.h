#pragma once

#include "effect.h"

class DecreaseDamage : public Effect
{
private:
    double rate;  // increase rate

public:
    DecreaseDamage(int _duration, double _rate);

    virtual void onAdd(Hero *hero);
    virtual void onRemove(Hero *hero);
};
