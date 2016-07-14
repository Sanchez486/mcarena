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

bool Player::isValidGroup()
{
    return (cost.getLeft() >= 0) && heroGroup.isFull();
}

bool Player::has(Hero *hero)
{
    return heroGroup.find(hero) != HeroPosition::NONE;
}

Hero *Player::at(HeroPosition pos)
{
    return heroGroup.at(pos);
}

HeroPosition Player::find(Hero *hero)
{
    return heroGroup.find(hero);
}
