#include "inc/attack.h"

Action *Attack::clone() const
{
    return new Attack(*this);
}

Targets Attack::getAvaliableTargetsPlayer1() const
{
    if(!player1->has(sender))
    {
        if(sender->getStats().kind == Kind::melee)
        {
            return getAliveTargetsFrontLine(player1);
        }
        if(sender->getStats().kind == Kind::range)
        {
            return getAliveTargets(player1);
        }
    }

    return Targets();
}

Targets Attack::getAvaliableTargetsPlayer2() const
{
    if(!player2->has(sender))
    {
        if(sender->getStats().kind == Kind::melee)
        {
            return getAliveTargetsFrontLine(player2);
        }
        if(sender->getStats().kind == Kind::range)
        {
            return getAliveTargets(player2);
        }
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

const std::string &Attack::getName() const
{
    return "Attack";
}

const std::string &Attack::getDescription() const
{
    return "simple attack";
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
