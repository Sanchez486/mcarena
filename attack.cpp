#include "inc/attack.h"

Action *Attack::clone() const
{
    return new Attack(*this);
}

Targets Attack::getAvaliableTargetsPlayer1() const
{
    if(!player1->has(sender))
    {
        return getAliveAttackTargets(player2, player1);
    }

    return Targets();
}

Targets Attack::getAvaliableTargetsPlayer2() const
{
    if(!player2->has(sender))
    {
        return getAliveAttackTargets(player1, player2);
    }

    return Targets();
}

Targets Attack::getTargetsPlayer1() const
{
    HeroPosition pos = player1->find(target);
    Targets targets;
    targets.set(pos);

    return targets;
}

Targets Attack::getTargetsPlayer2() const
{
    HeroPosition pos = player2->find(target);
    Targets targets;
    targets.set(pos);

    return targets;
}

std::string Attack::getName() const
{
    return "Attack";
}

std::string Attack::getDescription() const
{
    return "deal damage equal to this hero`s attack";
}

void Attack::doAction()
{
    Damage damage = sender->getStats().damage;
    int realDamage = getRandom(damage.min, damage.max);

    if(sender->getStats().element > target->getStats().element)
        realDamage *= 1.25;

    if(sender->getStats().element < target->getStats().element)
        realDamage *= 0.8;

    target->getStats().hp.curr -= realDamage;
}
