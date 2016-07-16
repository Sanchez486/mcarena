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

Targets Lifesteal::getAvaliableTargetsPlayer2() const
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

Targets Lifesteal::getTargetsPlayer1() const
{
    HeroPosition pos = player1->find(target);
    Targets targets;
    targets.set(pos);

    return targets;
}

Targets Lifesteal::getTargetsPlayer2() const
{
    HeroPosition pos = player2->find(target);
    Targets targets;
    targets.set(pos);

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

    if(sender->getStats().element > target->getStats().element)
        realDamage *= 1.25;

    if(sender->getStats().element < target->getStats().element)
        realDamage *= 0.8;

    target->getStats().hp.curr -= realDamage;
    sender->getStats().hp.add(realDamage);
}
