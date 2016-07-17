#include "inc/dissipateeffects.h"

DissipateEffects::DissipateEffects()
    : Action()
{

}

Action *DissipateEffects::clone() const
{
    return new DissipateEffects(*this);
}

Targets DissipateEffects::getAvaliableTargetsPlayer1() const
{
    if(player1->has(sender))
        return getAliveTargets(player1);

    return Targets(false);
}

Targets DissipateEffects::getAvaliableTargetsPlayer2() const
{
    if(player2->has(sender))
        return getAliveTargets(player2);

    return Targets(false);
}

Targets DissipateEffects::getTargetsPlayer1() const
{
    if(player1->has(sender))
        return getAliveTargets(player1);

    return Targets(false);
}

Targets DissipateEffects::getTargetsPlayer2() const
{
    if(player2->has(sender))
        return getAliveTargets(player2);

    return Targets(false);
}

std::string DissipateEffects::getName() const
{
    return "Dissipate";
}

std::string DissipateEffects::getDescription() const
{
    return "remove all effects from allies";
}

void DissipateEffects::doAction()
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

    player->at(HeroPosition::front1)->removeAllEffects();
    player->at(HeroPosition::front2)->removeAllEffects();
    player->at(HeroPosition::front3)->removeAllEffects();
    player->at(HeroPosition::back1)->removeAllEffects();
    player->at(HeroPosition::back2)->removeAllEffects();
    player->at(HeroPosition::back3)->removeAllEffects();
}
