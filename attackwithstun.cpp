#include "inc/attackwithstun.h"
#include "inc/stun.h"

AttackWithStun::AttackWithStun(const Damage &_damage, double _chance, int _duration)
    : Action(),
      damage(_damage),
      chance(_chance),
      duration(_duration)
{

}

Action *AttackWithStun::clone() const
{
    return new AttackWithStun(*this);
}

Targets AttackWithStun::getAvaliableTargetsPlayer1() const
{
    if(!player1->has(sender))
    {
        return getAliveAttackTargets(player2, player1);
    }

    return Targets();
}

Targets AttackWithStun::getAvaliableTargetsPlayer2() const
{
    if(!player2->has(sender))
    {
        return getAliveAttackTargets(player1, player2);
    }

    return Targets();
}

Targets AttackWithStun::getTargetsPlayer1() const
{
    Targets targets;
    targets.set(player1->find(target));

    return targets;
}

Targets AttackWithStun::getTargetsPlayer2() const
{
    Targets targets;
    targets.set(player2->find(target));

    return targets;
}

std::string AttackWithStun::getName() const
{
    return "Stun";
}

std::string AttackWithStun::getDescription() const
{
    return "deal " + std::to_string(damage.min) + "-" + std::to_string(damage.max) +
            " damage and stun target for " + std::to_string(duration) + " turns with "
            + std::to_string(chance * 100) + "% chance";
}

void AttackWithStun::doAction()
{
    int realDamage = getRandom(damage);

    realDamage = countDamageWithElement(realDamage, sender, target);

    target->getStats().hp.curr -= realDamage;

    if(rollChance(chance))
    {
        target->add(new Stun(duration));
    }
}
