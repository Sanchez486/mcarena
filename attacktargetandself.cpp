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
    return "Furious attack";
}

std::string AttackTargetAndSelf::getDescription() const
{
    std::string dmgTargetString;
    if(damageTarget.min == damageTarget.max)
        dmgTargetString = std::to_string(damageTarget.min);
    else
        dmgTargetString = std::to_string(damageTarget.min) + "-" + std::to_string(damageTarget.max);

    std::string dmgSelfString;
    if(damageSelf.min == damageSelf.max)
        dmgSelfString = std::to_string(damageSelf.min);
    else
        dmgSelfString = std::to_string(damageSelf.min) + "-" + std::to_string(damageSelf.max);

    return "deal " + dmgTargetString + " damage to target and " +
            dmgSelfString + " damage to yourself";
}

void AttackTargetAndSelf::doAction()
{
    int realDamageTarget = getRandom(damageTarget);
    int realDamageSelf = getRandom(damageSelf);

    realDamageTarget = countDamageWithElement(realDamageTarget, sender, target);

    target->getStats().hp.curr -= realDamageTarget;
    sender->getStats().hp.curr -= realDamageSelf;
}
