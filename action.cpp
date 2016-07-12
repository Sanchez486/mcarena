#include "inc/action.h"

Action::Action()
    : player1(nullptr), player2(nullptr), sender(nullptr), target(nullptr)
{

}

void Action::setPlayers(Player *_player1, Player *_player2)
{
    player1 = _player1;
    player2 = _player2;
}

void Action::setSender(Hero *_sender)
{
    sender = _sender;
}

void Action::setTarget(Hero *_target)
{
    target = _target;
}

Hero* Action::getSender()
{
    return sender;
}

Targets Action::getAvaliableTargetsPlayer1()
{
    if(player2->getHeroGroup().find(sender) != HeroPosition::NONE)
    {
        return Targets(true);
    }

    return Targets(false);
}

Targets Action::getAvaliableTargetsPlayer2()
{
    if(player1->getHeroGroup().find(sender) != HeroPosition::NONE)
    {
        return Targets(true);
    }

    return Targets(false);
}

Targets Action::getTargetsPlayer1()
{
    Targets targets;
    targets.set(player1->getHeroGroup().find(target));

    return targets;
}

Targets Action::getTargetsPlayer2()
{
    Targets targets;
    targets.set(player2->getHeroGroup().find(target));

    return targets;
}

void Action::doAction()
{

}
