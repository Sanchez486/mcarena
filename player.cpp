#include "inc/player.h"

Player::Player() : heroGroup()
{

}

HeroGroup& Player::getHeroGroup()
{
    return heroGroup;
}
