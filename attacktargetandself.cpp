#include "inc/attacktargetandself.h"

AttackTargetAndSelf::AttackTargetAndSelf(const Damage &_damageTarget, const Damage &_damageSelf)
    : Action(),
      damageTarget(_damageTarget),
      damageSelf(_damageSelf)
{

}

Action *AttackTargetAndSelf::clone() const
{
    return new AttackTargetAndSelf(*this);
}

Targets AttackTargetAndSelf::getAvaliableTargetsPlayer1() const
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

Targets AttackTargetAndSelf::getAvaliableTargetsPlayer2() const
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

Targets AttackTargetAndSelf::getTargetsPlayer1() const
{
    HeroPosition pos = player1->find(target);
    Targets targets;
    targets.set(pos);

    return targets;
}

Targets AttackTargetAndSelf::getTargetsPlayer2() const
{
    HeroPosition pos = player2->find(target);
    Targets targets;
    targets.set(pos);

    return targets;
}

const std::string &AttackTargetAndSelf::getName() const
{
    return "Self damaged attack";
}

const std::string &AttackTargetAndSelf::getDescription() const
{
    return "attack for " + std::to_string(damageTarget.min) + "-" + std::to_string(damageTarget.max) + " damage with self damage of " 
        + std::to_string(damageSelf.min) + "-" +std::to_string(damageSelf.max);
}

void AttackTargetAndSelf::doAction()
{
    int realDamageTarget = getRandom(damageTarget);
    int realDamageSelf = getRandom(damageSelf);

    if(sender->getStats().element > target->getStats().element)
        realDamageTarget *= 1.25;

    if(sender->getStats().element < target->getStats().element)
        realDamageTarget *= 0.8;

    target->getStats().hp.curr -= realDamageTarget;
    sender->getStats().hp.curr -= realDamageSelf;
}
