#include "inc/action.h"

Action::Action()
    : player1(nullptr), player2(nullptr), sender(nullptr), target(nullptr)
{

}

Action::~Action()
{

}

Action* Action::clone() const
{
    return new Action(*this);
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

Hero* Action::getSender() const
{
    return sender;
}

Targets Action::getAvaliableTargetsPlayer1() const
{
    if(player2->getHeroGroup().find(sender) != HeroPosition::NONE)
    {
        return Targets(true);
    }

    return Targets(false);
}

Targets Action::getAvaliableTargetsPlayer2() const
{
    if(player1->getHeroGroup().find(sender) != HeroPosition::NONE)
    {
        return Targets(true);
    }

    return Targets(false);
}

Targets Action::getTargetsPlayer1() const
{
    Targets targets;
    targets.set(player1->getHeroGroup().find(target));

    return targets;
}

Targets Action::getTargetsPlayer2() const
{
    Targets targets;
    targets.set(player2->getHeroGroup().find(target));

    return targets;
}

const std::string &Action::getName() const
{
    return "Action";
}

const std::string &Action::getDescription() const
{
    return "description for action";
}

void Action::doAction()
{

}

Targets Action::getAliveTargets(Player *player) const
{
    Targets targets;
    if(player->getHeroGroup().at(HeroPosition::front1)->isAlive())
        targets.set(HeroPosition::front1);
    if(player->getHeroGroup().at(HeroPosition::front2)->isAlive())
        targets.set(HeroPosition::front2);
    if(player->getHeroGroup().at(HeroPosition::front3)->isAlive())
        targets.set(HeroPosition::front3);
    if(player->getHeroGroup().at(HeroPosition::back1)->isAlive())
        targets.set(HeroPosition::back1);
    if(player->getHeroGroup().at(HeroPosition::back2)->isAlive())
        targets.set(HeroPosition::back2);
    if(player->getHeroGroup().at(HeroPosition::back3)->isAlive())
        targets.set(HeroPosition::back3);

    return targets;
}

int Action::countAlive(Player *player)
{
    Target alive = getAliveTargets(player);
    int count = alive.front1 + alive.front2 + alive.front3 + alive.back1 + alive.back2 + alive.back3;
    return count;
}

Targets Action::getRandomAliveTargets(int num) const
{
            
}


Targets Action::getAliveTargetsFrontLine(Player *player) const
{
    Targets targets;
    if(player->getHeroGroup().at(HeroPosition::front1)->isAlive())
        targets.set(HeroPosition::front1);
    if(player->getHeroGroup().at(HeroPosition::front2)->isAlive())
        targets.set(HeroPosition::front2);
    if(player->getHeroGroup().at(HeroPosition::front3)->isAlive())
        targets.set(HeroPosition::front3);

    return targets;
}

Targets Action::getAliveTargetsBackLine(Player *player) const
{
    Targets targets;
    if(player->getHeroGroup().at(HeroPosition::back1)->isAlive())
        targets.set(HeroPosition::back1);
    if(player->getHeroGroup().at(HeroPosition::back2)->isAlive())
        targets.set(HeroPosition::back2);
    if(player->getHeroGroup().at(HeroPosition::back3)->isAlive())
        targets.set(HeroPosition::back3);

    return targets;
}

int Action::getRandom(int from, int to) const
{
    return rand()%(to-from + 1) + from;
}
