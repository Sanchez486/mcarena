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
        return getAliveAttackTargets(player2, player1);
    }

    return Targets();
}

Targets AttackWithChance::getAvaliableTargetsPlayer2() const
{
    if(!player2->has(sender))
    {
        return getAliveAttackTargets(player1, player2);
    }

    return Targets();
}

Targets AttackWithChance::getTargetsPlayer1() const
{
    Targets targets;
    targets.set(player1->find(target));

    return targets;
}

Targets AttackWithChance::getTargetsPlayer2() const
{
    Targets targets;
    targets.set(player2->find(target));

    return targets;
}

std::string AttackWithChance::getName() const
{
    return "Lucky strike";
}

std::string AttackWithChance::getDescription() const
{
    std::string dmgString;
    if(damage.min == damage.max)
        dmgString = std::to_string(damage.min);
    else
        dmgString = std::to_string(damage.min) + "-" + std::to_string(damage.max);

    return "has a " + std::to_string( (int)(chance * 100) ) + "% chance of dealing " +
            dmgString + " damage";
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
