#include "inc/player.h"

Player::Player() : heroGroup(), cost()
{
    updateCost();
}

HeroGroup& Player::getHeroGroup()
{
    return heroGroup;
}

Cost &Player::getCost()
{
    return cost;
}

void Player::updateCost()
{
    cost.countUsed(heroGroup);
}

void Player::setMaxCost(int max)
{
    cost.setMax(max);
}
