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
        return getAliveAttackTargets(player2, player1);
    }

    return Targets();
}

Targets AttackSingle::getAvaliableTargetsPlayer2() const
{
    if(!player2->has(sender))
    {
        return getAliveAttackTargets(player1, player2);
    }

    return Targets();
}

Targets AttackSingle::getTargetsPlayer1() const
{
    Targets targets;
    targets.set(player1->find(target));

    return targets;
}

Targets AttackSingle::getTargetsPlayer2() const
{
    Targets targets;
    targets.set(player2->find(target));

    return targets;
}

std::string AttackSingle::getName() const
{
    return "Wide attack";
}

std::string AttackSingle::getDescription() const
{
    std::string dmgString;
    if(damage.min == damage.max)
        dmgString = std::to_string(damage.min);
    else
        dmgString = std::to_string(damage.min) + "-" + std::to_string(damage.max);

    return "deal " + dmgString + " damage";
}

void AttackSingle::doAction()
{
    int realDamage = getRandom(damage);

    realDamage = countDamageWithElement(realDamage, sender, target);

    target->getStats().hp.curr -= realDamage;
}
