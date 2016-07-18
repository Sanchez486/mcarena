#include "inc/heal.h"

Heal::Heal(Damage _healRange)
    : Action(),
      healRange(_healRange)
{

}

Action *Heal::clone() const
{
    return new Heal(*this);
}

Targets Heal::getAvaliableTargetsPlayer1() const
{
    if(player1->has(sender))
        return getAliveTargets(player1);

    return Targets(false);
}

Targets Heal::getAvaliableTargetsPlayer2() const
{
    if(player2->has(sender))
        return getAliveTargets(player2);

    return Targets(false);
}

Targets Heal::getTargetsPlayer1() const
{
    HeroPosition pos = player1->find(target);
    Targets targets;
    targets.set(pos);

    return targets;
}

Targets Heal::getTargetsPlayer2() const
{
    HeroPosition pos = player2->find(target);
    Targets targets;
    targets.set(pos);

    return targets;
}

std::string Heal::getName() const
{
    return "Heal";
}

std::string Heal::getDescription() const
{
    std::string dmgString;
    if(healRange.min == healRange.max)
        dmgString = std::to_string(healRange.min);
    else
        dmgString = std::to_string(healRange.min) + "-" + std::to_string(healRange.max);

    return "heal ally hero for " + dmgString + " hp";
}

void Heal::doAction()
{
    int realHeal = getRandom(healRange);
    target->getStats().hp.add(realHeal);
}
