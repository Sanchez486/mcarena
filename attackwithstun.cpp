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
    if(damage.max == 0)
        return "Stun";

    return "Stunning attack";
}

std::string AttackWithStun::getDescription() const
{
    std::string dmgString;
    if(damage.min == damage.max)
        dmgString = std::to_string(damage.min);
    else
        dmgString = std::to_string(damage.min) + "-" + std::to_string(damage.max);

    std::string dmgMessage;
    if(damage.max == 0)
        dmgMessage = "";
    else
        dmgMessage = "deal " + dmgString + " damage and ";

    std::string chanceMessage;
    if(chance == 1)
        chanceMessage = "";
    else
        chanceMessage = " with " + std::to_string( (int)(chance * 100) ) + "% chance";

    return dmgMessage + "stun target for " + std::to_string(duration) + " turn(s)" + chanceMessage;
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
