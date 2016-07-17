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
    Targets targets;
    targets.set(player1->find(target));

    return targets;
}

Targets Attack::getTargetsPlayer2() const
{
    Targets targets;
    targets.set(player2->find(target));

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

    realDamage = countDamageWithElement(realDamage, sender, target);

    target->getStats().hp.curr -= realDamage;
}
