#include "inc/player.h"

Player::Player() : heroGroup()
{

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
