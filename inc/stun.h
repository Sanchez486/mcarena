#pragma once

#include "effect.h"

class Stun : public Effect
{
public:
    Stun(int _duration);

    virtual bool onTurn(Hero *hero);
};
