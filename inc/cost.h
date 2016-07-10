#pragma once

#include "herogroup.h"

class Cost
{
private:
    int max;
    int used;

public:
    Cost(int _max = 0);

    int getMax();
    int getUsed();
    int getLeft();
    void setMax(int _max);
    void countUsed(const HeroGroup &heroGroup);
};
