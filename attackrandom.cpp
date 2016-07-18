#include "inc/attackrandom.h"

AttackRandom::AttackRandom(int _numTargets, const Damage &_damage)
    : Action(),
      numTargets(_numTargets),
      damage(_damage)
{

}

Action *AttackRandom::clone() const
{
    return new AttackRandom(*this);
}

Targets AttackRandom::getAvaliableTargetsPlayer1() const
{
    if(!player1->has(sender))
    {
        return getAliveTargets(player1);
    }

    return Targets(false);
}

Targets AttackRandom::getAvaliableTargetsPlayer2() const
{
    if(!player2->has(sender))
    {
        return getAliveTargets(player2);
    }

    return Targets(false);
}

Targets AttackRandom::getTargetsPlayer1() const
{
    if(player1->has(target))
        return targets;

    return Targets(false);
}

Targets AttackRandom::getTargetsPlayer2() const
{
    if(player2->has(target))
        return targets;

    return Targets(false);
}

std::string AttackRandom::getName() const
{
    return "Random shot";
}

std::string AttackRandom::getDescription() const
{
    std::string dmgString;
    if(damage.min == damage.max)
        dmgString = std::to_string(damage.min);
    else
        dmgString = std::to_string(damage.min) + "-" + std::to_string(damage.max);

    return "deal " + dmgString + " damage to " + std::to_string(numTargets) +
            " random enemies";
}

void AttackRandom::doAction()
{
    Player *player;
    if(player1->has(target))
    {
        player = player1;
    }
    else
    {
        player = player2;
    }

    targets = getRandomAliveTargets(player, numTargets);

    attackAllTargets(player, targets, damage);
}
