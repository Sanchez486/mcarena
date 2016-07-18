#include "inc/applyperiodicdamage.h"
#include "inc/periodicdamage.h"

ApplyPeriodicDamage::ApplyPeriodicDamage(const Damage &_damage, int _duration)
    : Action(),
      damage(_damage),
      duration(_duration)
{

}

Action *ApplyPeriodicDamage::clone() const
{
    return new ApplyPeriodicDamage(*this);
}

Targets ApplyPeriodicDamage::getAvaliableTargetsPlayer1() const
{
    if(!player1->has(sender))
    {
        return getAliveAttackTargets(player2, player1);
    }

    return Targets();
}

Targets ApplyPeriodicDamage::getAvaliableTargetsPlayer2() const
{
    if(!player2->has(sender))
    {
        return getAliveAttackTargets(player1, player2);
    }

    return Targets();
}

Targets ApplyPeriodicDamage::getTargetsPlayer1() const
{
    Targets targets;
    targets.set(player1->find(target));

    return targets;
}

Targets ApplyPeriodicDamage::getTargetsPlayer2() const
{
    Targets targets;
    targets.set(player2->find(target));

    return targets;
}

std::string ApplyPeriodicDamage::getName() const
{
    return "Burn";
}

std::string ApplyPeriodicDamage::getDescription() const
{
    std::string dmgString;
    if(damage.min == damage.max)
        dmgString = std::to_string(damage.min);
    else
        dmgString = std::to_string(damage.min) + "-" + std::to_string(damage.max);

    return "set target on fire to take " + dmgString +
            " damage in next " + std::to_string(duration) + " turn(s)";
}

void ApplyPeriodicDamage::doAction()
{
    target->add(new PeriodicDamage(duration, damage));
}
