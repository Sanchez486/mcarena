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
        return getAliveAttackTargets(player2, player1);
    }

    return Targets();
}

Targets AttackTargetAndSelf::getAvaliableTargetsPlayer2() const
{
    if(!player2->has(sender))
    {
        return getAliveAttackTargets(player1, player2);
    }

    return Targets();
}

Targets AttackTargetAndSelf::getTargetsPlayer1() const
{
    Targets targets;
    targets.set(player1->find(target));

    return targets;
}

Targets AttackTargetAndSelf::getTargetsPlayer2() const
{
    Targets targets;
    targets.set(player2->find(target));

    return targets;
}

std::string AttackTargetAndSelf::getName() const
{
    return "Self damaged attack";
}

std::string AttackTargetAndSelf::getDescription() const
{
    return "attack for " + std::to_string(damageTarget.min) + "-" + std::to_string(damageTarget.max) + " damage with self damage of " 
        + std::to_string(damageSelf.min) + "-" +std::to_string(damageSelf.max);
}

void AttackTargetAndSelf::doAction()
{
    int realDamageTarget = getRandom(damageTarget);
    int realDamageSelf = getRandom(damageSelf);

    realDamageTarget = countDamageWithElement(realDamageTarget, sender, target);

    target->getStats().hp.curr -= realDamageTarget;
    sender->getStats().hp.curr -= realDamageSelf;
}
