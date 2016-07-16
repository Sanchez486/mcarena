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

bool Player::isValidGroup() const
{
    return (cost.getLeft() >= 0) && heroGroup.isFull();
}

bool Player::has(Hero *hero) const
{
    return heroGroup.find(hero) != HeroPosition::NONE;
}

Hero *Player::at(HeroPosition pos) const
{
    return heroGroup.at(pos);
}

HeroPosition Player::find(Hero *hero) const
{
    return heroGroup.find(hero);
}

int Player::countAlive() const
{
    return heroGroup.front1->isAlive() +
            heroGroup.front2->isAlive() +
            heroGroup.front3->isAlive() +
            heroGroup.back1->isAlive() +
            heroGroup.back2->isAlive() +
            heroGroup.back3->isAlive();
}
