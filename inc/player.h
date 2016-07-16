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

    bool isValidGroup() const;
    bool has(Hero *hero) const;
    Hero* at(HeroPosition pos) const;
    HeroPosition find(Hero *hero) const;

    int countAlive() const;  // return number of alive heroes
};
