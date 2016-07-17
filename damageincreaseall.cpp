#include "inc/damageincreaseall.h"
#include "inc/increasedamage.h"

DamageIncreaseAll::DamageIncreaseAll(double _rate, int _duration)
    : Action(),
      rate(_rate),
      duration(_duration)
{

}

Action *DamageIncreaseAll::clone() const
{
    return new DamageIncreaseAll(*this);
}

Targets DamageIncreaseAll::getAvaliableTargetsPlayer1() const
{
    if(player1->has(sender))
        return getAliveTargets(player1);

    return Targets(false);
}

Targets DamageIncreaseAll::getAvaliableTargetsPlayer2() const
{
    if(player2->has(sender))
        return getAliveTargets(player2);

    return Targets(false);
}

Targets DamageIncreaseAll::getTargetsPlayer1() const
{
    if(player1->has(sender))
        return getAliveTargets(player1);

    return Targets(false);
}

Targets DamageIncreaseAll::getTargetsPlayer2() const
{
    if(player2->has(sender))
        return getAliveTargets(player2);

    return Targets(false);
}

std::string DamageIncreaseAll::getName() const
{
    return "Increase damage";
}

std::string DamageIncreaseAll::getDescription() const
{
    return "buff allies` damage by " + std::to_string(rate) + "% for " +
            std::to_string(duration) + " turns";
}

void DamageIncreaseAll::doAction()
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

    if(player->at(HeroPosition::front1)->isAlive())
        player->at(HeroPosition::front1)->add(new IncreaseDamage(duration, rate));

    if(player->at(HeroPosition::front2)->isAlive())
        player->at(HeroPosition::front2)->add(new IncreaseDamage(duration, rate));

    if(player->at(HeroPosition::front3)->isAlive())
        player->at(HeroPosition::front3)->add(new IncreaseDamage(duration, rate));

    if(player->at(HeroPosition::back1)->isAlive())
        player->at(HeroPosition::back1)->add(new IncreaseDamage(duration, rate));

    if(player->at(HeroPosition::back2)->isAlive())
        player->at(HeroPosition::back2)->add(new IncreaseDamage(duration, rate));

    if(player->at(HeroPosition::back3)->isAlive())
        player->at(HeroPosition::back3)->add(new IncreaseDamage(duration, rate));
}
