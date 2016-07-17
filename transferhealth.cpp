#include "inc/transferhealth.h"

TransferHealth::TransferHealth(const Damage &_damage)
    : Action(),
      damage(_damage)
{

}

Action *TransferHealth::clone() const
{
    return new TransferHealth(*this);
}

Targets TransferHealth::getAvaliableTargetsPlayer1() const
{
    if(player1->has(sender))
    {
        Targets targets = getAliveTargets(player1);
        targets.set(player1->find(sender), false);
        return targets;
    }

    return Targets(false);
}

Targets TransferHealth::getAvaliableTargetsPlayer2() const
{
    if(player2->has(sender))
    {
        Targets targets = getAliveTargets(player2);
        targets.set(player2->find(sender), false);
        return targets;
    }

    return Targets(false);
}

Targets TransferHealth::getTargetsPlayer1() const
{
    Targets targets;
    targets.set(player1->find(target));

    return targets;
}

Targets TransferHealth::getTargetsPlayer2() const
{
    Targets targets;
    targets.set(player2->find(target));

    return targets;
}

std::string TransferHealth::getName() const
{
    return "Transfer health";
}

std::string TransferHealth::getDescription() const
{
    return "deal " + std::to_string(damage.min) + "-" + std::to_string(damage.max) +
            " damage to yourself and heal ally for the same amount";
}

void TransferHealth::doAction()
{
    int realDamage = getRandom(damage);

    target->getStats().hp.add(realDamage);
    sender->getStats().hp.curr -= realDamage;
}
