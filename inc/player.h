#pragma once

#include "herogroup.h"

class Player
{
private:
    HeroGroup heroGroup;

public:
    Player();

    HeroGroup& getHeroGroup();
};
