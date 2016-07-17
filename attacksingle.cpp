#include "inc/attacksingle.h"

AttackSingle::AttackSingle(const Damage &_damage)
    : Action(),
      damage(_damage)
{

}

Action *AttackSingle::clone() const
{
    return new AttackSingle(*this);
}

Targets AttackSingle::getAvaliableTargetsPlayer1() const
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

Targets AttackSingle::getAvaliableTargetsPlayer2() const
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

Targets AttackSingle::getTargetsPlayer1() const
{
    HeroPosition pos = player1->find(target);
    Targets targets;
    targets.set(pos);

    return targets;
}

Targets AttackSingle::getTargetsPlayer2() const
{
    HeroPosition pos = player2->find(target);
    Targets targets;
    targets.set(pos);

    return targets;
}

std::string AttackSingle::getName() const
{
    return "Wide attack";
}

std::string AttackSingle::getDescription() const
{
    return "attack for " + std::to_string(damage.min) + "-" + std::to_string(damage.max) + " damage";
}

void AttackSingle::doAction()
{
    int realDamage = getRandom(damage);

    realDamage = countDamageWithElement(realDamage, sender, target);

    target->getStats().hp.curr -= realDamage;
}
