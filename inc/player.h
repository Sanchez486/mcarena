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

    bool isValidGroup();
    bool has(Hero *hero);
    Hero* at(HeroPosition pos);
    HeroPosition find(Hero *hero);
};
