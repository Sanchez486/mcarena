#include "inc/lifesteal.h"

Lifesteal::Lifesteal(const Damage &_damage)
    : Action(),
      damage(_damage)
{

}

Action *Lifesteal::clone() const
{
    return new Lifesteal(*this);
}

Targets Lifesteal::getAvaliableTargetsPlayer1() const
{
    if(!player1->has(sender))
    {
        return getAliveAttackTargets(player2, player1);
    }

    return Targets();
}

Targets Lifesteal::getAvaliableTargetsPlayer2() const
{
    if(!player2->has(sender))
    {
        return getAliveAttackTargets(player1, player2);
    }

    return Targets();
}

Targets Lifesteal::getTargetsPlayer1() const
{
    Targets targets;
    targets.set(player1->find(target));

    return targets;
}

Targets Lifesteal::getTargetsPlayer2() const
{
    Targets targets;
    targets.set(player2->find(target));

    return targets;
}

std::string Lifesteal::getName() const
{
    return "Lifesteal";
}

std::string Lifesteal::getDescription() const
{
    return "deal " + std::to_string(damage.min) + "-" + std::to_string(damage.max) +
            " damage and heal back for the same amount";
}

void Lifesteal::doAction()
{
    int realDamage = getRandom(damage);

    realDamage = countDamageWithElement(realDamage, sender, target);

    target->getStats().hp.curr -= realDamage;
    sender->getStats().hp.add(realDamage);
}
