#include "inc/attackwithchance.h"

AttackWithChance::AttackWithChance(const Damage &_damage, double _chance)
    : Action(),
      damage(_damage),
      chance(_chance)
{

}

Action *AttackWithChance::clone() const
{
    return new AttackWithChance(*this);
}

Targets AttackWithChance::getAvaliableTargetsPlayer1() const
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

Targets AttackWithChance::getAvaliableTargetsPlayer2() const
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

Targets AttackWithChance::getTargetsPlayer1() const
{
    HeroPosition pos = player1->find(target);
    Targets targets;
    targets.set(pos);

    return targets;
}

Targets AttackWithChance::getTargetsPlayer2() const
{
    HeroPosition pos = player2->find(target);
    Targets targets;
    targets.set(pos);

    return targets;
}

std::string AttackWithChance::getName() const
{
    return "Lucky strike";
}

std::string AttackWithChance::getDescription() const
{
    return "has a " + std::to_string(chance * 100) + "% chance of dealing " +
            std::to_string(damage.min) + "-" + std::to_string(damage.max) + " damage";
}

void AttackWithChance::doAction()
{
    int realDamage;
    if(rollChance(chance))
    {
        realDamage= getRandom(damage);
    }
    else
    {
        realDamage = 0;
    }

    realDamage = countDamageWithElement(realDamage, sender, target);

    target->getStats().hp.curr -= realDamage;
}
