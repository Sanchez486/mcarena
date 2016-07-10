#pragma once

#include "herogroup.h"
#include "cost.h"

class Player
{
private:
    HeroGroup heroGroup;
    Cost cost;

public:
    Player();

    HeroGroup& getHeroGroup();
    Cost& getCost();
    void updateCost();
    void setMaxCost(int max);
};
