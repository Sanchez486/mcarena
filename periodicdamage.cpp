#include "inc/periodicdamage.h"
#include "inc/hero.h"

PeriodicDamage::PeriodicDamage(int _duration, const Damage &_damage)
    : Effect(_duration), damage(_damage)
{

}

bool PeriodicDamage::onTurn(Hero *hero)
{
    int realDamage = getRandom(damage.min, damage.max);
    hero->getStats().hp.curr -= realDamage;

    return false; // do not skip turn
}

int PeriodicDamage::getRandom(int from, int to) const
{
    return rand()%(to-from + 1) + from;
}
