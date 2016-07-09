#include "inc/cost.h"

Cost::Cost(int _max) : max(_max), used(0)
{

}

int Cost::getMax()
{
    return max;
}

int Cost::getUsed()
{
    return used;
}

int Cost::getLeft()
{
    return max - used;
}

void Cost::setMax(int _max)
{
    max = _max;
}

void Cost::countUsed(const HeroGroup &heroGroup)
{
    used = 0;
    used += heroGroup.front1->getTemplateStats().cost;
    used += heroGroup.front2->getTemplateStats().cost;
    used += heroGroup.front3->getTemplateStats().cost;
    used += heroGroup.back1->getTemplateStats().cost;
    used += heroGroup.back2->getTemplateStats().cost;
    used += heroGroup.back3->getTemplateStats().cost;
}
