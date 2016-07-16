#include "inc/stun.h"

Stun::Stun(int _duration)
    : Effect(_duration)
{

}

bool Stun::onTurn(Hero *hero)
{
    return true; // skip turn
}
