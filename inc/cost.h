#pragma once

#include "herogroup.h"

class Cost
{
private:
    int max;
    int used;

public:
    Cost(int _max = 0);

    int getMax() const;
    int getUsed() const;
    int getLeft() const;
    void setMax(int _max);
    void countUsed(const HeroGroup &heroGroup);
};
