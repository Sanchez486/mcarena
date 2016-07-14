#include "inc/action.h"

Action::Action()
    : player1(nullptr), player2(nullptr), sender(nullptr), target(nullptr)
{

}

Action::~Action()
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

Hero* Action::getSender() const
{
    return sender;
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

// TODO: return [num] random alive targets
Targets Action::getRandomAliveTargets(Player *player, int num) const
{
    Targets targets;
    targets.set(HeroPosition::front1);
    targets.set(HeroPosition::front2);
    targets.set(HeroPosition::front3);

    return targets;
}

int Action::countAlive(Player *player) const
{
    Targets targets = getAliveTargets(player);
    return targets.front1 + targets.front2 + targets.front3 + targets.back1 + targets.back2 + targets.back3;
}

int Action::getRandom(int from, int to) const
{
    return rand()%(to-from + 1) + from;
}

int Action::getRandom(const Damage &damage) const
{
    return getRandom(damage.min, damage.max);
}

void Action::attack(Hero *hero, const Damage &damage)
{
    hero->getStats().hp.curr -= getRandom(damage);
}

void Action::attackAllTargets(Player *player, const Targets &targets, const Damage &damage)
{
    if(targets.front1)
        attack(player->at(HeroPosition::front1), damage);
    if(targets.front2)
        attack(player->at(HeroPosition::front2), damage);
    if(targets.front3)
        attack(player->at(HeroPosition::front3), damage);
    if(targets.back1)
        attack(player->at(HeroPosition::back1), damage);
    if(targets.back2)
        attack(player->at(HeroPosition::back2), damage);
    if(targets.back3)
        attack(player->at(HeroPosition::back3), damage);
}
