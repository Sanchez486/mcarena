#include "inc/attackrandom.h"

AttackRandom::AttackRandom(int _numTargets, const Damage &_damage)
    : numTargets(_numTargets), damage(_damage)
{

}

Action *AttackRandom::clone() const
{
    return new AttackRandom(*this);
}

Targets AttackRandom::getAvaliableTargetsPlayer1() const
{
    if(player1->getHeroGroup().find(sender) == HeroPosition::NONE)
    {
        return getAliveTargets(player1);
    }

    return Targets(false);
}

Targets AttackRandom::getAvaliableTargetsPlayer2() const
{
    if(player2->getHeroGroup().find(sender) == HeroPosition::NONE)
    {
        return getAliveTargets(player2);
    }

    return Targets(false);
}

Targets AttackRandom::getTargetsPlayer1() const
{
    if(player1->getHeroGroup().find(target) != HeroPosition::NONE)
        return targets;

    return Targets(false);
}

Targets AttackRandom::getTargetsPlayer2() const
{
    if(player2->getHeroGroup().find(target) != HeroPosition::NONE)
        return targets;

    return Targets(false);
}

const std::string &AttackRandom::getName() const
{
    return "Random shot";
}

const std::string &AttackRandom::getDescription() const
{
    return "Attack " + std::to_string(numTargets) + " random targets for " +
            std::to_string(damage.min) + "-" + std::to_string(damage.max) +
            " damage";
}

void AttackRandom::doAction()
{
    targets = getRandomAliveTargets(numTargets);

    Player *player;
    if(player1->getHeroGroup().find(target) != HeroPosition::NONE)
    {
        player = player1;
    }
    else
    {
        player = player2;
    }

    int realDamage = getRandom(damage.min, damage.max);

    if(targets.front1)
        player->getHeroGroup().at(HeroPosition::front1)->getStats().hp.curr -= realDamage;
    if(targets.front2)
        player->getHeroGroup().at(HeroPosition::front2)->getStats().hp.curr -= realDamage;
    if(targets.front3)
        player->getHeroGroup().at(HeroPosition::front3)->getStats().hp.curr -= realDamage;
    if(targets.back1)
        player->getHeroGroup().at(HeroPosition::back1)->getStats().hp.curr -= realDamage;
    if(targets.back2)
        player->getHeroGroup().at(HeroPosition::back2)->getStats().hp.curr -= realDamage;
    if(targets.back3)
        player->getHeroGroup().at(HeroPosition::back3)->getStats().hp.curr -= realDamage;
}
