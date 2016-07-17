#include "inc/attackwithdamagedecrease.h"
#include "inc/decreasedamage.h"

AttackWithDamageDecrease::AttackWithDamageDecrease(const Damage &_damage, double _rate, int _duration)
    : Action(),
      damage(_damage),
      rate(_rate),
      duration(_duration)
{

}

Action *AttackWithDamageDecrease::clone() const
{
    return new AttackWithDamageDecrease(*this);
}

Targets AttackWithDamageDecrease::getAvaliableTargetsPlayer1() const
{
    if(!player1->has(sender))
    {
        return getAliveAttackTargets(player2, player1);
    }

    return Targets();
}

Targets AttackWithDamageDecrease::getAvaliableTargetsPlayer2() const
{
    if(!player2->has(sender))
    {
        return getAliveAttackTargets(player1, player2);
    }

    return Targets();
}

Targets AttackWithDamageDecrease::getTargetsPlayer1() const
{
    Targets targets;
    targets.set(player1->find(target));

    return targets;
}

Targets AttackWithDamageDecrease::getTargetsPlayer2() const
{
    Targets targets;
    targets.set(player2->find(target));

    return targets;
}

std::string AttackWithDamageDecrease::getName() const
{
    return "Curse";
}

std::string AttackWithDamageDecrease::getDescription() const
{
    return "deal " + std::to_string(damage.min) + "-" + std::to_string(damage.max) +
            " damage and decrease target`s attack by " + std::to_string(rate * 100) +
            "% for " + std::to_string(duration) + " turns";
}

void AttackWithDamageDecrease::doAction()
{
    int realDamage = getRandom(damage);

    realDamage = countDamageWithElement(realDamage, sender, target);

    target->getStats().hp.curr -= realDamage;
    target->add(new DecreaseDamage(duration, rate));
}
